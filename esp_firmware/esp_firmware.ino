
#include "config.h"
#include "esp_led.h"
#include "esp_relay.h"
#include "esp_button.h"
#include "esp_wifi.h"
#include "esp_webserver.h"
#include "esp_mqtt.h"

#define DEBUG_MODE true

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
EspMqtt espMqtt;

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
    espMqtt.loop();
  } else if (EspMode == MODE_STANDBY) {
    delay(10000);
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
  unsigned int nbTry = 20;

  if (!espWifi.isConnected()) {
    espWifi.startSTA(cfg.wifiSSID, cfg.wifiPassword, cfg.wifiDeviceName);
    
    while (!espWifi.isConnected() && nbTry > 0 && EspMode == MODE_INIT) {
      nbTry--;
      delay(1000);
    }
  }
  
  if (espWifi.isConnected()) {

    #if DEBUG_MODE
    Serial.println(WiFi.localIP());
    #endif
    
    
    espMqtt.init(cfg.mqttHost, cfg.mqttPort);
    nbTry = 5;
    delay(100);
    
    while (!espMqtt.isConnected() && nbTry > 0 && EspMode == MODE_INIT) {
      nbTry--;
      espMqtt.connect(cfg.wifiDeviceName, cfg.mqttUser, cfg.mqttPassword, cfg.mqttTopic);
      delay(3000);
    }

    if(espMqtt.isConnected()) {
      espMqtt.onChangeState(mqttChangeStateCallback);
      setMode(MODE_NORMAL);
    } else {
      setMode(MODE_STANDBY);
    }
    
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
  if (espMqtt.isConnected()) {
    char  message[4];
    sprintf(message, "%s", masterRelay.getState() ? "ON" : "OFF");
    espMqtt.publishState(cfg.mqttTopic, message);
  }
}

void setMode(byte mode)
{
  EspMode = mode;

  if (mode == MODE_NORMAL) {
    #if DEBUG_MODE
    Serial.print("Set MODE_NORMAL");
    #else
    blueLed.stopBlinking();
    #endif
  } else if (mode == MODE_CONFIGURATION) {
    #if DEBUG_MODE
    Serial.print("Set MODE_CONFIGURATION");
    #else
    blueLed.startBlinking(2000);
    #endif
  } else if (mode == MODE_STANDBY) {
    #if DEBUG_MODE
    Serial.print("Set MODE_STANDBY");
    #else
    blueLed.startBlinking(5000);
    #endif
  } else { // MODE_INIT
    #if DEBUG_MODE
    Serial.print("Set MODE_INIT");
    #else
    blueLed.startBlinking(250);
    #endif
  }

}


void mqttChangeStateCallback(byte state)
{
  #if DEBUG_MODE
  Serial.print("Mqtt incoming state: ");
  Serial.println(state);
  #endif
  
  char  message[4];
  if (state == 1) {
    masterRelay.on();
    sprintf(message, "%s", "ON");
  } else {
    masterRelay.off();
    sprintf(message, "%s", "OFF");
  }
  espMqtt.publishState(cfg.mqttTopic, message);
}

