#include "led.h"

Led::Led(byte gpio, byte stateOn)
{
  _gpio = gpio;
  _stateOn = (stateOn > 0) ? 1 : 0;
  _stateOff = (stateOn > 0) ? 0 : 1;
  pinMode(_gpio, OUTPUT);
  digitalWrite(_gpio, _stateOff);
}

void Led::on()
{
  digitalWrite(_gpio, _stateOn);
}

void Led::off()
{
  digitalWrite(_gpio, _stateOff);
}

void Led::blink(unsigned int ms)
{
  on();
  delay(ms);
  off();
}

void Led::startBlinking(float sec)
{
  _ledTimer.attach(sec, LedBlinkingCallback, _gpio);
}

void Led::stopBlinking()
{
  _ledTimer.detach();
  off();
}

void LedBlinkingCallback(byte gpio)
{
  if (digitalRead(gpio) == 1) {
    digitalWrite(gpio, 0);
  }
  else {
    digitalWrite(gpio, 1);
  }
}

