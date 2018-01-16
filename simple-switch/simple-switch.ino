
#include "config.h"
#include "esp-led.h"
#include "esp-relay.h"
#include "esp-wifi.h"
#include "esp-webserver.h"

// GPIO configuration
#define BUTTON_GPIO 0
#define LED_GPIO 1
#define RELAY_GPIO 2

// static parameters
#define ON_WHEN_LOW 0
#define ON_WHEN_HIGH 1
#define MODE_NORMAL_WORK 0
#define MODE_CONFIGURATION 1
#define EEPROM_SIZE 512

Config cfg;
EspWifi espWifi;
EspLed blueLed(LED_GPIO, ON_WHEN_LOW);
EspRelay masterRelay(RELAY_GPIO, ON_WHEN_HIGH);

void setup() 
{
  delay(500);
Serial.begin(115200);
Serial.println("Startujemy");
  cfg.load();

///  blueLed.startBlinking(0.2);
espWifi.startSTA(cfg.wifiSSID, cfg.wifiPassword, cfg.wifiDeviceName);
//  espWifi.startAP(cfg.wifiDeviceName);

  unsigned int nbTry = 20;
  while (!espWifi.isConnected() && nbTry > 0) {
    nbTry--;
    delay(1000);
  }

  if(espWifi.isConnected()) {
    Serial.println(" WiFi started");
    Serial.println(WiFi.localIP());
    //  blueLed.stopBlinking();
    httpServerStart();    
  }
  else {
    Serial.println(" WiFi not started");
  }
  
}

void loop() 
{
  httpServer.handleClient();
}

