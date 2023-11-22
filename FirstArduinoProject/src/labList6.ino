#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Initializer.h>
#include <DebounceButton.h>
#include <LedRGB.h>

LedRGB ledRGB(LED_RED, LED_GREEN, LED_BLUE);
DebounceButton redDebounceButton(RED_BUTTON);

LiquidCrystal_I2C lcd(0x27,16,2);
#define LCD_ROW_INSIDE 0
#define LCD_ROW_OUTSIDE 1

bool isShowingTemperatures = true;
int const MAX_EXTREME_TEMPERATURES_DISPLAY = 5000;

#define ONE_WIRE A1
OneWire oneWire(ONE_WIRE);
DallasTemperature sensors(&oneWire);
unsigned long lastSensorReading = 0UL;
int const READINGS_WINDOW = 1000;

DeviceAddress mySensor = { 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFB };
#define MAIN_SENSOR_IDX 0

#define MAX_TEMP 125
#define LOWER_DECENT_TEMP 19
#define UPPER_DECENT_TEMP 26

float minTemp;
float maxTemp;

float getFilteredTempValue(float reading) {
    if (reading > MAX_TEMP) return 0;
    return reading;
}

void printInitialLCD() {
    lcd.setCursor(0, 0);
    lcd.print("Inside:");
    lcd.setCursor(0,1);
    lcd.print("Outside:");
}

void showTempOnLED(float temp) {
    if (temp < LOWER_DECENT_TEMP)
        ledRGB.lightOneColor(BLUE_LED_INDEX);
    else if (temp > UPPER_DECENT_TEMP)
        ledRGB.lightOneColor(RED_LED_INDEX);
    else
        ledRGB.lightOneColor(GREEN_LED_INDEX);
}

void printExtremeTemperaturesOnLcd() {
    lcd.setCursor(0,0);
    lcd.print("Max:    ");

    lcd.setCursor(10, 0);
    char bufferMax[5];
    sprintf(bufferMax, "%5s", String(maxTemp, 1).c_str());
    lcd.print(bufferMax);
    lcd.print("C");

    lcd.setCursor(0,1);
    lcd.print("Min:    ");

    lcd.setCursor(10, 1);
    char bufferMin[5];
    sprintf(bufferMin, "%5s", String(minTemp, 1).c_str());
    lcd.print(bufferMin);
    lcd.print("C");
}

void printTempOnLcd(int row, float temp) {
    lcd.setCursor(10, row);
    char buffer[5];
    sprintf(buffer, "%5s", String(temp, 1).c_str());
    lcd.print(buffer);
    lcd.print("C");
}

void readInitialTemp() {
    sensors.requestTemperatures();
    float tempOutside = sensors.getTempCByIndex(MAIN_SENSOR_IDX);
    tempOutside = getFilteredTempValue(tempOutside);
    minTemp = tempOutside;
    maxTemp = tempOutside;
}

void noteIfExtremeValue(float temp) {
    if (temp < minTemp)
        minTemp = temp;
    else if (temp > maxTemp)
        maxTemp = temp;
}

void setup()
{
    Initializer initializer;
    initializer.initSensors(&sensors);
    initializer.initLCD(&lcd);
    ledRGB.turnOn();

    readInitialTemp();
    printInitialLCD();
}

void switchMenus() {
    if (!isShowingTemperatures) {
        printExtremeTemperaturesOnLcd();
    } else {
        printInitialLCD();
    }
}

unsigned long lastTimeExtremesShown = 0UL;

void loop()
{
    if (redDebounceButton.isPressed()) {
        isShowingTemperatures = !isShowingTemperatures;
        if (!isShowingTemperatures)
            lastTimeExtremesShown = millis();
        switchMenus();
    }
    if (!isShowingTemperatures && millis() - lastTimeExtremesShown > MAX_EXTREME_TEMPERATURES_DISPLAY) {
        isShowingTemperatures = true;
        switchMenus();
    }
    if (isShowingTemperatures && millis() - lastSensorReading > READINGS_WINDOW) {
        lastSensorReading = millis();
        sensors.requestTemperatures();
        float tempOutside = sensors.getTempCByIndex(MAIN_SENSOR_IDX);
        tempOutside = getFilteredTempValue(tempOutside);
        noteIfExtremeValue(tempOutside);

        printTempOnLcd(LCD_ROW_INSIDE, 17.4);
        printTempOnLcd(LCD_ROW_OUTSIDE, tempOutside);
        showTempOnLED(tempOutside);
    }
}