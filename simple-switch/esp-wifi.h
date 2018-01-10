#ifndef _esp_wifi_h
#define _esp_wifi_h

#include <ESP8266WiFi.h>
#include <DNSServer.h>

class EspWifi
{
  
  public:
    EspWifi(const char ssid[32], const char password[32], const char deviceName[32]);
    void startAP();
    void startSTA();
    bool isConnected();
  private:
    const char* _ssid;
    const char* _password;
    const char* _deviceName;
    DNSServer dnsServer;
};

#endif
