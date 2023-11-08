#ifndef initializer_h
#define initializer_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DallasTemperature.h>

static const int DEBEOUNCE_TIME = 50UL;

static const int POTENTIOMETER = A0;
static const int LED_RED = 6;
static const int LED_GREEN = 5;
static const int LED_BLUE = 3;
static const int RED_BUTTON = 2;
static const int GREEN_BUTTON = 4;
static const int ENCODER1 = A2;
static const int ENCODER2 = A3;

class Initializer
{
  public:
    Initializer();
    void initEncoder();
    void initRGB();
    void initButtons();
    void initLCD(LiquidCrystal_I2C* lcd);
    void initSensors(DallasTemperature* sensors);
};

#endif