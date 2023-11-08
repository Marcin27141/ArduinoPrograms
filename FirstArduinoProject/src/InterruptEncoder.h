#ifndef inerruptEncoder_h
#define inerruptEncoder_h

#include <Arduino.h>

static const int NOT_TURNED = 0;
static const int TURNED_RIGHT = 1;
static const int TURNED_LEFT = 2;

class InterruptEncoder {
  public:
    InterruptEncoder();
    int getDirection();
  private:
    unsigned long _debounceTime;
    unsigned long _lastChanged;
};

#endif