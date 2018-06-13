#ifndef _esp_wifi_h
#define _esp_wifi_h

#include <ESP8266WiFi.h>

#define ESPWIFI_STATE_OFF 0
#define ESPWIFI_STATE_STA 1
#define ESPWIFI_STATE_AP 2

class EspWifi
{
  public:
    EspWifi();
    void startAP(const char deviceName[32]);
    void stopAP();
    
    void startSTA(const char ssid[32], const char password[32], const char deviceName[32]);
    void stopSTA();

    byte getState();

  private:
    byte state;

};

#endif
