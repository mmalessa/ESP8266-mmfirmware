#include "config.h"

Config::Config()
{
  EEPROM.begin(EEPROM_SIZE);
}

void Config::load()
{
#if DEBUG_MODE
  Serial.println("Load config...");
#endif

  read(0, 32).toCharArray(wifiSSID, sizeof(wifiSSID));
  read(64, 32).toCharArray(wifiPassword, sizeof(wifiPassword));
  read(96, 32).toCharArray(wifiDeviceName, sizeof(wifiDeviceName));
  read(128, 32).toCharArray(mqttHost, sizeof(mqttHost));
  read(160, 32).toCharArray(mqttUser, sizeof(mqttUser));
  read(192, 32).toCharArray(mqttPassword, sizeof(mqttPassword));
  read(224, 32).toCharArray(mqttTopic, sizeof(mqttTopic));
  mqttPort = read(256, 5).toInt();
  needConfiguration = EEPROM.read(261);
}

void Config::setWifiSSID(String in) { write(0, 32, in); }
void Config::setWifiPassword(String in) { write(64, 32, in); }
void Config::setWifiDeviceName(String in) { write(96, 32, in); }
void Config::setMqttHost(String in) { write(128, 32, in); }
void Config::setMqttUser(String in) { write(160, 32, in); }
void Config::setMqttPassword(String in) { write(192, 32, in); }
void Config::setMqttTopic(String in) { write(224, 32, in); }
void Config::setMqttPort(unsigned int in) { write(256, 5, String(in)); }
void Config::setNeedConfiguration(bool yn) { EEPROM.write(261, (yn ? 1 : 0)); EEPROM.commit(); }

void Config::write(unsigned int address, unsigned int size, String in) {
  clear(address, size);
  for (int i = 0; i < in.length(); ++i)
  {
    EEPROM.write(address + i, in[i]);
  }
  EEPROM.commit();
}

String Config::read(unsigned int address, unsigned int size) {
  String _return;
  for (int i = address; i < address + size; ++i)
  {
    if (EEPROM.read(i) != 255) {
      _return += char(EEPROM.read(i));
    }
  }
  return _return;
}

void Config::clear(unsigned int address, unsigned int size) {
  for (int i = 0; i < size; ++i) {
    EEPROM.write(i + address, 255);
  }
}

bool Config::isConfigured() {
  bool isc = !(wifiSSID[0] == (char)0 || wifiPassword[0] == (char)0 || wifiDeviceName[0] == (char)0 || needConfiguration == 1);
#if DEBUG_MODE
  Serial.print("Is configured: ");
  Serial.println(isc ? "YES" : "NO");
#endif
  return isc;
}

