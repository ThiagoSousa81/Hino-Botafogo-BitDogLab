/**
 * Exemplo de acionamento de buzzer utilizando sinal PWM no GPIO 21 da Raspberry Pico / BitDog Lab
 * 06/12/2024
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "inc/musica.h"

#include "inc/ssd1306.h"
#include "inc/bitmap_botafogo.h"    
#include <string.h>
// notas musicais

// Mapeando hardware
#define BUZZER_PIN 21
#define BUTTON_A_PIN 6

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;
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


    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);





    // Inicializar o PWM no pino do buzzer
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_init_buzzer(BUZZER_PIN, slice_num);

    // configurando botao
    //*
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
   
    

    // desenhando escudo botafogo:
    ssd1306_t ssd_bm;
    ssd1306_init_bm(&ssd_bm, 128, 64, false, 0x3C, i2c1);
    ssd1306_config(&ssd_bm);

    ssd1306_draw_bitmap(&ssd_bm, bitmap_botafogo);

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
