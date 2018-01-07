
#include "config.h"
#include "esp-led.h"
#include "esp-relay.h"
#include "esp-wifi.h"

#define GPIO_0 0
#define GPIO_1 1 // blue led
#define GPIO_2 2
#define GPIO_3 3

#define ON_WHEN_HIGH 1
#define ON_WHEN_LOW 0

Config cfg;

//EspLed blueLed(GPIO_1, ON_WHEN_LOW);
//EspRelay masterRelay(GPIO_2, ON_WHEN_HIGH);
//EspWifi wifiClient(cfg.wifiSSID, cfg.wifiPassword, cfg.wifiDeviceName);
EspWifi espWifi(cfg.wifiSSID);

void setup() {

  Serial.begin(115200);
  Serial.println("Startujemy");
  espWifi.test();  

}

void loop() {

}

