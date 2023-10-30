#include "Initializer.h"
#include <OneWire.h>

OneWire oneWire(A1);

Initializer::Initializer() : _lcd(0x27, 16, 2), _sensors(&oneWire)
{
}

void Initializer::initEncoder() {
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
}

void Initializer::initRGB() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void Initializer::initButtons() {
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void Initializer::initLCD() {
  _lcd.init();
  _lcd.clear();
  _lcd.backlight();
}

LiquidCrystal_I2C Initializer::getLCD()
{
    return _lcd;
}

void Initializer::initSensors() {
  _sensors.begin();
}

DallasTemperature Initializer::getSensors()
{
    return _sensors;
}