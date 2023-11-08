#ifndef inerruptEncoder_h
#define inerruptEncoder_h

#include <Arduino.h>

class InterruptEncoder {
  public:
    InterruptEncoder();
    bool isTurnedRight();
    bool isTurnedLeft();
  private:
    int isTurned();
    unsigned long _debounceTime;
    volatile int _debouncedState;
    volatile int _previousReading;
    volatile unsigned long _lastChanged;
};

#endif