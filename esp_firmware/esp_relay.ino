#include "esp_relay.h"

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
#if DEBUG_MODE
  Serial.println("Relay set to ON");
#endif
  
  digitalWrite(_gpio, _stateOn);
}

void EspRelay::off()
{
#if DEBUG_MODE
  Serial.println("Relay set to OFF");
#endif
  
  digitalWrite(_gpio, _stateOff);
}

void EspRelay::toggle()
{
  if (digitalRead(_gpio) == _stateOn) {
    off();
  }
  else {
    on();
  }
}

byte EspRelay::getState()
{
  byte state;
  if (digitalRead(_gpio) == _stateOn) {
    state = 1;
  } else {
    state = 0;
  }
  
#if DEBUG_MODE
  Serial.print("Relay state: ");
  Serial.println(state);
#endif
  
  return state;
}

