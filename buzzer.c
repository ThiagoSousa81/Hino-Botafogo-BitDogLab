/**
 * Exemplo de acionamento de buzzer utilizando sinal PWM no GPIO 21 da Raspberry Pico / BitDog Lab
 * 06/12/2024
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

// notas musicais
#define DO 0
#define REb 1
#define RE 2
#define MIb 3
#define MI 4
#define FA 5
#define SOLb 6
#define SOL 7
#define LAb 8
#define LA 9
#define SIb 10
#define SI 11

#define do 12
#define reb 13
#define re 14
#define mib 15
#define mi 16
#define fa 17
#define solb 18
#define sol 19
#define lab 20
#define la 21
#define sib 22
#define si 23

const float notas[24] = {
    261.625519,
    277.182648,
    293.664734,
    311.126984,
    329.627533,
    349.228241,
    369.994385,
    391.995392,
    415.304688,
    440,
    466.163788,
    493.883301,

    523.251099,
    554.365234,
    587.329529,
    622.253906,
    659.255127,
    698.456482,
    739.988831,
    783.990845,
    830.609375,
    880,
    932.327576,
    987.766602};

const char musica[] = {
    FA, FA, SIb, SIb, do, re, LA, LA,
    SIb, do, SOL, SOL, FA, SOL, SOL, FA, SOL, FA, LA, SOL,

    FA, FA, LA, LA, SIb, do, SOL, SOL,
    LA, SIb, FA, FA, do, re, do, SI, do, FA,

    FA, SOL, LA, SIb, do, re, do, SIb, SOL, SIb,
    SOL, SOL, do, re, mi, re, do, LA, do,

    FA, SIb, do, SIb, SOL, do, do,
    do, re, do, re, mib,
    mib, re, do, FA, SIb};

// Mapeando hardware
#define BUZZER_PIN 21
#define BUTTON_A_PIN 6

// Configuração da frequência do buzzer (em Hz)
#define top 65535

// Definição de uma função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin, uint slice_num)
{
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();

    pwm_init(slice_num, &config, true);

    pwm_set_gpio_level(pin, 0);
}

#define change_note(note) pwm_set_clkdiv(slice_num, clock_get_hz(clk_sys) / (notas[note] * top))

// Definição de uma função para emitir um beep com duração especificada
void beep(uint pin, uint duration_ms)
{
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048);

    // Temporização
    sleep_ms(duration_ms);

    // Desativar o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);

    // Pausa entre os beeps
    sleep_ms(100); // Pausa de 100ms
}

int main()
{
    // Inicializar o sistema de saída padrão
    stdio_init_all();

    // Inicializar o PWM no pino do buzzer
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_init_buzzer(BUZZER_PIN, slice_num);

    // configurando botao
    /*gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN,GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    */
    // CONFIGURAND JOYSTICK
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);

    unsigned long int adc_y_raw = 0;
    adc_select_input(0);
    int note = 0;

    while (true)
    {
        adc_y_raw = 0;

        while (adc_y_raw < 3000)
        {
            for (int i = 0; i < 20; i++)
            {
                adc_y_raw += adc_read();
            }
            adc_y_raw /= 20;
            printf("%u\n", adc_y_raw);
        }

        pwm_set_gpio_level(BUZZER_PIN, 500);
        change_note(musica[note]);
        note++;

        while (adc_y_raw > 3000)
        {

            for (int i = 0; i < 20; i++)
            {
                adc_y_raw += adc_read();
            }
            adc_y_raw /= 20;

            printf("%u\n", adc_y_raw);
        }
        pwm_set_gpio_level(BUZZER_PIN, 0);
    }

    int count = 0;
    // Loop infinito
    while (true)
    {
        while (gpio_get(BUTTON_A_PIN))
            ;
        printf("Apertou %d vezes\n", ++count);

        pwm_set_gpio_level(BUZZER_PIN, 500);
        change_note(musica[count]);

        sleep_ms(500);

        while (!gpio_get(BUTTON_A_PIN))
            ;
        pwm_set_gpio_level(BUZZER_PIN, 0);
    }
    return 0;
}
