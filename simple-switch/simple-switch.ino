
#include "led.h"

#define GPIO_0 0
#define GPIO_1 1 // blue led
#define GPIO_2 2
#define GPIO_3 3

Led blueLed(GPIO_1, LED_LOW);
Led redLed(GPIO_2, LED_HIGH);

void setup() {
  blueLed.off();
  redLed.off();
  delay(2000);
  blueLed.startBlinking(0.25);
  delay(1000);
  redLed.startBlinking(0.3);
  delay(10000);
  blueLed.stopBlinking();
  redLed.stopBlinking();
}

void loop() {

}
