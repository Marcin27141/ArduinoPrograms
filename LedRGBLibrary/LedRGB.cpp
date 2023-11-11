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

void LedRGB::lightRgb(int red, int green, int blue) {
    lightColor(RED_LED_INDEX, red);
    lightColor(GREEN_LED_INDEX, green);
    lightColor(BLUE_LED_INDEX, blue);
}

void LedRGB::lightOneColor(int ledIndex) {
    setActiveColor(ledIndex);
    showColorsIfTurnedOn();
}

void LedRGB::lightPredefinedColor(int color) {
    switch (color) {
        case RED:
            lightRgb(255, 0, 0);
            break;
        case GREEN:
            lightRgb(0, 255, 0);
            break;
        case BLUE:
            lightRgb(0, 0, 255);
            break;
        case YELLOW:
            lightRgb(255, 255, 0);
            break;
        case CYAN:
            lightRgb(0, 255, 255);
            break;
        case MAGENTA:
            lightRgb(255, 0, 144);
            break;
        case BLACK:
            lightRgb(0, 0, 0);
            break;
        case WHITE:
            lightRgb(255, 255, 255);
            break;
    }
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

void LedRGB::lightColor(int ledIndex, int intensity) {
    if (intensityIsInRange(intensity)) {
        _ledsStates[ledIndex] = intensity;
        showColorsIfTurnedOn();
    }
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