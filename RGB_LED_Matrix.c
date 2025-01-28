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
#include "pico/bootrom.h"  //
#include "hardware/flash.h"
#include "hardware/structs/systick.h"  // Necessário para a função de reset no SDK do Pico

#include "include/keypad.h"
#include "include/animacao_seta_jorge.h"
#include "pride_of_flag.h"
//arquivo .pio
#include "pio_matrix.pio.h"

// #include "include/coracao_pulsante_Deividson.h"
#include "include/matriz_led_control.h"
#include "include/coracao_pulsante_Deividson.h"
#include "include/buzzer.h"

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
void init_pio_routine(pio_t * meu_pio)
{
    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    meu_pio->ok = set_sys_clock_khz(128000, false);

    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (meu_pio->ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configurações da PIO
    uint offset = pio_add_program(meu_pio->pio, &pio_matrix_program);
    meu_pio->sm = pio_claim_unused_sm(meu_pio->pio, true);
    pio_matrix_program_init(meu_pio->pio, meu_pio->sm, offset, OUT_PIN);
}
//rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (R << 24) | (G << 16) | (B << 8)|0xFF;
}

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
void coracao_pulsante_com_som_vermelho(pio_t *meu_pio) {
    for (int i = 0; i < 3; i++) {
        desenho_pio_vermelho(coracao_alto, meu_pio);
        tocar_pulsacao();
        sleep_ms(300);
        desenho_pio_vermelho(coracao_medio, meu_pio);
        sleep_ms(300);
    }

    desenho_pio_vermelho(explosao_frame1, meu_pio);
    tocar_explosao();
    sleep_ms(300);
    desenho_pio_vermelho(explosao_frame2, meu_pio);
    sleep_ms(300);
    desenho_pio_vermelho(explosao_frame3, meu_pio);
    sleep_ms(300);

    desenho_pio_vermelho(restauracao_frame1, meu_pio);
    tocar_restauracao();
    sleep_ms(300);
    desenho_pio_vermelho(restauracao_frame2, meu_pio);
    sleep_ms(300);
    desenho_pio_vermelho(restauracao_frame3, meu_pio);
    sleep_ms(300);
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
        coracao_pulsante_com_som_vermelho(&meu_pio);

        // coracao_pulsante_com_som_vermelho();
            break;
        case '3': 
            break;
        case '4': 
            break;
        case '5': //função de gleison
                 // Ação para a tecla '5'
                star_spangled_gleison(& meu_pio);
            break; 
                  
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
        case '*': //bootloader
            entrarModoBootloader();
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
    init_pio_routine(&meu_pio);
    
    // Configura os pinos do buzzer  Bcomo saída
    gpio_init(BUZZER_B_PIN);
    gpio_set_dir(BUZZER_B_PIN, GPIO_OUT);

    // Configura os pinos do buzzer A como saída
    gpio_init(BUZZER_A_PIN);
    gpio_set_dir(BUZZER_A_PIN, GPIO_OUT);

    // Inicializa o teclado
    init_keypad(row_pins, col_pins);
/*
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
*/
while(true)
{
    ligar_todos_os_leds_20_p(&meu_pio); 
    sleep_ms(300); 
    desliga_tudo(&meu_pio);
    sleep_ms(600); 
    star_spangled_gleison(&meu_pio);
    
    sleep_ms(30000); 
    desliga_tudo(&meu_pio);
    entrarModoBootloader();
}
    return 0;
}