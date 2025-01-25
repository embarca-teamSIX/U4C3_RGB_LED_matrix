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

//arquivo .pio
#include "pio_matrix.pio.h"

#include "include/coracao_pulsante_Deividson.h"

//número de LEDs
#define NUM_PIXELS 25

//pino de saída
#define OUT_PIN 7

#define BUZZER_A_PIN 10
#define BUZZER_B_PIN 21

// Define os pinos do teclado
uint8_t row_pins[ROWS] = {16, 17, 18, 19};
uint8_t col_pins[COLS] = {20, 4, 9, 8};

PIO pio = pio0; 
bool ok;
uint16_t i;
uint32_t valor_led;
double r = 0.0, b = 0.0 , g = 0.0;
uint sm = 0;

double ligar_todos_os_leds_20[25] =   {0.2, 0.2, 0.2, 0.2, 0.2,
                                        0.2, 0.2, 0.2, 0.2, 0.2, 
                                        0.2, 0.2, 0.2, 0.2, 0.2,
                                        0.2, 0.2, 0.2, 0.2, 0.2,
                                        0.2, 0.2, 0.2, 0.2, 0.2};



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
//--------------------------------------------------
//funções comunidade aqui
/**
 * @brief função tocar e anmar bandeira americana
 *
 * @note função que funciona sendo chamada e sem demais interações
 *
 * @usage
 * ```
 * ```
 *
 * @details Função que chamara funções que gerarão o led na amtriz e tocar buzzer
 *             
 */
void star_spangled_gleison()
{

}
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(desenho[24-i], desenho[24-i], desenho[24-i]);
        pio_sm_put_blocking(pio, sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

// Função para tocar um tom específico no buzzer
void tocar_tom_buzzer(uint16_t frequency, uint duration_ms) {
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

// Função para tocar o som simulando pulsação
void tocar_pulsacao() {
    tocar_tom_buzzer(440, 200); // Primeiro batimento: frequência 440 Hz, duração 200ms
    sleep_ms(100);              // Pausa curta entre batimentos
    tocar_tom_buzzer(440, 400); // Segundo batimento: frequência 440 Hz, duração 400ms
    sleep_ms(300);              // Pausa antes do próximo ciclo
}

// Função para desenhar um frame na matriz de LEDs com intensidade no canal vermelho
void desenho_pio_vermelho(double *desenho, uint32_t valor_led, PIO pio, uint sm) {
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, desenho[24 - i], 0.0); // Corrigido para usar o canal vermelho corretamente
        pio_sm_put_blocking(pio, sm, valor_led);
    }
    printf("Frame desenhado na matriz de LEDs com cor vermelha.\n");
}

// Função do coração pulsante com som
void coracao_pulsante_com_som_vermelho() {
    // Define os dois frames do coração
    double *frames[] = {coracao_alto, coracao_medio};
    int delays[] = {300, 300}; // Tempo de exibição de cada frame

    for (int i = 0; i < 6; i++) { // Aumenta o número de ciclos de pulsação
        desenho_pio_vermelho(frames[i % 2], valor_led, pio, sm); // Alterna entre os dois frames

        if (i % 2 == 0) { // Sincroniza o som no frame de alta intensidade (batimento principal)
            tocar_pulsacao();
        }

        sleep_ms(delays[i % 2]); // Espera antes de mudar para o próximo frame
    }
}




void desenho_pio_azul_100(uint32_t valor_led, PIO pio, uint sm){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(1.0, 0.0, 0.0);
        pio_sm_put_blocking(pio, sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void desenho_pio_vermelho_80(uint32_t valor_led, PIO pio, uint sm){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, 0.8, 0.0);
        pio_sm_put_blocking(pio, sm, valor_led);
        //imprimir_binario(valor_led);
    }
    printf("clock set to %ld\n", clock_get_hz(clk_sys));
}

void desenho_pio_verde_50(uint32_t valor_led, PIO pio, uint sm){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, 0.0, 0.5);
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
        coracao_pulsante_com_som_vermelho();
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
            desenho_pio(desliga_tudo, valor_led, pio, sm); 
            break;
        case 'B':
            desenho_pio_azul_100(valor_led, pio, sm); 
            break;
        case 'C':
            desenho_pio_vermelho_80(valor_led, pio, sm); 
            break;
        case 'D':
            desenho_pio_verde_50(valor_led, pio, sm); 
            break;
        case '*': 
            break;
        case '#':
            desenho_pio(ligar_todos_os_leds_20, valor_led, pio, sm); 
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

    // Configura os pinos do buzzer  Bcomo saída
    gpio_init(BUZZER_B_PIN);
    gpio_set_dir(BUZZER_B_PIN, GPIO_OUT);

    // Configura os pinos do buzzer A como saída
    gpio_init(BUZZER_A_PIN);
    gpio_set_dir(BUZZER_A_PIN, GPIO_OUT);



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