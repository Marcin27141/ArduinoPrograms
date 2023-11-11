#include <DebounceButton.h>
#include <Arduino.h>
#include <Initializer.h>

DebounceButton::DebounceButton(int pin, unsigned long debounceTime) {
  pinMode(pin, INPUT_PULLUP);

  _debounceTime = debounceTime;
  _pin = pin;
  _debouncedState = HIGH;
  _previousReading = HIGH;
  _lastChanged = 0UL;
}

DebounceButton::DebounceButton(int pin) : DebounceButton(pin, DEBEOUNCE_TIME) {
}

bool DebounceButton::isPressed() {
    bool isPressed = false;
    int current_reading = digitalRead(_pin);

    if (_previousReading != current_reading)
      _lastChanged = millis();

    if (millis() - _lastChanged > _debounceTime && current_reading != _debouncedState)
    {
      if (_debouncedState == HIGH && current_reading == LOW)
        isPressed = true;
      _debouncedState = current_reading;
    }

    _previousReading = current_reading;
    return isPressed;
}