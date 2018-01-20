#include "esp_wifi.h"

bool EspWifi::startAP(const char deviceName[32])
{
  #if DEBUG_MODE
  Serial.println("Starting WiFi on AP mode");
  #endif

  // some magic
  WiFi.disconnect();
  WiFi.softAPdisconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(500);
  
  WiFi.mode(WIFI_AP);
  WiFi.forceSleepWake();
  IPAddress apIP(192, 168, 100, 1);
  bool statusConfig = WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  bool statusAP = WiFi.softAP(deviceName);  

  #if DEBUG_MODE
  Serial.println(statusConfig ? "Config ready" : "Config failed!");
  Serial.println(statusAP ? "AP ready" : "AP failed!");
  Serial.println(WiFi.softAPIP());
  #endif

  return (statusConfig && statusAP);
}

void EspWifi::startSTA(const char ssid[32], const char password[32], const char deviceName[32])
{
  #if DEBUG_MODE
  Serial.println("Starting WiFi on STA mode");
  #endif;

  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  delay(500);
  
  WiFi.mode(WIFI_STA);
  WiFi.hostname(deviceName);
  WiFi.begin(ssid, password);

}

bool EspWifi::isConnected()
{
  bool wlConnected;
  wlConnected = (WiFi.status() == WL_CONNECTED);
  
  #if DEBUG_MODE
  Serial.print("WiFi status: ");
  Serial.print(WiFi.status());
  if (wlConnected) {
    Serial.println(" (CONNECTED)");
  } else {
    Serial.println("");
  }
  #endif
  
  return wlConnected;
}
