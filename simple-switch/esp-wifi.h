#ifndef _esp_wifi_h
#define _esp_wifi_h

class EspWifi
{
  
  public:
    EspWifi(const char ssid[32]);
    void test();
  private:
    const char* _ssid;
//    /char* _password;
//    /char* _deviceName;

};

#endif
