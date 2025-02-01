# Tarefa--U4C4O12T---Tarefa-WLS

## Descrição do Código
main.c: 
O arquivo principal contém a lógica do programa:

Inicialização: 
Configura o GPIO, PIO e a comunicação serial.

Loop Principal:

Pisca o LED vermelho a 5Hz.

Verifica os botões e chama as funções de debounce.

update_led_buffer(value): Desenha o número especificado com o padrão definido na matriz desenho_numeros.

set_leds_from_buffer(): Envia os dados para a matriz de LEDs WS2812.

handle_button_a() e handle_button_b(): Funções para debounce e para incremento e decremento do display_value, chamando as funções para atualizar o display.

ws2812.pio.h: Define as macros e funções necessárias para controlar os LEDs WS2812 utilizando o PIO.

CMakeLists.txt: Arquivo para o processo de compilação do CMake, onde é especificado o arquivo principal, bibliotecas e funções.

A biblioteca PIO é utilizada para controlar a matriz de LEDs WS2812 de forma eficiente.

O debounce dos botões foi implementado através de delays utilizando a função to_ms_since_boot().

O padrão de contorno para cada número está definido na matriz desenho_numeros.
