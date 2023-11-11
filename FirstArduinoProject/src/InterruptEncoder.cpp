#include <InterruptEncoder.h>
#include <Arduino.h>
#include <util/atomic.h>
#include <Initializer.h>

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
    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);

  _debounceTime = DEBEOUNCE_TIME;
  _lastChanged = 0UL;

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);
}

int InterruptEncoder::getDirection() {
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

    if (en1 == LOW && timestamp > _lastChanged + _debounceTime)
    {
        if (en2 == HIGH)
            result = TURNED_RIGHT;
        else
            result = TURNED_LEFT;

        _lastChanged = timestamp;
    }  
    return result;
  }