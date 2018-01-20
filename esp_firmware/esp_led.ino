#include "esp_led.h"

EspLed::EspLed(byte gpio, byte stateOn)
{
  _gpio = gpio;
  _stateOn = (stateOn > 0) ? 1 : 0;
  _stateOff = (stateOn > 0) ? 0 : 1;
  pinMode(_gpio, OUTPUT);
  digitalWrite(_gpio, _stateOff);
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

void EspLed::startBlinking(float sec)
{
  _ledTimer.attach(sec, EspLedBlinkingCallback, _gpio);
}

void EspLed::stopBlinking()
{
  _ledTimer.detach();
  off();
}

void EspLedBlinkingCallback(byte gpio)
{
  if (digitalRead(gpio) == 1) {
    digitalWrite(gpio, 0);
  }
  else {
    digitalWrite(gpio, 1);
  }
}

