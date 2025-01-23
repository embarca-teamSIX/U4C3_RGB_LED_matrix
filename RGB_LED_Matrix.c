/*
    Arquivo principal
    Criado em: 22/01/2025
    Grupo 6 - Subgrupo 4
*/

#include <stdio.h>
#include "pico/stdlib.h"

// Definindo os pinos para o teclado matricial
#define ROWS 4
#define COLS 4
uint8_t row_pins[ROWS] = {2, 3, 4, 5};  // Pinos correspondentes às linhas do teclado
uint8_t col_pins[COLS] = {6, 7, 8, 9};  // Pinos correspondentes às colunas do teclado


// Mapeamento das teclas do teclado matricial
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para inicializar as linhas do teclado como entradas pull-down
void init_keypad() {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]); // Inicializa o pino da linha
        gpio_set_dir(row_pins[i], GPIO_IN); // Configura o pino como entrada
        gpio_pull_down(row_pins[i]); // Ativa o resistor de pull-down
    }
    // Inicializa as colunas como saídas
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]); // Inicializa o pino da coluna
        gpio_set_dir(col_pins[i], GPIO_OUT); // Configura o pino como saída
        gpio_put(col_pins[i], 1); // Configura o pino inicialmente em nível lógico alto
    }
}

// Função para verificar qual tecla foi pressionada no teclado
char scan_keypad() {
    for (int col = 0; col < COLS; col++) {
        // Ativa a coluna atual (nível lógico baixo)
        gpio_put(col_pins[col], 0);
        for (int row = 0; row < ROWS; row++) {
            if (gpio_get(row_pins[row]) == 1) {  // Detecta se a linha está ativa
                while (gpio_get(row_pins[row]) == 1);  // Aguarda até que a tecla seja liberada
                gpio_put(col_pins[col], 1);  // Restaura a coluna para nível lógico alto
                return keys[row][col];  // Retorna a tecla correspondente
            }
        }
        gpio_put(col_pins[col], 1);  // Restaura a coluna para nível lógico alto
    }
    return '\0'; // Retorna nulo se nenhuma tecla foi pressionada
}

// Função para executar uma ação específica com base na tecla pressionada
void escolher_acao(char key) {

    switch (key) {
        case '1': 
            break; // Ação para a tecla '1'
        case '2': 
            break; // Ação para a tecla '2'
        case '3': 
            break; // Ação para a tecla '3'
        case '4': 
            break; // Ação para a tecla '4'
        case '5': 
            break; // Ação para a tecla '5'
        case '6': 
            break; // Ação para a tecla '6'
        case '7': 
            break; // Ação para a tecla '7'
        case '8': 
            break; // Ação para a tecla '8'
        case '9': 
            break; // Ação para a tecla '9'
        case '0': 
            break; // Ação para a tecla '0'
        case 'A': 
            break; // Ação para a tecla 'A'
        case 'B': 
            break; // Ação para a tecla 'B'
        case 'C': 
            break; // Ação para a tecla 'C'
        case 'D': 
            break; // Ação para a tecla 'D'
        case '*': 
            break; // Ação para a tecla '*'
        case '#': 
            break; // Ação para a tecla '#'
        default: 
            break; // Ação padrão para qualquer outra tecla
    }
}

int main() {
    stdio_init_all(); // Inicializa a comunicação padrão (UART)

    // Inicializa o teclado matricial
    init_keypad();

    printf("Teclado matricial pronto!\n");

    while (1) {
        char key = scan_keypad(); // Verifica se uma tecla foi pressionada
        if (key != '\0') {  // Se uma tecla for detectada
            printf("Tecla pressionada: %c\n", key);
            escolher_acao(key);  // Executa a ação associada à tecla
        }
    }

    return 0;
}
