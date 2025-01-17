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

const uint8_t row_pins[KEYPAD_ROWS] = {1, 2, 3, 4};
const uint8_t col_pins[KEYPAD_COLS] = {5, 6, 7, 8};
const uint32_t buzzer_frequency = 100;

uint8_t btn_counter;
uint8_t keypad_key_counter;

const char key_map[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

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
        while(gpio_get(col_pins[j]));

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

void buzzer_active(uint32_t buzzer_frequency, uint32_t duration_buzzer_on) {
    uint32_t half_period_us = (1000000 / buzzer_frequency) / 2; // Define por quanto tempo o pino conectado ao buzzer deve ficar em nível alto/baixo

    // gera uma onda quadrada
    for (uint32_t i = 0; i < duration_buzzer_on * 1000; i += half_period_us * 2) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(half_period_us);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(half_period_us);
    }
}

int main() {
    btn_counter = 0;
    keypad_key_counter = 0;

    stdio_init_all();
    keypad_init();
    btn_init();
    buzzer_init();

    while (true) {
        char key = keypad_read();

        if (key == 'A') {
            // codigo (1) aqui 
        } else if (key == 'B') {
            // codigo (1) aqui 
        } else if (key == 'C') {
            // codigo (1) aqui 
        } else if (key == 'D') {
            // codigo (2) aqui
        } else if (key == '#') {
            // Quando o botão # for pressionado, o buzzer é ativado por 2s com uma frequência de 900Hz
            buzzer_active(900, 2000);
        } else if (key == '0') {
            // codigo (6) aqui
        } else if (key == '6') {
            // codigo (7) aqui
        } else if (key == '9') {
            // codigo (8) aqui
        } else if (!gpio_get(BTN_PIN)) {
            // codigo (4) aqui
            // para o contador, utilize a variavel btn_counter que ja foi criada
        } else if (key == '*') {
            // codigo (5) aqui
            // para o contador, utilize a variavel keypad_key_counter que ja foi criada
        }

        sleep_ms(100);
    }

    return 0;
}
