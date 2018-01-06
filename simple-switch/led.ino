#include "led.h"

Led::Led(byte gpio, byte high)
{
  _gpio = gpio;
  _highState = (high > 0) ? 1 : 0;
  _lowState = (high > 0) ? 0 : 1;
  pinMode(_gpio, OUTPUT);
  digitalWrite(_gpio, 0);
}

void Led::on()
{
  digitalWrite(_gpio, _highState);
}

void Led::off()
{
  digitalWrite(_gpio, _lowState);
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

