#ifndef debounceButton_h
#define debounceButton_h

#include <Arduino.h>

const int GREEN_BUTTON_INDEX = 0;
const int RED_BUTTON_INDEX = 1;
const unsigned long DEBOUNCE_TIME = 10UL;

class DebounceButton
{
  public:
    DebounceButton(int pin);
    DebounceButton(int pin, unsigned long debounceTime);
    bool isPressed();
  private:
    int _pin;
    unsigned long _debounceTime;
    int _debouncedState;
    int _previousReading;
    unsigned long _lastChanged;
};

#endif