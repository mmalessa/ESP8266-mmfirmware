#ifndef _led_h
#define _led_h

#include <Ticker.h>

#define LED_HIGH 1
#define LED_LOW 0

class Led
{
  public:
    Led(byte gpio, byte high);
    void on();
    void off();
    void blink(unsigned int t);
    void startBlinking(float t);
    void stopBlinking();
  private:
    byte _gpio;
    byte _highState = 1;
    byte _lowState = 0;
    Ticker _ledTimer;
  
};


#endif
