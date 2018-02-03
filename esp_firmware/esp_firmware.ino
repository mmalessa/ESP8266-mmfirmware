/*
  ESP OH: firmware
  2018 mmalessa http://www.malessa.pl/
*/

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
EspWebServer espWebServer;
EspMqtt espMqtt;

byte espMode;

void setup() 
{
#if DEBUG_MODE
  Serial.begin(115200);
  Serial.println("Starting...");
#else
  blueLed.startBlinking(100);
#endif

  espMode = MODE_INIT;
  
  delay(200);
  cfg.load();
  delay(200);
  
  if (cfg.isConfigured()) {
    startNormalMode();    
  } else {
    startConfigurationMode();
  }
}

void loop() 
{
  if (espMode == MODE_CONFIGURATION) {
    espWebServer.loop();
  } else if (espMode == MODE_NORMAL) {
    espMqtt.loop();
  } else if (espMode == MODE_STANDBY) {
    delay(10000);
    if (espMode == MODE_STANDBY) {
      startNormalMode();
    }
  } else { // MODE_INIT
    
  }
}

void goToConfiguration()
{
#if DEBUG_MODE
  Serial.println("Go to configuration");
#endif

  cfg.setNeedConfiguration(true);
  delay(100);
  reboot();
}

void exitFromConfiguration()
{
#if DEBUG_MODE
  Serial.println("Exit from configuration");
#endif

  cfg.setNeedConfiguration(false);
  delay(100);
  reboot();
}

void startConfigurationMode()
{ 
  espMode = MODE_CONFIGURATION;

#if DEBUG_MODE
  Serial.println("Start configuration mode");
#else
  blueLed.startBlinking(1000);
#endif

  espMqtt.stop();

  espButton.onLongPress(exitFromConfiguration);
  espButton.onShortPress([]()->void{});

  bool apStatus = espWifi.startAP(cfg.wifiDeviceName);

  if(apStatus) {
    espWebServer.start();
  } 

}

void startNormalMode()
{
  espMode = MODE_NORMAL;
  
#if DEBUG_MODE
  Serial.println("Start normal mode");
#else
  blueLed.startBlinking(400);
#endif
  
  espButton.onLongPress(goToConfiguration);
  espButton.onShortPress(changeRelayState);
  
  espWebServer.stop();
  
  unsigned int nbTry = 20;
  if (espMode == MODE_NORMAL && !espWifi.isConnected()) {
    espWifi.startSTA(cfg.wifiSSID, cfg.wifiPassword, cfg.wifiDeviceName);
    
    while (espMode == MODE_NORMAL && !espWifi.isConnected() && nbTry > 0) {
      nbTry--;
      delay(1000);
    }
  }
  
  if (espMode == MODE_NORMAL && espWifi.isConnected()) {

#if DEBUG_MODE
    Serial.println(WiFi.localIP());
#else
    blueLed.startBlinking(600);
#endif
    
    espMqtt.init(cfg.mqttHost, cfg.mqttPort);
    nbTry = 5;
    delay(100);
    
    while (espMode == MODE_NORMAL && !espMqtt.isConnected() && nbTry > 0) {
      nbTry--;
      espMqtt.connect(cfg.wifiDeviceName, cfg.mqttUser, cfg.mqttPassword, cfg.mqttTopic);
      delay(3000);
    }

    if(espMqtt.isConnected()) {
#if DEBUG_MODE
      Serial.println("Mqtt connected");
#else
      blueLed.stopBlinking();
#endif
      espMqtt.onChangeState(mqttChangeStateCallback);
    } else if (espMode == MODE_NORMAL) {
      espMode = MODE_STANDBY;
      
#if !DEBUG_MODE
      blueLed.startBlinking(3000);
#endif

    }
    
  } else if (espMode == MODE_NORMAL) {
    espMode = MODE_STANDBY;
    
#if !DEBUG_MODE
    blueLed.startBlinking(3000);
#endif
    
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
  masterRelay.toggle();
  if (espMqtt.isConnected()) {
    char  message[4];
    sprintf(message, "%s", masterRelay.getState() ? "ON" : "OFF");
    espMqtt.publishState(cfg.mqttTopic, message);
  }
#if DEBUG_MODE
  Serial.println("Change relay state");
#else
  blueLed.blink(100);
#endif
}

void mqttChangeStateCallback(byte state)
{
  char  message[4];
  if (state == 1) {
    masterRelay.on();
    sprintf(message, "%s", "ON");
  } else {
    masterRelay.off();
    sprintf(message, "%s", "OFF");
  }
  espMqtt.publishState(cfg.mqttTopic, message);
  
#if DEBUG_MODE
  Serial.print("Mqtt incoming state: ");
  Serial.println(state);
#else
  blueLed.blink(100);
#endif

}

