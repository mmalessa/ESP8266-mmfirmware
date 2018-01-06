
#define _DEBUG true

#include "led.h"
#include "relay.h"

#define GPIO_0 0
#define GPIO_1 1 // blue led
#define GPIO_2 2
#define GPIO_3 3

#define ON_WHEN_HIGH 1
#define ON_WHEN_LOW 0

Led blueLed(GPIO_1, ON_WHEN_LOW);
Relay masterRelay(GPIO_2, ON_WHEN_HIGH);

void setup() {

  #if _DEBUG
  Serial.begin(115200);
  #endif

  // LED TEST
  /*
  blueLed.off();
  delay(2000);
  blueLed.startBlinking(0.25);
  delay(10000);
  blueLed.stopBlinking();
  */
  

  // RELAY TEST
  masterRelay.off();
  Serial.println("Switch OFF");
  delay(2000);
  masterRelay.toggle();
  Serial.print("Switch TOGGLE: ");
  Serial.println(masterRelay.getState());
  delay(2000);
  masterRelay.toggle();
  Serial.print("Switch TOGGLE: ");
  Serial.println(masterRelay.getState());
  delay(2000);
  masterRelay.toggle();
  Serial.print("Switch TOGGLE: ");
  Serial.println(masterRelay.getState());
  delay(2000);
  masterRelay.toggle();
  Serial.print("Switch TOGGLE: ");
  Serial.println(masterRelay.getState());
  delay(2000);
  masterRelay.off();
  Serial.println("Switch OFF");
  delay(2000);
  masterRelay.on();
  Serial.println("Switch ON");
  delay(2000);
  masterRelay.off();
  Serial.println("Switch OFF");
}

void loop() {

}

