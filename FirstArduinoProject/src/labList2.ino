#include <Initializer.h>
#include <DebounceButton.h>
#include <LedRGB.h>

//----------------------task1------------------------
//green button changes color, red button turns on/off
// int leds[] = {LED_RED, LED_GREEN, LED_BLUE};
// const int LED_RED_INDEX = 0;
// const int LED_GREEN_INDEX = 1;
// const int LED_BLUE_INDEX = 2;
// int currectLedOn;
// bool turnedOn = true;;

LiquidCrystal_I2C* lcd;
LedRGB* ledRGB;
DebounceButton* greenDebounceButton;
DebounceButton* redDebounceButton;

void initializeForTask1() {
  ledRGB->setActiveColor(RED_LED_INDEX);
  ledRGB->turnOn();

  lcd->setCursor(0, 0);
  lcd->print("GREEN: COLOR");
  lcd->setCursor(0, 1);
  lcd->print("RED: TURN ON/OFF");
}

void runTask1() {
  static int currentLedOn = RED_LED_INDEX;

  while (true)
  {
    if (redDebounceButton->isPressed()) {
        ledRGB->turnState();
    }
    if (greenDebounceButton->isPressed()) {
        currentLedOn = ledRGB->setFollowingColor(currentLedOn);
        ledRGB->showColorsIfTurnedOn();
    }
  }
}

void setup() {
  Initializer initializer = Initializer();
  initializer.initRGB();
  initializer.initButtons();
  initializer.initLCD();

  lcd = initializer.getLCD();
  ledRGB = new LedRGB(LED_RED, LED_GREEN, LED_BLUE);
  greenDebounceButton = new DebounceButton(GREEN_BUTTON);
  redDebounceButton = new DebounceButton(RED_BUTTON);

  initializeForTask1();
  runTask1();
}

void loop() {
}

//------------------------task2-----------------------------
//LED PWM presentation - red button makes led darker, green button - brighter

// void initializeForTask2(int analogVal) {
//   lcd.clear();
//   lcd.print("GREEN: BRIGHTER");
//   lcd.setCursor(0, 1);
//   lcd.print("RED: DARKER");

//   analogWrite(LED_GREEN, analogVal);
// }

// void runTask2() {
//   int analogVal = 150;
//   int redBtn = HIGH;
//   int greenBtn = HIGH;
//   initializeForTask2(analogVal);
  
//   while (true) {
//     greenBtn = digitalRead(GREEN_BUTTON);
//     if (greenBtn == LOW && analogVal < (255 - 10)) {
//       analogVal = analogVal + 10;
//     }

//     redBtn = digitalRead(RED_BUTTON);
//     if (redBtn == LOW && analogVal > (0 + 10)) {
//       analogVal = analogVal - 10;
//     }
//     analogWrite(LED_GREEN, analogVal);
//     delay(200);
//   }
// }

// //------------------------task3-----------------------------
// //on green button press, led fluently changes colors: red, green, blue, red, ... 

// int singleStep = 255/100;
// int redAnalogVal = 255;
// int greenAnalogVal = 0;
// int blueAnalogVal = 0;

// void initializeForTask3() {
//   lcd.clear();
//   lcd.print("PRESS GREEN TO");
//   lcd.setCursor(0, 1);
//   lcd.print("CHANGE COLOR");

//   analogWrite(LED_RED, redAnalogVal);
// }

// void runTask3() {
//   int greenBtn = HIGH;
//   initializeForTask3();
  
//   while (true) {
//     greenBtn = digitalRead(GREEN_BUTTON);
//     if (greenBtn == LOW) {
//       changeColorIntensity();
//       showUpdatedIntensity();
//     }
    
//     delay(45);
//   }
// }

// void changeColorIntensity() {
//   if (redAnalogVal > singleStep && blueAnalogVal <= singleStep) {
//     redAnalogVal -= singleStep;
//     greenAnalogVal += singleStep;
//   }
//   else if (greenAnalogVal > singleStep) {
//     greenAnalogVal -= singleStep;
//     blueAnalogVal += singleStep;
//   }
//   else if (blueAnalogVal > singleStep) {
//     blueAnalogVal -= singleStep;
//     redAnalogVal += singleStep;
//   }
// }

// void showUpdatedIntensity() {
//   analogWrite(LED_RED, redAnalogVal);
//   analogWrite(LED_GREEN, greenAnalogVal);
//   analogWrite(LED_BLUE, blueAnalogVal);
// }