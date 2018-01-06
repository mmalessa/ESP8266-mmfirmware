#ifndef _relay_h
#define _relay_h

class Relay
{
  public:
    Relay(byte gpio, byte stateOn);
    void on();
    void off();
    void toggle();
    byte getState();
  private:
    byte _gpio;
    byte _stateOn = 1;
    byte _stateOff = 0;
};

#endif
