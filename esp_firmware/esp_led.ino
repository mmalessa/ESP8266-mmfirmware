#include "esp_led.h"

EspLed::EspLed(byte gpio, byte stateOn)
{
  _gpio = gpio;
  pinMode(_gpio, OUTPUT);
  
  _stateOn = (stateOn > 0) ? 1 : 0;
  _stateOff = (stateOn > 0) ? 0 : 1;
  off();
}

void EspLed::on()
{
  digitalWrite(_gpio, _stateOn);
}

void EspLed::off()
{
  digitalWrite(_gpio, _stateOff);
}

void EspLed::blink(unsigned int ms)
{
  on();
  delay(ms);
  off();
}

void EspLed::startBlinking(unsigned int ms)
{
  on();
  _ledTimer.attach_ms<byte>(ms, [](byte gpio){ digitalWrite(gpio, !digitalRead(gpio)); }, _gpio);
}

void EspLed::stopBlinking()
{
  _ledTimer.detach();
  off();
}

