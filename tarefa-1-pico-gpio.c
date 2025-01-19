#include <stdio.h>
#include "pico/stdlib.h"

/**
* R1 -> GP1
* R2 -> GP2
* R3 -> GP3
* R4 -> GP4
* C1 -> GP5
* C2 -> GP6
* C3 -> GP7
* C4 -> GP8
*/

#define HIGH_LEVEL 1
#define LOW_LEVEL 0
#define NO_KEY_PRESSED 0

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

#define BTN_PIN 28
#define BUZZER_PIN 21

// definindo os LEDs
#define LED_RED 10
#define LED_GREEM 11
#define LED_BLUE 12

// PROTÓTIPOS DE FUNÇÕES
void ligar_semaforo(void); // Ativa os leds na sequência do semáforo
void sos_morse_code(void); // Executa código morse
void ponto(void); // Função que implementa ponto(.) do código morse
void traco(void); // Função que implementa traço(-) do código morse
void acender_leds(void); // Função que acende todos os leds
void apagar_leds(void); // Função que apaga todos os leds
void asterisco_led_buzzer(char key); // Função que implementa a lógica do asterisco
void keypad_init(); // Inicializa teclado matricial
char keypad_read(); // Leitura do teclado matricial
void btn_init(); // Inicializa botão vermelho
void led_init(); // Inicializa os LEDs
void buzzer_init(); // Inicializa o Buzzer
void buzzer_active(uint32_t buzzer_frequency, uint32_t duration_buzzer_on); // Ativa o buzzer (emissão sonora)

const uint8_t row_pins[KEYPAD_ROWS] = {1, 2, 3, 4};
const uint8_t col_pins[KEYPAD_COLS] = {5, 6, 7, 8};
const uint32_t buzzer_frequency = 300;

uint8_t btn_counter;
uint8_t keypad_key_counter;

const char key_map[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

int main() {
    btn_counter = 0;
    keypad_key_counter = 0;

    stdio_init_all();

    keypad_init();
    btn_init();
    buzzer_init();
    led_init();

    while (true) {
        char key = keypad_read();

        if (key == 'A') {
            // o botao A do teclado é pressionado, led vermelho é aceso 

            printf("ROTINA ATIVA: LED VERMELHO ACESO!\n");
            gpio_put(LED_RED, 1); 
            gpio_put(LED_GREEM, 0); 
            gpio_put(LED_BLUE, 0); 
        } else if (key == 'B') {
            // o botao B do teclado é pressionado, led verde é aceso 

            printf("ROTINA ATIVA: LED VERDE ACESO!\n");
            gpio_put(LED_RED, 0); 
            gpio_put(LED_GREEM, 1); 
            gpio_put(LED_BLUE, 0); 
        } else if (key == 'C') {
            // o botao C do teclado é pressionado, led azul é aceso 

            printf("ROTINA ATIVA: LED AZUL ACESO!\n");
            gpio_put(LED_RED, 0); 
            gpio_put(LED_GREEM, 0); 
            gpio_put(LED_BLUE, 1); 
        } else if (key == 'D') {
            // o botao D do teclado é pressionado, os três leds são acesos

            printf("ROTINA ATIVA: TRES LEDS ACESOS!\n");
            gpio_put(LED_RED, 1); 
            gpio_put(LED_GREEM, 1); 
            gpio_put(LED_BLUE, 1);
        } else if (!gpio_get(BTN_PIN) && key == NO_KEY_PRESSED) {
            // Quando o botão externo for pressionado três vezes, o buzzer é ativado com uma frequência de 900Hz
            btn_counter = btn_counter + 1;
            printf("TECLA PRESSIONADA: %c\n", key);
            printf("Nº DE CLICKS: %d\n", btn_counter);

            if (btn_counter == 3) {
                printf("ROTINA ATIVA: BUZZER EMITE SOM!\n");

                buzzer_active(buzzer_frequency, 500);
                sleep_ms(200);
                buzzer_active(buzzer_frequency, 500);
                sleep_ms(200);
                buzzer_active(buzzer_frequency, 500);

                btn_counter = 0;
                printf("ROTINA FINALIZADA: BUZZER EMITE SOM!\n");
            }
        } else if (key == '6') {
            // Quando o botão 6 for pressionado, o LED azul pisca em um padrão morse para o código "SOS"

            printf("ROTINA ATIVA: CODIGO MORSE LED AZUL!\n");
            sos_morse_code();
        } else if (key == '9') {
            // Quando o botão 9 for pressionado, o semáforo é ativado

            printf("ROTINA ATIVA: LEDS PISCAM EM SEQUENCIA!\n");
            ligar_semaforo();
        } else if (key == '*') {
             // codigo (5) aqui
            // Após 5 pressões consecutivas do '*', o buzzer toca 5 vezes e os LEDs acendem todos juntos para indicar que o contador 
            //atingiu o número 5. O contador é então zerado.
            asterisco_led_buzzer(key);
        } else {
            // Desligando todos os PINS caso nenhuma tecla esteja ativada
            gpio_put(LED_RED, 0); 
            gpio_put(LED_GREEM, 0); 
            gpio_put(LED_BLUE, 0);
        }

        if ((key != NO_KEY_PRESSED && key != '*') || (!gpio_get(BTN_PIN))) { 
            // Zerar contador caso outra tecla/botão vermelho seja pressionada(o) quando está no meio da contagem da tecla *
            keypad_key_counter = 0;
        }

        if (key != NO_KEY_PRESSED && gpio_get(BTN_PIN)) { 
            // Zerar contador caso outra tecla seja pressionada quando está no meio da contagem do botão vermelho
            btn_counter = 0;
        }

        sleep_ms(100);
    }

    return 0;
}

void keypad_init() {
  for (uint8_t i = 0; i < KEYPAD_ROWS; i++) {
    gpio_init(row_pins[i]);
    gpio_set_dir(row_pins[i], GPIO_OUT);
    gpio_put(row_pins[i], LOW_LEVEL);
  }

  for (uint8_t j = 0; j < KEYPAD_COLS; j++) {
    gpio_init(col_pins[j]);
    gpio_set_dir(col_pins[j], GPIO_IN);
    gpio_pull_down(col_pins[j]);
  }
}

char keypad_read() {
  for (uint8_t i = 0; i < KEYPAD_ROWS; i++) {
    gpio_put(row_pins[i], HIGH_LEVEL);

    for (uint8_t j = 0; j < KEYPAD_COLS; j++) {
      if (gpio_get(col_pins[j]) == HIGH_LEVEL) {
        sleep_ms(50);
        gpio_put(row_pins[i], LOW_LEVEL);

        return key_map[i][j];
      }
    }

    gpio_put(row_pins[i], LOW_LEVEL);
  }

  return NO_KEY_PRESSED;
}

void btn_init() {
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);
}

