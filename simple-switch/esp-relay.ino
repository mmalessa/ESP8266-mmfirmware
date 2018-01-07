#include "esp-relay.h"

EspRelay::EspRelay(byte gpio, byte stateOn)
{
  _gpio = gpio;
  _stateOn = (stateOn > 0) ? 1 : 0;
  _stateOff = (stateOn > 0) ? 0 : 1;
  pinMode(_gpio, OUTPUT);
  digitalWrite(_gpio, _stateOff);
}

void EspRelay::on()
{
  digitalWrite(_gpio, _stateOn);
}

void EspRelay::off()
{
  digitalWrite(_gpio, _stateOff);
}

void EspRelay::toggle()
{
  if (digitalRead(_gpio) == 1) {
    digitalWrite(_gpio, 0);
  }
  else {
    digitalWrite(_gpio, 1);
  }
}

byte EspRelay::getState()
{
  return digitalRead(_gpio);
}

