/*
 * ESP8266 EMEM firmware
 * 2018 mmalessa http://www.malessa.pl/
 */

#include "config.h"
#include "esp_button.h"
#include "esp_relay.h"
#include "esp_wifi.h"
#include "esp_led.h"
#include "esp_core.h"


#define DEBUG_MODE false


void setup()
{
  espCoreSetConfig();
}

void loop()
{
  espCoreLoopMain();
}



