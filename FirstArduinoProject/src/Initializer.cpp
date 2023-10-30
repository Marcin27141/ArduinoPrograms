#include "Initializer.h"
#include <OneWire.h>

Initializer::Initializer() {
  _lcd = new LiquidCrystal_I2C(0x27, 16, 2);
  OneWire oneWire(A1);
  _sensors = new DallasTemperature(&oneWire);
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
  _lcd->init();
  _lcd->clear();
  _lcd->backlight();
}

LiquidCrystal_I2C* Initializer::getLCD()
{
    return _lcd;
}

void Initializer::initSensors() {
  _sensors->begin();
}

DallasTemperature* Initializer::getSensors()
{
    return _sensors;
}

Initializer::~Initializer() {
  delete _lcd;
  delete _sensors;
}