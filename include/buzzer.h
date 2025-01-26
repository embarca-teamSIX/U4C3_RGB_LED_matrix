#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h> // Necessário para uint16_t e outros tipos de largura fixa

// Define o pino do buzzer
#define BUZZER_B_PIN 21

// Protótipos das funções para o buzzer
void tocar_tom_buzzer(uint16_t frequency, uint32_t duration_ms); // Corrigido para uint32_t
void tocar_pulsacao();
void tocar_explosao();
void tocar_restauracao();

#endif
