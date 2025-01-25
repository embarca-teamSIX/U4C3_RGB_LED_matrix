#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "include/keypad.h"

#define RED_LED_RGB 13
#define GREEN_LED_RGB 11
#define BLUE_LED_RGB 12

#define MATRIZ_LED_PIN 7

// Define os pinos do teclado
uint8_t row_pins[ROWS] = {16, 17, 18, 19};
uint8_t col_pins[COLS] = {20, 4, 9, 8};

void configure_pwm(uint gpio_pin) {
    
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM);
    // Obtém o slice de PWM do pino
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);
    // Habilita o PWM no slice
    pwm_set_enabled(slice_num, true);
}

void set_pwm_duty(uint gpio_pin, uint8_t value) {
    // Obtém o slice e canal do pino
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);
    uint channel = pwm_gpio_to_channel(gpio_pin);

    // Mapeia o valor de 0-255 para 0-65535 (16 bits para resolução PWM)
    uint16_t duty_cycle = (value * 65535) / 255;

    // Define o duty cycle do canal
    pwm_set_chan_level(slice_num, channel, duty_cycle);
}

void setup_gpio()
{
    // gpio_init(RED_LED_RGB);             
    // gpio_set_dir(RED_LED_RGB, GPIO_OUT);
    // gpio_init(GREEN_LED_RGB);
    // gpio_set_dir(GREEN_LED_RGB, GPIO_OUT);
    // gpio_init(BLUE_LED_RGB);
    // gpio_set_dir(BLUE_LED_RGB, GPIO_OUT);
    
    configure_pwm(RED_LED_RGB);
    configure_pwm(GREEN_LED_RGB);
    configure_pwm(BLUE_LED_RGB);
    gpio_init(MATRIZ_LED_PIN);
    gpio_set_dir(MATRIZ_LED_PIN, GPIO_OUT);
}

// Função para executar ações com base na tecla pressionada
void escolher_acao(char key) 
{
    switch (key) 
    {
        case '1': 
            gpio_put(RED_LED_RGB, 0);
            break; // Ação para a tecla '1'
        case '2': 
            break; // Ação para a tecla '2'
        case '3': 
            break; // Ação para a tecla '3'
        case '4': 
            break; // Ação para a tecla '4'
        case '5': 
            break; // Ação para a tecla '5'
                  //função de gleison
        case '6': 
            break; // Ação para a tecla '6'
        case '7': 
            break; // Ação para a tecla '7'
        case '8': 
            break; // Ação para a tecla '8'
        case '9': 
            break; // Ação para a tecla '9'
        case '0': 
            // Liga o led RGB
            set_pwm_duty(RED_LED_RGB, 255);   // Vermelho no máximo
            set_pwm_duty(GREEN_LED_RGB, 128); // Verde em 50%
            set_pwm_duty(BLUE_LED_RGB, 64);   // Azul em 25%

            sleep_ms(500);

            set_pwm_duty(RED_LED_RGB, 50);   // Vermelho no máximo
            set_pwm_duty(GREEN_LED_RGB, 20); // Verde em 50%
            set_pwm_duty(BLUE_LED_RGB, 255);   // Azul em 25%

            sleep_ms(500);

            set_pwm_duty(RED_LED_RGB, 255);   // Vermelho no máximo
            set_pwm_duty(GREEN_LED_RGB, 128); // Verde em 50%
            set_pwm_duty(BLUE_LED_RGB, 64);   // Azul em 25%

            // gpio_put(RED_LED_RGB, 1);
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

int main() 
{
    
    stdio_init_all();
    setup_gpio();
    printf("Inicializando teclado matricial...\n");

    // Inicializa o teclado
    init_keypad(row_pins, col_pins);

    while (1) 
    {
        char key = scan_keypad(row_pins, col_pins);
        if (key != '\0') // Se uma tecla foi pressionada
        { 
            printf("Tecla pressionada: %c\n", key);
            escolher_acao(key); // Executa a ação associada
        }
    }

    return 0;
}