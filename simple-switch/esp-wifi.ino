#include "esp-wifi.h"

EspWifi::EspWifi(const char ssid[32], const char password[32], const char deviceName[32])
{
  _ssid = ssid;
  _password = password;
  _deviceName = deviceName;
}

void EspWifi::startAP()
{
  WiFi.mode(WIFI_AP);
  IPAddress apIP(192, 168, 5, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(_deviceName);
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(53, "www.example.com", apIP);
  
}

void EspWifi::startSTA()
{
  WiFi.mode(WIFI_STA);
  WiFi.hostname(_deviceName);
  WiFi.begin(_ssid, _password);
}

bool EspWifi::isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}
