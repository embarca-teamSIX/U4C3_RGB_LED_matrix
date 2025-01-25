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

#include "include/keypad.h"
#include "include/animacao_seta_jorge.h"

//arquivo .pio
#include "pio_matrix.pio.h"

//número de LEDs
#define NUM_PIXELS 25

//pino de saída
#define OUT_PIN 7

// Define os pinos do teclado
uint8_t row_pins[ROWS] = {16, 17, 18, 19};
uint8_t col_pins[COLS] = {20, 4, 9, 8};

PIO pio = pio0; 
bool ok;
uint16_t i;
uint32_t valor_led;
double r = 0.0, b = 0.0 , g = 0.0;
uint sm = 0;

double ligar_todos_os_leds[25] =   {1.0, 1.0, 1.0, 1.0, 1.0,
                            1.0, 1.0, 1.0, 1.0, 1.0, 
                            1.0, 1.0, 1.0, 1.0, 1.0,
                            1.0, 1.0, 1.0, 1.0, 1.0,
                            1.0, 1.0, 1.0, 1.0, 1.0};

                            //vetor para criar imagem na matriz de led - 1
double desliga_tudo[25] =   {0.0, 0.0, 0.0, 0.0, 0.0,
                            0.0, 0.0, 0.0, 0.0, 0.0, 
                            0.0, 0.0, 0.0, 0.0, 0.0,
                            0.0, 0.0, 0.0, 0.0, 0.0,
                            0.0, 0.0, 0.0, 0.0, 0.0};


//imprimir valor binário
void imprimir_binario(int num) {
 int i;
 for (i = 31; i >= 0; i--) {
  (num & (1 << i)) ? printf("1") : printf("0");
 }
}

//rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(desenho[24-i], desenho[24-i], desenho[24-i]);
        pio_sm_put_blocking(pio, sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void escolher_acao(char key) 
{
    switch (key) 
    {
        case '1':
            for(int i = 0; i < 2; i++)
            {
                desenho_pio(seta_1, valor_led, pio, sm);
                sleep_ms(300);
                desenho_pio(seta_2, valor_led, pio, sm);
                sleep_ms(300);
                desenho_pio(seta_3, valor_led, pio, sm);
                sleep_ms(300);
                desenho_pio(seta_4, valor_led, pio, sm);
                sleep_ms(300);
                desenho_pio(seta_5, valor_led, pio, sm);
                sleep_ms(300);
                desenho_pio(seta_6, valor_led, pio, sm);
                sleep_ms(300);
                desenho_pio(seta_7, valor_led, pio, sm);
                sleep_ms(300);
            } 
            desenho_pio(desliga_tudo, valor_led, pio, sm); 
            break; 
        case '2': 
            break;
        case '3': 
            break;
        case '4': 
            break;
        case '5': 
            break;
        case '6': 
            break;
        case '7': 
            break;
        case '8': 
            desenho_pio(ligar_todos_os_leds, valor_led, pio, sm);
            break;
        case '9':
            break;
        case '0':  
            break;
        case 'A': 
            desenho_pio(desliga_tudo, valor_led, pio, sm); 
            break;
        case 'B': 
            break;
        case 'C': 
            break;
        case 'D': 
            break;
        case '*': 
            break;
        case '#': 
            break;
        default: 
            desenho_pio(desliga_tudo, valor_led, pio, sm);
            break; // Ação padrão para qualquer outra tecla
    }
}

//função principal
int main()
{
    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

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