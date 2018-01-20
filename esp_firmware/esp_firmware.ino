
#include "config.h"
#include "esp_led.h"
#include "esp_relay.h"
#include "esp_button.h"
#include "esp_wifi.h"
#include "esp_webserver.h"
#include "esp_mqtt.h"

#define DEBUG_MODE false

// GPIO configuration
#define BUTTON_GPIO 0
#define LED_GPIO 1
#define RELAY_GPIO 2

// static parameters
#define ON_WHEN_LOW 0
#define ON_WHEN_HIGH 1

#define MODE_INIT 0
#define MODE_NORMAL 1
#define MODE_CONFIGURATION 2
#define MODE_STANDBY 3
#define MODE_ERROR 255

Config cfg;
EspButton espButton(BUTTON_GPIO, ON_WHEN_LOW);
EspWifi espWifi;
EspLed blueLed(LED_GPIO, ON_WHEN_LOW);
EspRelay masterRelay(RELAY_GPIO, ON_WHEN_HIGH);
byte EspMode;

void setup() 
{
  
  #if DEBUG_MODE
  Serial.begin(115200);
  Serial.println("Starting...");
  #endif

  delay(500);
  cfg.load();
  delay(500);

  //startConfigurationMode();
  //return; 
  
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

    //TODO Mqtt handle
    
  } else if (EspMode == MODE_STANDBY) {
    Serial.println("Before 10000 delay");
    delay(10000);
    Serial.println("After 10000 delay");
    startNormalMode();
  } else { // MODE_INIT
    
  }
  
}

void startNormalMode()
{
  setMode(MODE_INIT);
  
  #if DEBUG_MODE
  Serial.println("Start normal mode");
  #endif
  
  espButton.onLongPress(startConfigurationMode);
  espButton.onShortPress(changeRelayState);
  httpServerStop();

  espWifi.startSTA(cfg.wifiSSID, cfg.wifiPassword, cfg.wifiDeviceName);
  unsigned int nbTry = 20;
  while (!espWifi.isConnected() && nbTry > 0) {
    nbTry--;
    delay(1000);
  }
  
  if(espWifi.isConnected()) {

    #if DEBUG_MODE
    Serial.println(WiFi.localIP());
    #endif
    
    setMode(MODE_NORMAL);
    
    //TODO start Mqtt
    
  }
  else {
    setMode(MODE_STANDBY);
  }
}

void startConfigurationMode()
{
  #if DEBUG_MODE
  Serial.println("Start configuration mode");
  #endif

  setMode(MODE_INIT);
  
  espButton.onLongPress(reboot); //TODO ESP.restart();
  espButton.onShortPress([]()->void{});
  bool apStatus = espWifi.startAP(cfg.wifiDeviceName);
  if(apStatus) {
    httpServerStart();
    setMode(MODE_CONFIGURATION);
  }
}

void reboot()
{
  #if DEBUG_MODE
  Serial.println("Restart");
  delay(500);
  Serial.end();
  #endif;
  
  delay(500);
  ESP.restart();
}

void changeRelayState()
{
  #if DEBUG_MODE
  Serial.println("Change relay state");
  #else
  blueLed.blink(200);
  #endif
  masterRelay.toggle();
}

void setMode(byte mode)
{
  EspMode = mode;

  #if DEBUG_MODE
  Serial.print("Set mode: ");
  Serial.println(mode);
  #else
  if (mode == MODE_NORMAL) {
    blueLed.stopBlinking();
  } else if (mode == MODE_CONFIGURATION) {
    blueLed.startBlinking(2000);
  } else if (mode == MODE_STANDBY) {
    blueLed.startBlinking(5000);
  } else { // MODE_INIT
    blueLed.startBlinking(250);
  }
  #endif
}

