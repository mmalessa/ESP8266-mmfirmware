
#include "config.h"
#include "esp-led.h"
#include "esp-relay.h"
#include "esp-wifi.h"
#include "esp-webserver.h"


Config cfg;

EspLed blueLed(LED_GPIO, ON_WHEN_LOW);
EspRelay masterRelay(RELAY_GPIO, ON_WHEN_HIGH);
EspWifi espWifi(cfg.wifiSSID, cfg.wifiPassword, cfg.wifiDeviceName);


void setup() 
{
///  Serial.begin(115200);
///  Serial.println("Startujemy");
  //espWifi.test();  

  blueLed.startBlinking(0.2);
  espWifi.startSTA();
  delay(10000);
  blueLed.stopBlinking();
  httpServerStart();
}

void loop() 
{
  httpServer.handleClient();

}



