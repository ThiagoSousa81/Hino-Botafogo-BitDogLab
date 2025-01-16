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

const int tempos_off[] = {
194314,
193271,
212358,
216686,
218190,
250482,
215839,
220852,
219293,
258888,
277035,
167749,
181921,
262126,
190068,
156896,
167814,
155907,
183453,
241263,
182624,
165687,
209273,
208070,
228435,
219001,
220944,
252194,
243330,
255024,
212375,
181504,
149064,
153086,
154220,
169555,
224882,
145369,
187233,
204307,
245571,
246397,
200709,
198183,
155901,
158117,
176260,
221173,
120782,
208998,
230035,
216509,
206067,
156892,
148523,
173262,
249148,
223286,
217373,
162159,
134691,
174012,
197735,
205494,
163483,
127238,
145798,
178325,
245787,
182936,
129484,
155288,
184928,
0,
};
const int tempos_on[] = {
100055,
100005,
356402,
294792,
320747,
305048,
355481,
320853,
308782,
309847,
278868,
100005,
100005,
253820,
100005,
100005,
100005,
100005,
100005,
600791,
100006,
100005,
361438,
337487,
334709,
306064,
342731,
311295,
293245,
286705,
642123,
100005,
100005,
100005,
100004,
100005,
353855,
100004,
100005,
344333,
283075,
845394,
308885,
325317,
100005,
100005,
100004,
590775,
100005,
100005,
839234,
308214,
313848,
100005,
100005,
100005,
584835,
317832,
832255,
100005,
100005,
100004,
335705,
300653,
100005,
100004,
100005,
100005,
738570,
104106,
100005,
100005,
100005,
1373966,
};
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

// funcao para gravar os tempos de cada nota (e o espaço entre elas também)
void gravar(int* tempos_off,int* tempos_on, uint slice_num){
    uint32_t t1 = 0;
    uint32_t t0 = 0;
    for (int count = 0; count < 74; count++)
    {

        while (gpio_get(BUTTON_A_PIN)) // butao em pull up
        {
        }

        t0 = time_us_32();
        tempos_off[count] = t0 - t1;

        pwm_set_gpio_level(BUZZER_PIN, 500);
        change_note(musica[count]);

        sleep_ms(100);

        while (!gpio_get(BUTTON_A_PIN))
        {
        }
        t1 = time_us_32();

        tempos_on[count] = t1 - t0;
        // printf("%d,", time);

        pwm_set_gpio_level(BUZZER_PIN, 0);
        sleep_ms(100);
    }


    // Printando dados na serial se quiser reutilizar vvvvvvvvv
    printf("const int tempos_off[] = {\n");
    for (int i = 0; i < 74; i++)
    {
        printf("%d,\n", tempos_off[i + 1]);
    }
    printf("}\n");

    printf("const int tempos_on[] = {\n");
    for (int i = 0; i < 74; i++)
    {
        printf("%d,\n", tempos_on[i]);
    }
    printf("}\n");

}


int main()
{
    // Inicializar o sistema de saída padrão
    stdio_init_all();

    // Inicializar o PWM no pino do buzzer
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_init_buzzer(BUZZER_PIN, slice_num);

    // configurando botao
    //*
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
   
   
    sleep_ms(1000); //pausinha dramática

    for (int i = 0; i < 74; i++)
    {
        pwm_set_gpio_level(BUZZER_PIN, 500);
        change_note(musica[i]);
        sleep_us(tempos_on[i]);

        pwm_set_gpio_level(BUZZER_PIN, 0);
        sleep_us(tempos_off[i]);
    }
    pwm_set_gpio_level(BUZZER_PIN, 0);

   
    while (true)
        ;
    return 0;
}
