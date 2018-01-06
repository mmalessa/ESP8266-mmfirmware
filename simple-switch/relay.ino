#include "relay.h"

Relay::Relay(byte gpio, byte stateOn)
{
  _gpio = gpio;
  _stateOn = (stateOn > 0) ? 1 : 0;
  _stateOff = (stateOn > 0) ? 0 : 1;
  pinMode(_gpio, OUTPUT);
  digitalWrite(_gpio, _stateOff);
}

void Relay::on()
{
  digitalWrite(_gpio, _stateOn);
}

void Relay::off()
{
  digitalWrite(_gpio, _stateOff);
}

void Relay::toggle()
{
  if (digitalRead(_gpio) == 1) {
    digitalWrite(_gpio, 0);
  }
  else {
    digitalWrite(_gpio, 1);
  }
}

byte Relay::getState()
{
  return digitalRead(_gpio);
}

