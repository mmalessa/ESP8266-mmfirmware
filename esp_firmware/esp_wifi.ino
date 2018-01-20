#include "esp_wifi.h"

void EspWifi::startAP(const char deviceName[32])
{
  WiFi.mode(WIFI_AP);
  IPAddress apIP(192, 168, 5, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(deviceName);  
}

void EspWifi::startSTA(const char ssid[32], const char password[32], const char deviceName[32])
{
  WiFi.mode(WIFI_STA);
  WiFi.hostname(deviceName);
  WiFi.begin(ssid, password);
}

bool EspWifi::isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}
