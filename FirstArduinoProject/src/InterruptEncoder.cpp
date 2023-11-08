#include <InterruptEncoder.h>
#include <Arduino.h>
#include <util/atomic.h>
#include <Initializer.h>

#define NOT_TURNED 0
static const int TURNED_RIGHT = 1;
#define TURNED_LEFT 2

volatile int encoder1 = HIGH;
volatile int encoder2 = HIGH;
volatile unsigned long encoderTimestamp = 0UL;

ISR(PCINT1_vect)
{
    encoder1 = digitalRead(ENCODER1);
    encoder2 = digitalRead(ENCODER2);
    encoderTimestamp = millis();
}

InterruptEncoder::InterruptEncoder() {
  _debounceTime = DEBEOUNCE_TIME;
  _debouncedState = HIGH;
  _previousReading = HIGH;
  _lastChanged = 0UL;

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);
}

int InterruptEncoder::isTurned() {
    int result = NOT_TURNED;
    int en1;
    int en2;
    unsigned long timestamp;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        en1 = encoder1;
        en2 = encoder2;
        timestamp = encoderTimestamp;
    }

    if (en1 == LOW && _debouncedState == HIGH && timestamp > _lastChanged + _debounceTime)
    {
        if (en2 == HIGH)
            result = TURNED_RIGHT;
        else
            result = TURNED_LEFT;

        _lastChanged = timestamp;
    }
    _previousReading = en1;    
    return result;
  }

bool InterruptEncoder::isTurnedRight() {
    int result = isTurned();
    if (result == TURNED_RIGHT) {
        Serial.print("Turned right true");
    }
        
    return result == TURNED_RIGHT;
}

bool InterruptEncoder::isTurnedLeft() {
    int result = isTurned();
    if (result == TURNED_LEFT) {
        Serial.print("Turned left true");
    }
        
    return result == TURNED_LEFT;
}