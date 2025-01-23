#include "keypad.h"
#include "pico/stdlib.h"

// Mapeamento de teclas
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Inicializa as linhas e colunas do teclado
void init_keypad(uint8_t row_pins[], uint8_t col_pins[]) {
    // Configura os pinos das linhas como entradas pull-down
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_IN);
        gpio_pull_down(row_pins[i]);
    }
    // Configura os pinos das colunas como saídas
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_OUT);
        gpio_put(col_pins[i], 1); // Nível lógico alto inicialmente
    }
}

// Verifica qual tecla foi pressionada
char scan_keypad(uint8_t row_pins[], uint8_t col_pins[]) {
    for (int col = 0; col < COLS; col++) {
        // Ativa a coluna atual (nível lógico baixo)
        gpio_put(col_pins[col], 0);
        for (int row = 0; row < ROWS; row++) {
            if (gpio_get(row_pins[row]) == 1) { // Verifica se a linha está ativa
                while (gpio_get(row_pins[row]) == 1); // Aguarda até que a tecla seja liberada
                gpio_put(col_pins[col], 1); // Restaura a coluna para nível lógico alto
                return keys[row][col]; // Retorna a tecla correspondente
            }
        }
        gpio_put(col_pins[col], 1); // Restaura a coluna para nível lógico alto
    }
    return '\0'; // Nenhuma tecla foi pressionada
}
