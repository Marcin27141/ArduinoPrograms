// #include <Arduino.h>
// #include <LiquidCrystal_I2C.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>
// #include <Initializer.h>

// LiquidCrystal_I2C lcd(0x27,16,2);
// #define LCD_ROW_INSIDE 0
// #define LCD_ROW_OUTSIDE 1

// // #define LED_RED 6
// // #define LED_GREEN 5
// // #define LED_BLUE 3

// #define ONE_WIRE A1
// OneWire oneWire(ONE_WIRE);
// DallasTemperature sensors(&oneWire);

// DeviceAddress mySensor = { 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFB };
// #define MAIN_SENSOR_IDX 0


// #define MAX_TEMP 125
// #define LOWER_DECENT_TEMP 19
// #define UPPER_DECENT_TEMP 26

// float minTemp;
// float maxTemp;

// void initLCD()
// {
//   lcd.init();
//   lcd.clear();
//   lcd.backlight();
// }

// void initRGB()
// {
//   pinMode(LED_RED, OUTPUT);
//   pinMode(LED_GREEN, OUTPUT);
//   pinMode(LED_BLUE, OUTPUT);
// }

// void printSerialNumber(int sensorIdx) {
//     DeviceAddress tempDeviceAddress;
//     sensors.getAddress(tempDeviceAddress, sensorIdx);

//     Serial.print("Serial number: ");
//     for (uint8_t j = 0; j < 8; j++) {
//       Serial.print(tempDeviceAddress[j], HEX);
//       Serial.print(" ");
//     }
//     Serial.println();
// }

// float getFilteredTempValue(float reading) {
//     if (reading > MAX_TEMP) return 0;
//     return reading;
// }

// void identifySensorsByTemp() {
//   sensors.requestTemperatures();
//   float temp0 = sensors.getTempCByIndex(0);
//   float temp1 = sensors.getTempCByIndex(1);

//   Serial.print("Sensor 0: ");
//   printSerialNumber(0);
//   Serial.print("Temperature: ");
//   Serial.print(temp0);
//   Serial.println(" Celsius");

//   Serial.print("Sensor 1: ");
//   printSerialNumber(1);
//   Serial.print("Temperature: ");
//   Serial.print(temp1);
//   Serial.println(" Celsius");
// }

// void printInitialLCD() {
//     lcd.setCursor(0, 0);
//     lcd.print("Inside:");
//     lcd.setCursor(0,1);
//     lcd.print("Outside:");
// }

// void turnOffLED() {
//     digitalWrite(LED_RED, LOW);
//     digitalWrite(LED_GREEN, LOW);
//     digitalWrite(LED_BLUE, LOW);
// }

// void showTempOnLED(float temp) {
//     turnOffLED();
//     if (temp < LOWER_DECENT_TEMP)
//         digitalWrite(LED_BLUE, HIGH);
//     else if (temp > UPPER_DECENT_TEMP)
//         digitalWrite(LED_RED, HIGH);
//     else
//         digitalWrite(LED_GREEN, HIGH);
// }

// void printTempOnLcd(int row, float temp) {
//     // lcd.setCursor(8, row);
//     // char buffer[40];
//     // sprintf(buffer, "%8s", String(temp, 4).c_str());
//     lcd.setCursor(10, row);
//     char buffer[5];
//     sprintf(buffer, "%5s", String(temp, 1).c_str());
//     lcd.print(buffer);
//     lcd.print("C");
// }

// void readInitialTemp() {
//     sensors.requestTemperatures();
//     float tempOutside = sensors.getTempCByIndex(MAIN_SENSOR_IDX);
//     tempOutside = getFilteredTempValue(tempOutside);
//     minTemp = tempOutside;
//     maxTemp = tempOutside;
// }

// void noteIfExtremeValue(float temp) {
//     if (temp < minTemp)
//         minTemp = temp;
//     else if (temp > maxTemp)
//         maxTemp = temp;
// }

// void setup()
// {
//     sensors.begin();
//     initLCD();

//     readInitialTemp();
//     printInitialLCD();
// }

// void loop()
// {
//   sensors.requestTemperatures();
//   float tempOutside = sensors.getTempCByIndex(MAIN_SENSOR_IDX);
//   tempOutside = getFilteredTempValue(tempOutside);
//   noteIfExtremeValue(tempOutside);
//   //float temperatureFahrenheit = sensors.toFahrenheit(temperatureCelsius);

//   printTempOnLcd(LCD_ROW_INSIDE, 17.4);
//   printTempOnLcd(LCD_ROW_OUTSIDE, tempOutside);
//   showTempOnLED(tempOutside);
//   delay(1000);
// }