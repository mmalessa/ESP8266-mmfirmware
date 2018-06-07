#include "esp_core.h"

  EspButton espButton(BUTTON_GPIO, ON_WHEN_LOW);
  EspRelay espRelay(RELAY_GPIO, ON_WHEN_LOW);


void espCoreSetConfig()
{
  espButton.onShortPress(espCoreOnShortPress);
  espButton.onLongPress(espCoreOnLongPress);
}

void espCoreOnShortPress()
{
  espRelay.toggle();
}

void espCoreOnLongPress()
{
  
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

