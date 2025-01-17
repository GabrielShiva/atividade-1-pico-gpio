# Projeto: Controle de Dispositivos com GPIO no Raspberry Pi Pico W (EMBARCATECH/U4-ATV1)

Este projeto implementa um sistema utilizando GPIOs do Raspberry Pi Pico W para integrar e controlar um teclado matricial 4x4, um botão externo, LEDs RGB, e um buzzer. Ele é a solução para a **Atividade 1 - Unidade 4** do programa de residência da **Embarcatech**.

## Descrição do Funcionamento

- **Teclado matricial 4x4**: Cada tecla tem uma função específica para interagir com os componentes do sistema.
  - Botão `A`: Acende o LED vermelho.
  - Botão `B`: Acende o LED verde.
  - Botão `C`: Acende o LED azul.
  - Botão `D`: Acende os três LEDs simultaneamente.
  - Botão `#`: Ativa o buzzer em uma frequência de 900Hz por 2 segundos.
  - Botão `*`: Função de alternância para desativar todos os LEDs.
  
- **Botão externo**: Ao ser pressionado três vezes consecutivas, dispara uma sequência de animação nos LEDs RGB (acendendo e apagando em ordem e com atraso definido).

## Componentes Utilizados

1. **Teclado matricial 4x4**: Utilizado para controle das funções principais.
2. **Botão externo**: Atribuído a um evento especial de controle dos LEDs RGB.
3. **LEDs RGB (vermelho, verde e azul)**: Para feedback visual ao usuário.
   - Vermelho conectado ao GPIO 10.
   - Verde conectado ao GPIO 11.
   - Azul conectado ao GPIO 12.
4. **Buzzer**: Emite sons em frequências diferentes quando acionado, conectado ao GPIO 21.

## Link para Apresentação em Vídeo

O vídeo demonstrando o funcionamento do projeto pode ser acessado [aqui](#).