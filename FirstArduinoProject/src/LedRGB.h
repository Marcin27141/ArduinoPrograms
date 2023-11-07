#ifndef ledRGB_h
#define ledRGB_h

#include <Arduino.h>

const int RED_LED_INDEX = 0;
const int GREEN_LED_INDEX = 1;
const int BLUE_LED_INDEX = 2;

class LedRGB
{
  public:
    LedRGB(int redPin, int greenPin, int bluePin);
    void lightOneColor(int ledIndex);
    void lightOneColor(int ledIndex, int intensity);
    void lightColor(int ledIndex);
    void turnOffColor(int ledIndex);
    void turnColor(int ledIndex);
    void lightColor(int ledIndex, int intensity);
    void setActiveColor(int ledIndex);
    int setFollowingColor(int currentColorIndex);
    void showColorsIfTurnedOn();
    void turnOn();
    void turnOff();
    void turnState();
  private:
    const int NUMBER_OF_COLORS = 3;
    const int MAX_INTENSITY = 255;
    int _leds[3];
    int _ledsStates[3];
    bool _turnedOn;
    bool intensityIsInRange(int intensity); 
};

#endif