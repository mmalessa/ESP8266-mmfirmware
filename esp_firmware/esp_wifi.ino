#include "esp_wifi.h"

EspWifi::EspWifi()
{
  state = ESPWIFI_STATE_OFF;
  //WiFi.mode(WIFI_AP_STA);
}

void EspWifi::startAP(const char deviceName[32])
{
#if DEBUG_MODE
  Serial.println("Starting WiFi on AP mode");
#endif

  if (state != ESPWIFI_STATE_OFF) {
#if DEBUG_MODE
  Serial.println("  ERROR - wifi is still ON");
#endif
    return;
  }

/*
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
//    WiFi.softAPdisconnect();
    WiFi.mode(WIFI_OFF);
    //WiFi.forceSleepBegin();
  delay(100);  
  }
  //WiFi.forceSleepWake();
  delay(1000);
  */
  WiFi.mode(WIFI_AP);

  unsigned nbTry = 3;
  bool statusAP = false;
  bool statusConfig = false;

  #if DEBUG_MODE
    Serial.print("  Try");
  #endif
  while (statusAP == false && nbTry>0) {
    #if DEBUG_MODE
        Serial.print(".");
      #endif
    IPAddress apIP(192, 168, 1, 1);
    statusConfig = WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    statusAP = WiFi.softAP(deviceName);
    //statusAP = WiFi.softAP(deviceName, "haslo");
    nbTry--;
    if (statusAP == false) {
      delay(1000);  
    }
  }
  if (statusAP) {
    state = ESPWIFI_STATE_AP;
  }
  #if DEBUG_MODE
    Serial.println("");
  #endif

#if DEBUG_MODE
  Serial.println((String)"  Device name: " + (String)deviceName);
  Serial.println(statusConfig ? "  Config ready" : "  Config failed!");
  Serial.println(statusAP ? "  AP ready" : "  AP failed!");
  Serial.println(WiFi.softAPIP());
#endif

}

void EspWifi::stopAP()
{
#if DEBUG_MODE
  Serial.println("WiFi - StopAP");
#endif

  if (state != ESPWIFI_STATE_AP) {
#if DEBUG_MODE
  Serial.println("  ERROR - wifi isn't in AP mode");
#endif
    return;
  }
  
  bool statusAP = WiFi.softAPdisconnect(true); 
  if (statusAP) {
    state = ESPWIFI_STATE_OFF;
  }

#if DEBUG_MODE
  Serial.println(statusAP ? "  OK" :"  ERROR");
#endif
}

void EspWifi::startSTA(const char ssid[32], const char password[32], const char deviceName[32])
{
#if DEBUG_MODE
  Serial.println("Starting WiFi on STA mode");
#endif;

  if (state != ESPWIFI_STATE_OFF) {
#if DEBUG_MODE
  Serial.println("  ERROR - wifi is still ON");
#endif
    return;
  }

  WiFi.mode(WIFI_STA);
  WiFi.hostname(deviceName);
  
  unsigned int nbTry = 4;
  while ((WiFi.status() != WL_CONNECTED) && (nbTry > 0)) {
    bool statusSTA = WiFi.begin(ssid, password);
    unsigned int nbWait = 7;
    #if DEBUG_MODE
      Serial.print((String)"  Try " + (String)nbTry);
    #endif
    while ((WiFi.status() != WL_CONNECTED) && (nbWait > 0)) {
      #if DEBUG_MODE
        Serial.print(".");
      #endif
      nbWait--;
      delay(1000);
    }
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.disconnect();
      delay(5000);
    }
    Serial.println("");
    nbTry--;
    
  }

  if (WiFi.status() == WL_CONNECTED) {
    state = ESPWIFI_STATE_STA;
    #if DEBUG_MODE
      Serial.println("  SUCCESS");
      //IPAddress myAddress = ;
      Serial.print("  IP: ");
      Serial.println(WiFi.localIP());
    #endif
  } else {
    #if DEBUG_MODE
      Serial.println("  ERROR");
    #endif
  }
}

void EspWifi::stopSTA()
{
#if DEBUG_MODE
  Serial.println("WiFi - StopSTA");
#endif

  if (state != ESPWIFI_STATE_STA) {
#if DEBUG_MODE
  Serial.println("  ERROR - wifi isn't in STA mode");
#endif
    return;
  }

  WiFi.disconnect();
  state = ESPWIFI_STATE_OFF;
  
#if DEBUG_MODE
  Serial.println("  OK");
#endif  
}

byte EspWifi::getState()
{
  return state;
}

