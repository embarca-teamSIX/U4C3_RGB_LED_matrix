/*
*  GRUPO 6 - SUBGRUPO 4 - EMBARCATECH
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/pwm.h"

#include "include/keypad.h"
#include "include/animacao_seta_jorge.h"
#include "pride_of_flag.h"
//arquivo .pio
#include "pio_matrix.pio.h"

// #include "include/coracao_pulsante_Deividson.h"
#include "include/matriz_led_control.h"

//pino de saída
#define OUT_PIN 7

#define BUZZER_A_PIN 10
#define BUZZER_B_PIN 21

// Define os pinos do teclado
uint8_t row_pins[ROWS] = {16, 17, 18, 19};
uint8_t col_pins[COLS] = {20, 4, 9, 8};

pio_t meu_pio = {
    .pio = pio0,       
    .ok = false,       
    .i = 0,              
    .r = 0.0,          
    .g = 0.0,          
    .b = 0.0, 
    .sm = 0          
};

// // Função para tocar um tom específico no buzzer
// void tocar_tom_buzzer(uint16_t frequency, uint duration_ms) {
//     gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_PWM); // Configura pino do buzzer para PWM
//     uint slice_num = pwm_gpio_to_slice_num(BUZZER_B_PIN);

//     pwm_set_wrap(slice_num, 125000000 / frequency); // Período do PWM
//     pwm_set_gpio_level(BUZZER_B_PIN, (125000000 / frequency) / 2); // Duty cycle 50%
//     pwm_set_enabled(slice_num, true); // Ativa o PWM

//     sleep_ms(duration_ms); // Toca por tempo especificado

//     pwm_set_enabled(slice_num, false); // Desliga o PWM
//     gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_SIO);
//     gpio_put(BUZZER_B_PIN, 0);
// }

// // Função para tocar o som simulando pulsação
// void tocar_pulsacao() {
//     tocar_tom_buzzer(440, 200); // Primeiro batimento: frequência 440 Hz, duração 200ms
//     sleep_ms(100);              // Pausa curta entre batimentos
//     tocar_tom_buzzer(440, 400); // Segundo batimento: frequência 440 Hz, duração 400ms
//     sleep_ms(300);              // Pausa antes do próximo ciclo
// }

void gpio_setup()
{
    // Configura os pinos do buzzer  Bcomo saída
    gpio_init(BUZZER_B_PIN);
    gpio_set_dir(BUZZER_B_PIN, GPIO_OUT);

    // Configura os pinos do buzzer A como saída
    gpio_init(BUZZER_A_PIN);
    gpio_set_dir(BUZZER_A_PIN, GPIO_OUT);

    // Inicializa o teclado
    init_keypad(row_pins, col_pins);
}

void escolher_acao(char key) 
{
    switch (key) 
    {
        case '1':
            for(int i = 0; i < 2; i++)
            {
                desenho_pio(seta_1, &meu_pio);
                sleep_ms(300);
                desenho_pio(seta_2, &meu_pio);
                sleep_ms(300);
                desenho_pio(seta_3, &meu_pio);
                sleep_ms(300);
                desenho_pio(seta_4, &meu_pio);
                sleep_ms(300);
                desenho_pio(seta_5, &meu_pio);
                sleep_ms(300);
                desenho_pio(seta_6, &meu_pio);
                sleep_ms(300);
                desenho_pio(seta_7, &meu_pio);
                sleep_ms(300);
            } 
            desliga_tudo(&meu_pio); 
            break; 
        case '2': 
        // coracao_pulsante_com_som_vermelho();
            break;
        case '3': 
            break;
        case '4': 
            break;
        case '5': 
                star_spangled_gleison();
            break; // Ação para a tecla '5'
                  //função de gleison
        case '6': 
            break;
        case '7': 
            break;
        case '8': 
            break;
        case '9':
            break;
        case '0':
            break;
        case 'A': 
            desliga_tudo(&meu_pio); 
            break;
        case 'B':
            desenho_pio_azul_100(&meu_pio); 
            break;
        case 'C':
            desenho_pio_vermelho_80(&meu_pio); 
            break;
        case 'D':
            desenho_pio_verde_50(&meu_pio); 
            break;
        case '*': 
            break;
        case '#':
            ligar_todos_os_leds_20_p(&meu_pio); 
            break;
        default: 
            desliga_tudo(&meu_pio);
            break; // Ação padrão para qualquer outra tecla
    }
}

//função principal
int main()
{ 
    init_pio_routine(&meu_pio, OUT_PIN);
    
    // Configura os pinos do buzzer  Bcomo saída
    gpio_init(BUZZER_B_PIN);
    gpio_set_dir(BUZZER_B_PIN, GPIO_OUT);

    // Configura os pinos do buzzer A como saída
    gpio_init(BUZZER_A_PIN);
    gpio_set_dir(BUZZER_A_PIN, GPIO_OUT);

    // Inicializa o teclado
    init_keypad(row_pins, col_pins);

    while (true) 
    {
        char key = scan_keypad(row_pins, col_pins);
        if (key != '\0') // Se uma tecla foi pressionada
        { 
            printf("Tecla pressionada: %c\n", key);
            escolher_acao(key); // Executa a ação associada
        }
        sleep_ms(300);  // debounce
    }

    return 0;
}