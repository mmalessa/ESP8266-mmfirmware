
#include "config.h"
#include "esp_led.h"
#include "esp_relay.h"
#include "esp_button.h"
#include "esp_wifi.h"
#include "esp_webserver.h"
#include "esp_mqtt.h"

// GPIO configuration
#define BUTTON_GPIO 0
#define LED_GPIO 1
#define RELAY_GPIO 2

// static parameters
#define ON_WHEN_LOW 0
#define ON_WHEN_HIGH 1
#define MODE_NORMAL 0
#define MODE_CONFIGURATION 1
#define MODE_STANDBY 2
#define EEPROM_SIZE 512

Config cfg;
EspButton espButton(BUTTON_GPIO, ON_WHEN_LOW);
EspWifi espWifi;
EspLed blueLed(LED_GPIO, ON_WHEN_LOW);
EspRelay masterRelay(RELAY_GPIO, ON_WHEN_HIGH);
unsigned int EspMode;

void setup() 
{
//Serial.begin(115200);
  delay(500);
  cfg.load();
  
  if (cfg.isConfigured()) {
    startNormalMode();    
  } else {
    startConfigurationMode();
  }
}

void loop() 
{
  if (EspMode == MODE_CONFIGURATION) {
    httpServer.handleClient();
  } else if (EspMode == MODE_NORMAL) {
    
  } else { // MODE_SLEEP
    delay(10000);
    startNormalMode();
  }
}

void startNormalMode()
{
  espButton.onLongPress(startConfigurationMode);
  espButton.onShortPress(changeRelayState);

  blueLed.startBlinking(0.2);
  espWifi.startSTA(cfg.wifiSSID, cfg.wifiPassword, cfg.wifiDeviceName);
  unsigned int nbTry = 20;
  while (!espWifi.isConnected() && nbTry > 0) {
    nbTry--;
    delay(1000);
  }
  if(espWifi.isConnected()) {
    blueLed.stopBlinking();
    EspMode = MODE_NORMAL;
    httpServerStart();    
    
  }
  else {
    blueLed.startBlinking(1);
    EspMode = MODE_STANDBY;
  }
}

void startConfigurationMode()
{
  espButton.onLongPress(startNormalMode);
  espButton.onShortPress([]()->void{});
  espWifi.startAP(cfg.wifiDeviceName);
}

void changeRelayState()
{
  masterRelay.toggle();
}

