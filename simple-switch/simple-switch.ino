
#include "led.h"

#define GPIO_0 0
#define GPIO_1 1 // blue led
#define GPIO_2 2
#define GPIO_3 3

#define ON_WHEN_HIGH 1
#define ON_WHEN_LOW 0

Led blueLed(GPIO_1, ON_WHEN_LOW);

void setup() {

  // LED TEST
  blueLed.off();
  delay(2000);
  blueLed.startBlinking(0.25);
  delay(10000);
  blueLed.stopBlinking();
}

void loop() {

}
