#include "esp_led.h"

EspLed::EspLed(byte gpio, byte stateOn)
{
  _gpio = gpio;
  pinMode(_gpio, OUTPUT);
  
  _stateOn = (stateOn > 0) ? 1 : 0;
  _stateOff = (stateOn > 0) ? 0 : 1;
  _currentState = _stateOff;
  off();
}

void EspLed::on()
{
  _currentState = _stateOn;
  digitalWrite(_gpio, _stateOn);
}

void EspLed::off()
{
  _currentState = _stateOff;
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
  _ledTimer.attach_ms(ms, EspLedBlinkingCallback);
}

void EspLed::stopBlinking()
{
  _ledTimer.detach();
  off();
}

void EspLed::blinkingCallback()
{
  if (_currentState == _stateOn) {
    off();
  }
  else {
    on();
  }  
}

void EspLedBlinkingCallback()
{
  blueLed.blinkingCallback();
}

