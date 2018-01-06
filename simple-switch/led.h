#ifndef _led_h
#define _led_h

#include <Ticker.h>

class Led
{
  public:
    Led(byte gpio, byte stateOn);
    void on();
    void off();
    void blink(unsigned int t);
    void startBlinking(float t);
    void stopBlinking();
  private:
    byte _gpio;
    byte _stateOn = 1;
    byte _stateOff = 0;
    Ticker _ledTimer;
};


#endif
