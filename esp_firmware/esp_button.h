#ifndef _esp_button_h
#define _esp_button_h

#include <Ticker.h>
#include <FunctionalInterrupt.h>

class EspButton
{
  typedef void (*CallbackFunction) ();
    
  public:
    EspButton(byte gpio, byte stateOn);
    void interruptCallback();
    void onShortPress(CallbackFunction onPressFunction);
    void onLongPress(CallbackFunction onPressFunction);
  private:
    byte _gpio;
    byte _stateOn = 1;
    byte _stateOff = 0;
    CallbackFunction _onShortPressCallback;
    CallbackFunction _onLongPressCallback;
    
    unsigned int _counter = 0;
    Ticker _buttonTimer;
    void onPress();
    void onRelase();
};

#endif
