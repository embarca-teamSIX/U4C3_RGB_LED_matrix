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
    for (int i = 0; i < ROWS; i++) {  // Itera sobre cada linha do teclado.
        gpio_init(row_pins[i]);       // Inicializa o pino da linha atual.
        gpio_set_dir(row_pins[i], GPIO_OUT); // Define o pino como saída.
        gpio_put(row_pins[i], 1);     // Define o pino como alto (1).
    }

    for (int i = 0; i < COLS; i++) {  // Itera sobre cada coluna do teclado.
        gpio_init(col_pins[i]);       // Inicializa o pino da coluna atual.
        gpio_set_dir(col_pins[i], GPIO_IN);  // Define o pino como entrada.
        gpio_pull_up(col_pins[i]);    // Ativa o resistor de pull-up no pino.
    }
}

// Verifica qual tecla foi pressionada
char scan_keypad(uint8_t row_pins[], uint8_t col_pins[]) {
    for (int row = 0; row < ROWS; row++)
    {
        gpio_put(row_pins[row], 0);

        for (int col = 0; col < COLS; col++) 
        {
            if (gpio_get(col_pins[col]) == 0)
            {
                while (gpio_get(col_pins[col]) == 1); // Aguarda até que a tecla seja liberada
                gpio_put(row_pins[row], 1); // Restaura a coluna para nível lógico alto
                return keys[row][col]; // Retorna a tecla correspondente
            }
        }
        gpio_put(row_pins[row], 1);
    }

    return '\0'; // Nenhuma tecla foi pressionada
}
