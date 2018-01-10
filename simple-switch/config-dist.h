/*
 * Rename this file from config-dist.h to config.h
 */
 
#ifndef _config_h
#define _config_h

// GPIO configuration
#define BUTTON_GPIO 0
#define LED_GPIO 1
#define RELAY_GPIO 2

// static parameters
#define ON_WHEN_LOW 0
#define ON_WHEN_HIGH 1
#define MODE_NORMAL_WORK 0
#define MODE_CONFIGURATION 1


class Config
{
  public:
    char    wifiSSID[32] = "";
    char    wifiPassword[32] = "";
    char    wifiDeviceName[32] = "ESP8266_001";
};

#endif
