#include <stdio.h>
#include "pico/stdlib.h"
#include "include/keypad.h"

// Define os pinos do teclado
uint8_t row_pins[ROWS] = {16, 17, 18, 19};
uint8_t col_pins[COLS] = {20, 4, 9, 8};

// Função para executar ações com base na tecla pressionada
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
    stdio_init_all();
    printf("Inicializando teclado matricial...\n");

    // Inicializa o teclado
    init_keypad(row_pins, col_pins);

    while (1) {
        char key = scan_keypad(row_pins, col_pins);
        if (key != '\0') { // Se uma tecla foi pressionada
            printf("Tecla pressionada: %c\n", key);
            escolher_acao(key); // Executa a ação associada
        }
    }

    return 0;
}