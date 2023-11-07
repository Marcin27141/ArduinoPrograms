#include <LedRGB.h>
#include <Arduino.h>

LedRGB::LedRGB(int redPin, int greenPin, int bluePin) :
    _leds{redPin, greenPin, bluePin},
    _ledsStates{0, 0, 0} {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    _turnedOn = false;
}

bool LedRGB::intensityIsInRange(int intensity) {
    return intensity >= 0 && intensity <= MAX_INTENSITY;
}

void LedRGB::showColorsIfTurnedOn() {
    if (_turnedOn) {
        for (int i = 0; i < NUMBER_OF_COLORS; i++)
            analogWrite(_leds[i], _ledsStates[i]);
    }
    
}

void LedRGB::lightOneColor(int ledIndex) {
    setActiveColor(ledIndex);
    showColorsIfTurnedOn();
}

void LedRGB::lightOneColor(int ledIndex, int intensity) {
    if (intensityIsInRange(intensity)) {
        for (int i = 0; i < NUMBER_OF_COLORS; i++) {
            int state = ledIndex == i ? intensity : 0;
            _ledsStates[i] = state;
        }
        showColorsIfTurnedOn();
    }
}

void LedRGB::lightColor(int ledIndex) {
    lightColor(ledIndex, MAX_INTENSITY);
}

void LedRGB::turnOffColor(int ledIndex) {
    _ledsStates[ledIndex] = LOW;
    showColorsIfTurnedOn();
}

void LedRGB::turnColor(int ledIndex) {
    if (_ledsStates[ledIndex] == LOW) {
        lightColor(ledIndex);
    }
    else
        turnOffColor(ledIndex);
}

void LedRGB::lightColor(int ledIndex, int intensity) {
    if (intensityIsInRange(intensity)) {
        _ledsStates[ledIndex] = intensity;
        showColorsIfTurnedOn();
    }
}

void LedRGB::setActiveColor(int ledIndex) {
    for (int i = 0; i < NUMBER_OF_COLORS; i++) {
        int state = ledIndex == i ? MAX_INTENSITY : 0;
        _ledsStates[i] = state;
    }
}

int LedRGB::setFollowingColor(int currentColorIndex) {
    int nextColor;
    switch(currentColorIndex) {
    case RED_LED_INDEX:
        nextColor = GREEN_LED_INDEX;
        break;
    case GREEN_LED_INDEX:
        nextColor = BLUE_LED_INDEX;
        break;
    case BLUE_LED_INDEX:
        nextColor = RED_LED_INDEX;
        break;
    default:
        nextColor = currentColorIndex;
        break;
    }
    setActiveColor(nextColor);
    return nextColor;
}

void LedRGB::turnOn() {
    _turnedOn = true;
    showColorsIfTurnedOn();
}

void LedRGB::turnOff() {
    _turnedOn = false;
    for (int i = 0; i < NUMBER_OF_COLORS; i++)
        digitalWrite(_leds[i], LOW);
}

void LedRGB::turnState() {
    if (_turnedOn)
        turnOff();
    else
        turnOn();
}