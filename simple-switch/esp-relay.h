#ifndef _esp_relay_h
#define _esp_relay_h

class EspRelay
{
  public:
    EspRelay(byte gpio, byte stateOn);
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
