#include "Initializer.h"
#include <OneWire.h>

Initializer::Initializer() {
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

void Initializer::initLCD(LiquidCrystal_I2C* lcdPtr) {
  lcdPtr->init();
  lcdPtr->clear();
  lcdPtr->backlight();
}


void Initializer::initSensors(DallasTemperature* sensors) {
  sensors->begin();
}