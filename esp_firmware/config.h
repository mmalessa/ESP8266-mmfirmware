#ifndef _config_h
#define _config_h

#include <EEPROM.h>

class Config
{
  private:
    void write(unsigned int address, unsigned int size, String in);
    String read(unsigned int address, unsigned int size);
    void clear(unsigned int start, unsigned int size);
    
  public:
    Config();
    void load();
    void setWifiSSID(String in);
    void setWifiPassword(String in);
    void setWifiDeviceName(String in);
    void setMqttHost(String in);
    void setMqttPort(unsigned int in);
    void setMqttUser(String in);
    void setMqttPassword(String in);
    void setMqttTopic(String in);
    bool isConfigured();
    char wifiSSID[32];
    char wifiPassword[32];
    char wifiDeviceName[32];
    char mqttHost[32];
    unsigned int mqttPort;
    char mqttUser[32];
    char mqttPassword[32];
    char mqttTopic[32];
};

#endif
