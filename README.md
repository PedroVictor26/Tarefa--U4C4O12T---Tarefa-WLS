# Projeto de Controle de Matriz de LEDs WS2812 com Raspberry Pi Pico

## Visão Geral

Este projeto demonstra o controle de uma matriz de LEDs WS2812 5x5 utilizando um microcontrolador Raspberry Pi Pico, combinando hardware e software para criar uma experiência interativa. O sistema exibe números de 0 a 9 na matriz, utiliza botões para interagir com o sistema e ainda pisca um LED RGB para indicar que o sistema está em execução.

## Objetivos

*   Controlar uma matriz de LEDs WS2812 (5x5) usando um Raspberry Pi Pico.
*   Exibir números de 0 a 9 na matriz, cada um com um contorno específico e representativo.
*   Permitir que o usuário navegue entre os números usando dois botões (A e B).
*   Implementar um sistema de debounce para os botões.
*   Fazer o LED vermelho do LED RGB piscar 5 vezes por segundo, indicando que o sistema está ativo.

## Hardware Necessário

*   Raspberry Pi Pico (ou Pico W)
*   Matriz de LEDs WS2812 (5x5)
*   LED RGB
*   2 botões de pressão
*   Resistores para pull-up (opcional, usar pull-up interno da placa)
*   Fios para conexão e protoboard

## Software Necessário

*   Pico SDK (versão 2.1.0 ou superior)
*   Toolchain para Raspberry Pi Pico
*   Editor de código (VS Code com extensão Pico, ou qualquer outro)
*   CMake (opcional)
*   Ninja (opcional)

## Arquivos do Projeto

*   `main.c`: Arquivo principal do projeto, contendo a lógica para controle dos LEDs, botões e a matriz.
*   `ws2812.pio.h`: Define as funções necessárias para controlar os LEDs WS2812 utilizando o PIO (Programmable I/O).
*  `CMakeLists.txt`:  Arquivo de configuração do CMake para compilação do projeto.
