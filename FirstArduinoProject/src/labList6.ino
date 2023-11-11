#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define ONE_WIRE A1
OneWire oneWire(ONE_WIRE);
DallasTemperature sensors(&oneWire);

DeviceAddress mySensor = { 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFB };
#define MAIN_SENSOR_IDX 0
#define LCD_ROW_INSIDE 0
#define LCD_ROW_OUTSIDE 1

#define MAX_TEMP 125

void initLCD()
{
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void printSerialNumber(int sensorIdx) {
    DeviceAddress tempDeviceAddress;
    sensors.getAddress(tempDeviceAddress, sensorIdx);

    Serial.print("Serial number: ");
    for (uint8_t j = 0; j < 8; j++) {
      Serial.print(tempDeviceAddress[j], HEX);
      Serial.print(" ");
    }
    Serial.println();
}

void identifySensorsByTemp() {
  sensors.requestTemperatures();
  float temp0 = sensors.getTempCByIndex(0);
  float temp1 = sensors.getTempCByIndex(1);

  Serial.print("Sensor 0: ");
  printSerialNumber(0);
  Serial.print("Temperature: ");
  Serial.print(temp0);
  Serial.println(" Celsius");

  Serial.print("Sensor 1: ");
  printSerialNumber(1);
  Serial.print("Temperature: ");
  Serial.print(temp1);
  Serial.println(" Celsius");
}

void printInitialLCD() {
    lcd.setCursor(0, 0);
    lcd.print("Inside:");
    lcd.setCursor(0,1);
    lcd.print("Outside:");
}

void printTempOnLcd(int row, float temp) {
    // lcd.setCursor(8, row);
    // char buffer[40];
    // sprintf(buffer, "%8s", String(temp, 4).c_str());
    if (temp > MAX_TEMP) temp = 0;
    lcd.setCursor(11, row);
    char buffer[5];
    sprintf(buffer, "%5s", String(temp, 1).c_str());
    lcd.print(buffer);
}

void setup()
{
    sensors.begin();
    initLCD();
    printInitialLCD();
}

void loop()
{
  sensors.requestTemperatures();
  float temperatureCelsius = sensors.getTempCByIndex(MAIN_SENSOR_IDX);
  //float temperatureFahrenheit = sensors.toFahrenheit(temperatureCelsius);
  printTempOnLcd(LCD_ROW_INSIDE, 17.4);
  printTempOnLcd(LCD_ROW_OUTSIDE, temperatureCelsius);
  delay(1000);
}