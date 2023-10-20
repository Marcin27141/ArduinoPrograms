#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

void initLCD()
{
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void initRGB()
{

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void initButtons()
{
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

//task 1
//notify button states using Serial
// #define DEBOUNCE_PERIOD 10UL
// int buttons[] = {GREEN_BUTTON, RED_BUTTON};
// int debouncedStates[] = {HIGH, HIGH};
// int previousReadings[] = {HIGH, HIGH};
// unsigned long lastChanged[] = {0UL, 0UL};

// bool notifyButtonsStateChanges(int buttonId) {
//     bool isPressed = false;
//     int current_reading = digitalRead(buttons[buttonId]);

//     if (previousReadings[buttonId] != current_reading)
//     {
//         lastChanged[buttonId] = millis();
//     }

//     if (millis() - lastChanged[buttonId] > DEBOUNCE_PERIOD)
//     {
//         if(current_reading != debouncedStates[buttonId])
//         {
//             String buttonColor = buttonId == 0 ? "Green" : "Red";
//             if (debouncedStates[buttonId] == HIGH && current_reading == LOW)
//             {
//                 isPressed = true;
//                 Serial.println(buttonColor + " button pushed");
//             }
//             else {
//               Serial.println(buttonColor + " button released");
//             }
//             debouncedStates[buttonId] = current_reading;
//         }
//     }

//     previousReadings[buttonId] = current_reading;
//     return isPressed;
// }

// void setup() {
//   initButtons();

//   Serial.begin(9600);
//   while (!Serial) {
//   }
// }


// void loop() {
//   for (int i = 0; i < 2; i++)
//     notifyButtonsStateChanges(i);
// }

//task 2
//light RGB led colors based on Serial input
// bool isValidNumber(String input) {
//   int result = input.toInt();
//   return input == "0" || (result > 0 && result <= 255);
// }

// bool validatePassedValues(String r, String g, String b) {
//   String notValidMessage = " is not a valid number. Put a number from 0 to 255";

//   if (!isValidNumber(r)) {
//     Serial.println(r + notValidMessage);
//     return false;
//   }
//   if (!isValidNumber(g)) {
//     Serial.println(g + notValidMessage);
//     return false;
//   }
//   if (!isValidNumber(b)) {
//     Serial.println(b + notValidMessage);
//     return false;
//   }
//   return true;
// }

// void printSuccessfulCommand(int r_intensity, int g_intensity, int b_intensity) {
//   Serial.print(r_intensity);
//   Serial.print(" ");
//   Serial.print(g_intensity);
//   Serial.print(" ");
//   Serial.println(b_intensity);
// }

// void setup()
// {
//     initRGB();
//     Serial.begin(9600);
//     while (!Serial)
//     {
//     }
// }

// //message format: red_percent, green_percent, blue_percent
// void loop()
// {
//     if (Serial.available() > 0)
//     {
//         String command = Serial.readStringUntil('\n');
//         command.trim();
//         int space1 = command.indexOf(' ');
//         int space2 = command.indexOf(' ', space1 + 1);
//         int space3 = command.indexOf(' ', space2 + 1);

//         if (space1 == -1 || space2 == -1 || space3 != -1) {
//           Serial.println("Incorrect line format. Separate 3 intensity values with single spaces");
//         }
//         else {
//           String r_str = command.substring(0, space1);
//           String g_str = command.substring(space1 + 1, space2);
//           String b_str = command.substring(space2 + 1);

//           bool valuesAreValid = validatePassedValues(r_str, g_str, b_str);
//           if (valuesAreValid) {
//             int r_intensity = r_str.toInt();
//             int g_intensity = g_str.toInt();
//             int b_intensity = b_str.toInt();

//             analogWrite(LED_RED, r_intensity);
//             analogWrite(LED_GREEN, g_intensity);
//             analogWrite(LED_BLUE, b_intensity);
//             printSuccessfulCommand(r_intensity, g_intensity, b_intensity);
//           }
//         }

        
//     }
// }

//zadanie 3
//showing on lcd potentiometer real and read value

void printValuesOnLcd(int sensor, float real) {
  lcd.setCursor(12, 0);
  char paddedSensorValue[5];
  sprintf(paddedSensorValue, "%4d", sensor);
  lcd.print(paddedSensorValue);

  lcd.setCursor(12, 1);
  char paddedRealValue[10];
  dtostrf(real, 3, 2, paddedRealValue);
  lcd.print(paddedRealValue);
}



void setup()
{
  initLCD();

  lcd.setCursor(0, 0);
  lcd.print("Sensor:");
  lcd.setCursor(0, 1);
  lcd.print("Real:");

  Serial.begin(9600);
}

#define REF_VOLTAGE 5.0
#define RESOLUTION 1024

int sensorValue = 0; 
float sensorRealValue = 0;

void loop()
{
    sensorValue = analogRead(POTENTIOMETER);
    sensorRealValue = REF_VOLTAGE / RESOLUTION * sensorValue;
    printValuesOnLcd(sensorValue, sensorRealValue);
}
