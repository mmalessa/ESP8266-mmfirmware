#include "esp_button.h"


EspButton::EspButton(byte gpio, byte stateOn)
{
  _gpio = gpio;
  _stateOn = (stateOn > 0) ? 1 : 0;
  _stateOff = (stateOn > 0) ? 0 : 1;
  onShortPress([]()->void{});
  onLongPress([]()->void{});
  pinMode(_gpio, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_gpio), EspButtonInterruptCallback, CHANGE);
}

void EspButton::interruptCallback()
{
  if(digitalRead(_gpio) == _stateOn) {
    onPress();
  }
  else {
    onRelase();
  }
}

void EspButton::onPress()
{
  _buttonTimer.attach(0.05, EspButtonTimerCallback);
}
void EspButton::onRelase()
{
  if (_counter > 40) {
    _onLongPressCallback();
  } else if (_counter > 0) {
    _onShortPressCallback();
  }
  _counter = 0;
  _buttonTimer.detach();
}

void EspButton::timerCallback()
{
  _counter++;
}

void EspButton::onShortPress(CallbackFunction onPressFunction)
{
  _onShortPressCallback = onPressFunction;
}

void EspButton::onLongPress(CallbackFunction onPressFunction)
{
  _onLongPressCallback = onPressFunction;
}

  // uggly, but...
void EspButtonInterruptCallback()
{
  espButton.interruptCallback();
}
void EspButtonTimerCallback()
{
  espButton.timerCallback();
}
