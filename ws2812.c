#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define LED_RED 11
#define LED_GREEN 12
#define LED_BLUE 13
#define BUTTON_A 5
#define BUTTON_B 6

// Variáveis globais
uint8_t display_value = 0;
uint32_t last_button_a_press = 0;
uint32_t last_button_b_press = 0;
const uint32_t debounce_delay_ms = 200;
bool led_state = false;

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

uint32_t led_buffer[NUM_PIXELS] = {0}; // Buffer para armazenar as cores de todos os LEDs

// Padrão de contorno para cada numero
double desenho_numeros[10][NUM_PIXELS] = {
    {0, 1, 1, 1, 0,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     0, 1, 1, 1, 0}, // 0

    {0, 1, 1, 1, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 1, 1, 0, 0,
     0, 0, 1, 0, 0}, // 1

    {0, 1, 1, 1, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0}, // 2

    {0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0}, // 3

    {0, 1, 0, 0, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 0, 1, 0}, // 4

    {0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 0, 0,
     0, 1, 1, 1, 0}, // 5

    {0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0}, // 6

    {0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0}, // 7

    {0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0}, // 8

    {0, 1, 1, 1, 0,
     0, 0, 0, 1, 0,
     0, 1, 1, 1, 0,
     0, 1, 0, 1, 0,
     0, 1, 1, 1, 0}  // 9
};
// Função para criar efeitos na matriz (ex: números)
void update_led_buffer(uint8_t value)
{
    // Apaga todos os LEDs
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        led_buffer[i] = 0;
    }

    uint8_t r, g, b;
    r = 0;
    g = 255;
    b = 0; // Verde

    // Aplica o padrão de contorno para cada número
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho_numeros[value][i] == 1)
        {
            led_buffer[i] = urgb_u32(r, g, b);
        }
    }
}

void set_leds_from_buffer()
{
    // Envia o estado de todos os LEDs para a matriz
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        put_pixel(led_buffer[i]);
    }
}

// Função para lidar com a pressão do botão A
void handle_button_a()
{
    uint32_t now = to_ms_since_boot(get_absolute_time());
    if (now - last_button_a_press > debounce_delay_ms)
    {
        display_value = (display_value + 1) % 10;
        update_led_buffer(display_value);
        set_leds_from_buffer();
        last_button_a_press = now;
    }
}

// Função para lidar com a pressão do botão B
void handle_button_b()
{
    uint32_t now = to_ms_since_boot(get_absolute_time());
    if (now - last_button_b_press > debounce_delay_ms)
    {
        display_value = (display_value == 0) ? 9 : display_value - 1;
        update_led_buffer(display_value);
        set_leds_from_buffer();
        last_button_b_press = now;
    }
}

int main()
{
    stdio_init_all();
    printf("WS2812 5x5 Matrix - Single LED Control\n");

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    // Inicializar os pinos GPIO
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    update_led_buffer(display_value);
    set_leds_from_buffer();

    while (1)
    {
        // Pisca o LED vermelho
        led_state = !led_state;
        gpio_put(LED_RED, led_state);
        sleep_ms(100); // Delay para criar um pisca-pisca de 5 vezes por segundo.

        if (gpio_get(BUTTON_A) == 0)
        {
            handle_button_a();
        }

        if (gpio_get(BUTTON_B) == 0)
        {
            handle_button_b();
        }
    }

    return 0;
}