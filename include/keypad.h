#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

// Dimensões do teclado
#define ROWS 4
#define COLS 4

// Mapeamento de teclas
extern char keys[ROWS][COLS];

void init_keypad(uint8_t row_pins[], uint8_t col_pins[]);
char scan_keypad(uint8_t row_pins[], uint8_t col_pins[]);

#endif