void buzzer_init() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void led_init(){
    // configuração inicial dos LEDs

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0); 

    gpio_init(LED_GREEM);
    gpio_set_dir(LED_GREEM, GPIO_OUT);
    gpio_put(LED_GREEM, 0); 

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0); 
}

void buzzer_active(uint32_t buzzer_frequency_in, uint32_t duration_buzzer_on) {
    uint32_t half_period_us = (1000000 / buzzer_frequency_in) / 2; // Define por quanto tempo o pino conectado ao buzzer deve ficar em nível alto/baixo

    // gera uma onda quadrada
    for (uint32_t i = 0; i < duration_buzzer_on * 1000; i += half_period_us * 2) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(half_period_us);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(half_period_us);
    }
}

void ligar_semaforo(void) {
    gpio_put(LED_RED, 1);
    sleep_ms(3000);
    gpio_put(LED_RED, 0);

    for (int i = 0; i < 3; i++) {
        gpio_put(LED_BLUE, 1);
        sleep_ms(1000);
        gpio_put(LED_BLUE, 0);
        sleep_ms(1000);
    }

    gpio_put(LED_GREEM, 1);
    sleep_ms(5000);
    gpio_put(LED_GREEM, 0);
}

void ponto() {
    gpio_put(LED_BLUE, true);
    sleep_ms(200);
    gpio_put(LED_BLUE, false);
}

void traco() {
    gpio_put(LED_BLUE, true);
    sleep_ms(800);
    gpio_put(LED_BLUE, false);
}

void sos_morse_code(void) {
    // Letra S
    ponto();
    sleep_ms(125);
    ponto();
    sleep_ms(125);
    ponto();
    
    sleep_ms(250);

    // Letra O
    traco();
    sleep_ms(125);
    traco();
    sleep_ms(125);
    traco();

    sleep_ms(250);

    // Letra S
    ponto();
    sleep_ms(125);
    ponto();
    sleep_ms(125);
    ponto();
}

// Acender todos os LEDs
void acender_leds() {
    gpio_put(LED_RED, 1);
    gpio_put(LED_GREEM, 1);
    gpio_put(LED_BLUE, 1);
}
// Apagar todos os LEDs
void apagar_leds() {
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEM, 0);
    gpio_put(LED_BLUE, 0);
}

void asterisco_led_buzzer(char key) {   
    keypad_key_counter++;
    printf("TECLA PRESSIONADA: %c\n", key);
    printf("Nº DE CLICKS: %d\n", keypad_key_counter);
    
    if (keypad_key_counter == 5) {
        printf("ROTINA ATIVA: BUZZER EMITE SOM E LEDS ACENDEM!\n");

        // Acende os LEDs e toca o buzzer
        acender_leds();

        // Ativa buzzer
        for (int i = 0; i < 5; i++) {
            buzzer_active(buzzer_frequency, 200);
            sleep_ms(500); // Pausa entre toques
        }

        apagar_leds();

        // Reseta o contador
        keypad_key_counter = 0;
        printf("ROTINA FINALIZADA: BUZZER EMITE SOM E LEDS ACENDEM!\n");
    }
}