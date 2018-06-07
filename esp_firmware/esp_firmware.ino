/*
 * ESP8266 EMEM firmware
 * 2018 mmalessa http://www.malessa.pl/
 */

#include "esp_button.h"
#include "esp_relay.h"
#include "esp_core.h"


#define DEBUG_MODE true


void setup()
{
  espCoreSetConfig();
}

void loop()
{
  espCoreLoopMain();
}



