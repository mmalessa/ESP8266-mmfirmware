#include "esp_core.h"

  EspButton espButton(BUTTON_GPIO, ON_WHEN_LOW);
  EspRelay espRelay(RELAY_GPIO, ON_WHEN_LOW);
  EspLed espLed(LED_GPIO, ON_WHEN_LOW);
  EspWifi espWifi;

  byte espState;

void espCoreSetConfig()
{
  espState = ESP_STATE_BOOT;
  delay(1000);
  
  #if DEBUG_MODE
    Serial.begin(115200);
    Serial.println("Starting...");
  #else
    espLed.startBlinking(1000);
  #endif
  
  espButton.onShortPress(espCoreOnShortPress);
  espButton.onLongPress(espCoreOnLongPress);

  espWifi.startSTA(WIFI_SSID,WIFI_PASSWORD,"TestESP");
  
  if (espWifi.getState() == ESPWIFI_STATE_OFF) {
    #if DEBUG_MODE
      Serial.println("  ESP STATE ERROR");
    #else
      espLed.startBlinking(250);
    #endif
    espState = ESP_STATE_ERROR;
    return;
  }
  
  #if DEBUG_MODE
    Serial.println("  OK");
  #else
    espLed.stopBlinking();
  #endif
}

void espCoreOnShortPress()
{
  espRelay.toggle();
}

void espCoreOnLongPress()
{
#if DEBUG_MODE
  Serial.println("LongPress");
#endif  

  if (espWifi.getState() == ESPWIFI_STATE_AP) {
    reboot();
  } else {
    espWifi.stopSTA();    
    delay(2000);
    espLed.startBlinking(2000);
    espWifi.startAP("TestAP");
    delay(2000);
  }
}

void reboot()
{
  #if DEBUG_MODE
    Serial.println("Restart");
    delay(1000);
    Serial.end();
  #endif;
  delay(2000);
  ESP.restart();
}





//////////////////
void espCoreLoopMain()
{
    /*
  switch(cfg.mode) {
    case ESP_MODE_CONFIG:
      loopConfig();
      break;
    case ESP_MODE_NORMAL:
      loopNormal();
      break;
  }
  */
}

void espCoreLoopConfig()
{
  /* 
   *  led.modeConfigBlink
   */

   /* 
    *  if no_accesspoint / no_network (?)
    *   led.noAccesspointBlink
    *   (??)
    */

    /* 
     *  espWebServer.loop();
     */
}

void espCoreLoopNormal()
{
  /* 
   *  led.off
   */

  /* 
   *  if no_network
   *    led.noNetworkBlink
   *    delay(1000);
   *    return;
   */

   /* 
    *  if no_mqtt
    *   led.noMqttBlink
    *   delay(1000);
    *   return;
    */

    /* 
     *  espMqtt.loop();
     */
}


///////////////////////////////
void goToConfigMode()
{
  
}

void goToNormalMode()
{
  
}



