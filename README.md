# Projeto: Controle de Dispositivos com GPIO no Raspberry Pi Pico W (EMBARCATECH/U4-ATV1)

Este projeto implementa um sistema utilizando GPIOs do Raspberry Pi Pico W para integrar e controlar um teclado matricial 4x4, um botão externo, LEDs RGB, e um buzzer. Ele é a solução para a **Atividade 1 - Unidade 4** do programa de residência da **Embarcatech**.

---

## 📜 **Descrição do Funcionamento**

A tabela abaixo descreve os comandos implementados e suas funcionalidades planejadas:

| **Comando**                  | **Descrição**                                                                | **Responsável**    |
|------------------------------|----------------------------------------------------------------------------|--------------------|
| **Pressionar Tecla D**       | Liga os três LEDs ao mesmo tempo.                                           | Pedro Duarte       |
| **Pressionar Tecla * (5x)**  | O buzzer toca 5 vezes e os LEDs acendem todos juntos.                       | Bruna              |
| **Pressionar Botão Push-Up (3x)** | Ao ser pressionado três vezes consecutivas, o buzzer emite um som três vezes consecutivas. | Gabriel Shiva      |
| **Pressionar Tecla A**       | Liga o LED vermelho.                                                        | Ícaro              |
| **Pressionar Tecla B**       | Liga o LED verde.                                                           | Ícaro              |
| **Pressionar Tecla C**       | Liga o LED azul.                                                            | Ícaro              |
| **Pressionar Tecla 9**       | Os LEDs piscam na sequência de um semáforo (o LED azul atua como o LED amarelo). | Reinan          |
| **Pressionar Tecla 6**       | O LED azul pisca em um padrão Morse para o código "SOS".                    | Samyr              |

---

## 🔌 **Conexão de Componentes**

Os pinos configurados no programa são:

- **LED Vermelho**: GPIO 10  
- **LED Verde**: GPIO 11  
- **LED Azul**: GPIO 12  
- **Buzzer**: GPIO 21  
- **Botão Push-Up**: GPIO 28  
- **Teclado Matricial**:  
  - *Linhas*: GPIOs 1, 2, 3 e 4  
  - *Colunas*: GPIOs 5, 6, 7 e 8  

---

## 🔧 **Como Usar**

1. **Configuração do Ambiente**:  
   - Instale as extensões:  
     - `Raspberry Pi Pico W`  
     - `CMake`  
     - `Wokwi Simulator`  
   - Na IDE **VSCode**, clone o repositório para sua máquina utilizando o comando:  
     ```bash
     git clone -b main https://github.com/GabrielShiva/atividade-1-pico-gpio.git
     ```

2. **Execução do Programa**:  
   - Realize a compilação do projeto;  
   - Abra o arquivo `diagram.json` e clique no botão verde (*executar*);  
   - Alternativamente, acesse o código disponível no **Wokwi Web** [clicando aqui](#).  

---

## 🎥 **Apresentação em Vídeo**

O vídeo demonstrando o funcionamento do projeto pode ser acessado [clicando aqui](#).

---
