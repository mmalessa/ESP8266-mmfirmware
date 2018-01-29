#include "esp_mqtt.h"

EspMqtt::EspMqtt()
{
  onChangeState([](byte state)->void{});
}

void EspMqtt::init(char host[32], int port) {
  #if DEBUG_MODE
  Serial.print("Mqtt init ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);
  #endif
  
  Mqtt.setClient(wifiClient);
  Mqtt.setServer(host, port);
  Mqtt.setCallback(std::bind(&EspMqtt::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  //Mqtt.setCallback([this] (char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });
}

void EspMqtt::callback(char* topic, byte* payload, unsigned int length)
{
  #if DEBUG_MODE
  Serial.print("Mqtt callback: ");
  #endif
  
  if (length >= 1) { // command arrived
    if ((char)payload[1] == 'N') {
      #if DEBUG_MODE
      Serial.print("ON");
      #endif
      _onChangeStateCallback(1);
    } else if ((char)payload[1] == 'F') {
      #if DEBUG_MODE
      Serial.print("OFF");
      #endif
      _onChangeStateCallback(0);
    }
  }
  #if DEBUG_MODE
  Serial.println("");
  #endif
}

bool EspMqtt::isConnected()
{
  bool ok = Mqtt.connected();
  return ok;
}

void EspMqtt::connect(char wifiDeviceName[32], char mqttUser[32], char mqttPassword[32], char mqttTopic[32]) {
  if (isConnected()) {
    return;
  }
  
  char  mqttString[60];
  sprintf(mqttString, "ESP (Device name: %s)", wifiDeviceName);
  
  #if DEBUG_MODE
  Serial.print("Mqtt try: ");
  Serial.print(mqttString);
  Serial.print(" ");
  Serial.print(mqttUser);
  Serial.print("/");
  Serial.println(mqttPassword);
  #endif

  if (Mqtt.connect(mqttString, mqttUser, mqttPassword)) {
    delay(500);
    sprintf(mqttString, "%scmd", mqttTopic);
    Mqtt.subscribe(mqttString);
    #if DEBUG_MODE
    Serial.println(mqttString);
    #endif
  }
}

void EspMqtt::disconnect()
{
  Mqtt.disconnect();
}

void EspMqtt::publishState(char mqttTopic[32], char* message) {
  if (Mqtt.state() == MQTT_CONNECTED) {
    char  mqttTopicState[50];
    sprintf(mqttTopicState, "%s%s", mqttTopic, "state");
    Mqtt.publish(mqttTopicState, message);
  }
}

void EspMqtt::onChangeState(CallbackFunction onChangeStateFunction)
{
  _onChangeStateCallback = onChangeStateFunction;
}

void  EspMqtt::loop() {
  Mqtt.loop();
}
