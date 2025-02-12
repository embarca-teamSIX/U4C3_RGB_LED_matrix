# Instruções de Funcionamento

Este projeto implementa um sistema interativo utilizando o Raspberry Pi Pico, controlando uma matriz de LEDs RGB 5x5, um buzzer e um teclado matricial. O objetivo é realizar animações, interações com o usuário e emitir sons conforme a entrada do teclado.

## Hardware Necessário

- **Raspberry Pi Pico**
- **Teclado matricial 4x4**
- **Matriz de LEDs RGB 5x5**
- **Buzzer A e B**

## Descrição do Funcionamento

O programa realiza as seguintes funcionalidades principais:

1. **Configuração do Teclado**: O teclado matricial 4x4 captura a entrada do usuário. Cada tecla pressionada aciona uma ação específica no sistema.

2. **Animações com a Matriz de LEDs RGB 5x5**: 
   - A matriz de LEDs RGB 5x5 é controlada pelo PIO (Programmable Input/Output) do Raspberry Pi Pico para exibir animações coloridas.
   - As animações incluem corações pulsantes, setas em movimento, explosões e reconstrução de formas, usando as cores disponíveis na matriz (vermelho, verde, azul, etc.).

3. **Emissão de Sons**:
   - Sons são emitidos através de dois buzzers (A e B), que são ativados durante as animações.
   - A animação e o som são sincronizados, proporcionando uma resposta interativa ao usuário.

4. **Funções de Controle**:
   - **Tecla '1'**: Exibe uma animação de uma seta que se move pela matriz de LEDs.
   - **Tecla '2'**: Exibe animação de coração pulsante com som, seguida de explosão e reconstrução do coração.
   - **Tecla '3'**: [Ação a ser definida]
   - **Tecla '4'**: [Ação a ser definida]
   - **Tecla '5'**: Exibição de bandeira Experimental para teste de cores e RGB do led
   - **Tecla '6'**: [Ação a ser definida]
   - **Tecla '7'**: [Ação a ser definida]
   - **Tecla '8'**: [Ação a ser definida]
   - **Tecla '9'**: [Ação a ser definida]
   - **Tecla '0'**: Animação com a variação de um rosto triste pra um rosto feliz.
   - **Tecla 'A'**: Desliga todos os LEDs e sons.
   - **Tecla 'B'**: Liga todos os LEDs em azul com brilho de 100%.
   - **Tecla 'C'**: Liga todos os LEDs em vermelho com brilho de 80%.
   - **Tecla 'D'**: Liga todos os LEDs em verde com brilho de 50%.
   - **Tecla '#'**: Liga todos os LEDs com brilho de 20%.
   - **Tecla '*'**: Entra em modo de bootloader.

## Como Usar

1. **Conecte o hardware**: 
   - Conecte o teclado matricial, a matriz de LEDs RGB 5x5 e os buzzers ao Raspberry Pi Pico conforme o código.
   
2. **Inicie o programa**: 
   - Ao executar o código, o sistema estará pronto para interagir.
   - Pressione qualquer tecla do teclado para ver a ação correspondente.

## Link do vídeo - Apresentação da tarefa
- https://youtu.be/1xzIMVtQOTQ

## Considerações

- A leitura do teclado pode ser afetada por "debounce", garantindo que múltiplas leituras da mesma tecla não sejam feitas em rápida sucessão.
- As animações são renderizadas no PIO (Programmable Input/Output) para otimizar a performance do Raspberry Pi Pico, permitindo um controle eficiente da matriz de LEDs RGB 5x5.

