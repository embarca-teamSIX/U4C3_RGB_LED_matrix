// buzzer.c
#include "buzzer.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Função para tocar um tom específico no buzzer
void tocar_tom_buzzer(uint16_t frequency, uint32_t duration_ms) {
    gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_PWM); // Configura pino do buzzer para PWM
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_B_PIN);

    pwm_set_wrap(slice_num, 125000000 / frequency); // Período do PWM
    pwm_set_gpio_level(BUZZER_B_PIN, (125000000 / frequency) / 2); // Duty cycle 50%
    pwm_set_enabled(slice_num, true); // Ativa o PWM

    sleep_ms(duration_ms); // Toca por tempo especificado

    pwm_set_enabled(slice_num, false); // Desliga o PWM
    gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_SIO);
    gpio_put(BUZZER_B_PIN, 0);
}


// Função para tocar o som de pulsação
void tocar_pulsacao() {
    tocar_tom_buzzer(440, 200); // Primeiro batimento: frequência 440 Hz, duração 200ms
    sleep_ms(100);              // Pausa curta entre batimentos
    tocar_tom_buzzer(440, 400); // Segundo batimento: frequência 440 Hz, duração 400ms
    sleep_ms(300);              // Pausa antes do próximo ciclo
}

// Função para tocar som de explusão
void tocar_explosao() {
    tocar_tom_buzzer(800, 300);
    sleep_ms(100);
    tocar_tom_buzzer(600, 300);
    sleep_ms(100);
    tocar_tom_buzzer(400, 300);
}

// Função para tocar som de restauração
void tocar_restauracao() {
    tocar_tom_buzzer(400, 200);
    sleep_ms(100);
    tocar_tom_buzzer(600, 200);
    sleep_ms(100);
    tocar_tom_buzzer(800, 200);
}
