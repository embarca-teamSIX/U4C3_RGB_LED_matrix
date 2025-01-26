#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define ROWS 4
#define COLS 4

char keypad[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

char scan_keypad() {
    char tecla;
    printf("Pressione uma tecla do teclado matricial (use '3' para testar, 'Q' para sair): ");
    scanf(" %c", &tecla);
    return tecla;
}

void executar_comando_tecla3() {
    printf("Comando da tecla '3' executado com sucesso!\n");
}

void executar_morse(char letra) {
    switch (letra) {
        case 'S':
            printf("... "); // Código Morse para 'S'
            break;
        case 'O':
            printf("--- "); // Código Morse para 'O'
            break;
        default:
            printf("Letra '%c' não tem código Morse associado.\n", letra);
            break;
    }
    printf("\n");
}

int main() {
    char key;
    bool running = true;

    printf("Sistema inicializado. Pressione teclas para interagir.\n");

    while (running) {
        key = scan_keypad();

        if (key == '3') {
            executar_comando_tecla3();
            executar_morse('S');
            executar_morse('O');
            executar_morse('S');
        } else if (key == 'Q' || key == 'q') {
            printf("Encerrando o programa...\n");
            running = false;
        } else {
            printf("Tecla '%c' pressionada, mas sem comando associado.\n", key);
        }

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    return 0;
}
