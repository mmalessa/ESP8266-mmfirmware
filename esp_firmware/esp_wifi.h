#ifndef _esp_wifi_h
#define _esp_wifi_h

#include <ESP8266WiFi.h>

class EspWifi
{
  public:
    bool startAP(const char deviceName[32]);
    void startSTA(const char ssid[32], const char password[32], const char deviceName[32]);
    bool isConnected();
    

};

#endif
