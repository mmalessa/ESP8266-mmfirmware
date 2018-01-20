#ifndef _esp_led_h
#define _esp_led_h

#include <Ticker.h>

class EspLed
{
  public:
    EspLed(byte gpio, byte stateOn);
    void on();
    void off();
    void blink(unsigned int t);
    void startBlinking(unsigned int t);
    void stopBlinking();
    void blinkingCallback();
  private:
    byte _gpio;
    byte _stateOn = 1;
    byte _stateOff = 0;
    byte _currentState = 0;
    Ticker _ledTimer;
};


#endif
