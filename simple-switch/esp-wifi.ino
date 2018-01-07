#include "esp-wifi.h"


EspWifi::EspWifi(const char ssid[32])
{
  _ssid = ssid;
//  /_password = password;
//  /_deviceName = deviceName;
}

void EspWifi::test()
{
  Serial.println("WifiClient");
  Serial.println(_ssid);
// / Serial.println(_password);
//  /Serial.println(_deviceName);  
}

