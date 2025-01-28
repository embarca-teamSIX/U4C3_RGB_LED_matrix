#include "matriz_led_control.h"
#include "pride_of_flag.h"
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/structs/systick.h"  // Necessário para a função de reset no SDK do Pico
#include "pico/bootrom.h"  //
#include <stdio.h>
// #include "buzzer_functions.h"
#define NUM_PIXELS 25



//imprimir valor binário
void imprimir_binario(int num) 
{
 int i;
 for (i = 31; i >= 0; i--) {
  (num & (1 << i)) ? printf("1") : printf("0");
 }
}



void desenho_pio(double *desenho, pio_t * meu_pio)
{
    uint32_t valor_led = 0;

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(desenho[24-i], desenho[24-i], desenho[24-i]);
        pio_sm_put_blocking(meu_pio->pio, meu_pio->sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void desenho_pio_vermelho(double *desenho, pio_t * meu_pio) 
{
    uint32_t valor_led = 0;

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, desenho[24 - i], 0.0); // Corrigido para usar o canal vermelho corretamente
        pio_sm_put_blocking(meu_pio->pio, meu_pio->sm, valor_led);
    }
    printf("Frame desenhado na matriz de LEDs com cor vermelha.\n");
}

void desenho_pio_azul_100(pio_t * meu_pio)
{
    uint32_t valor_led = 0;

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(1.0, 0.0, 0.0);
        pio_sm_put_blocking(meu_pio->pio, meu_pio->sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void desenho_pio_vermelho_80(pio_t * meu_pio)
{
    uint32_t valor_led = 0;

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, 0.8, 0.0);
        pio_sm_put_blocking(meu_pio->pio, meu_pio->sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void desenho_pio_verde_50(pio_t * meu_pio)
{
    uint32_t valor_led = 0;

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, 0.0, 0.5);
        pio_sm_put_blocking(meu_pio->pio, meu_pio->sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void ligar_todos_os_leds_20_p(pio_t * meu_pio)
{
    uint32_t valor_led = 0;
    double ligar_todos_os_leds_20[25] =   {0.2, 0.2, 0.2, 0.2, 0.2,
                                        0.2, 0.2, 0.2, 0.2, 0.2, 
                                        0.2, 0.2, 0.2, 0.2, 0.2,
                                        0.2, 0.2, 0.2, 0.2, 0.2,
                                        0.2, 0.2, 0.2, 0.2, 0.2};

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(ligar_todos_os_leds_20[24-i], ligar_todos_os_leds_20[24-i], ligar_todos_os_leds_20[24-i]);
        pio_sm_put_blocking(meu_pio->pio, meu_pio->sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void desliga_tudo(pio_t * meu_pio)
{
    uint32_t valor_led = 0;

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, 0.0, 0.0);
        pio_sm_put_blocking(meu_pio->pio, meu_pio->sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void entrarModoBootloader() {

    tocar_tom_buzzer(1000, 200); 
    sleep_ms(100);              
    tocar_tom_buzzer(1500, 200); 
    sleep_ms(100);               
    tocar_tom_buzzer(2000, 300);
    sleep_ms(100);               
    tocar_tom_buzzer(1000, 200);
    sleep_ms(50);                
    tocar_tom_buzzer(1500, 200); 
    sleep_ms(50);                
    tocar_tom_buzzer(2000, 400);
    reset_usb_boot(0, 0); // Reinicia no modo bootloader
}
//desenho pio
void desenho_pioFlag(double (*flagB)[25],double (*flagG)[25],double (*flagR)[25], pio_t *meu_pio)
{
    uint32_t valor_led = 0;
    int frames=10;
    tocar_tom_buzzer(1000, 200); 
    sleep_ms(100);              

    for(int j=0; j<frames; j++)
    {//frames ou linhas
        for (int i = 0; i < NUM_PIXELS; i++) //laço pixels ou colnas
        {
            valor_led = matrix_rgb(flagB[j][i], flagR[j][i], flagG[j][i]);
            pio_sm_put_blocking(pio0, 0, valor_led);
            //desliga_tudo(&meu_pio)
            //imprimir_binario(valor_led);
            printf("\n**********\nvalor led: %lu\nvalor j: %d\n valor i: %d\n\n-------------------\n flagB: %f\n flagF: %f\nflagG: %f \n\n*********", valor_led, j, i, flagB[j][i], flagR[j][i], flagG[j][i]);
        }
        sleep_ms(50);
    }
}
void star_spangled_gleison(pio_t *meu_pio)
{
desenho_pioFlag(flagB, flagG, flagR, &meu_pio);
}


