#ifndef _esp_mqtt_h
#define _esp_mqtt_h

#include <PubSubClient.h>

class EspMqtt
{
  typedef void (*CallbackFunction) (byte state);
  
  private:
    PubSubClient Mqtt;
    WiFiClient wifiClient;
    CallbackFunction _onChangeStateCallback;

  public:
    EspMqtt();
    void init(char host[32], int port);
    //void callback(char* topic, byte* payload, unsigned int length);
    void callback(char* topic, byte* payload, unsigned int length);
    bool isConnected();
    void connect(char wifiDeviceName[32], char mqttUser[32], char mqttPassword[32], char mqttTopic[32]);
    void disconnect();
    void publishState(char mqttTopic[32], char* message);
    void loop();
    void onChangeState(CallbackFunction onChangeStateFunction);
};


#endif
