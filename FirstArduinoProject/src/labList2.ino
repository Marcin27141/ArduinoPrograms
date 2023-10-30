#include <Initializer.h>

//#include <Arduino.h>
// #include <LiquidCrystal_I2C.h>
// #include <Wire.h>
// #include <OneWire.h>
// #include <DallasTemperature.h>

// LiquidCrystal_I2C lcd(0x27,16,2);

// OneWire oneWire(A1);
// DallasTemperature sensors(&oneWire);

// #define POTENTIOMETER A0

// #define LED_RED 6
// #define LED_GREEN 5
// #define LED_BLUE 3

// #define RED_BUTTON 2
// #define GREEN_BUTTON 4

// #define ENCODER1 A2
// #define ENCODER2 A3

// volatile bool redPressed = false;


// void initEncoder()
// {
//   pinMode(ENCODER1, INPUT_PULLUP);
//   pinMode(ENCODER2, INPUT_PULLUP);
// }

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

// void initButtons()
// {
//   pinMode(RED_BUTTON, INPUT_PULLUP);
//   pinMode(GREEN_BUTTON, INPUT_PULLUP);
// }

// void initSensors()
// {
//   sensors.begin();
// }

//----------------------task1------------------------
//green button changes color, red button turns on/off

int greenBtn = HIGH;
int redBtn = HIGH;
bool turnedOn = true;
int redState = HIGH;
int greenState = LOW;
int blueState = LOW;

void initializeForTask1(Initializer initializer) {
  initializer.initLCD();
  LiquidCrystal_I2C lcd = initializer.getLCD();
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  lcd.setCursor(0, 0);
  lcd.print("GREEN: COLOR");
  lcd.setCursor(0, 1);
  lcd.print("RED: TURN ON/OFF");
}

void runTask1() {
  int delayTime = 400;
  
  delay(delayTime);

  while (true)
  {
    redBtn = digitalRead(RED_BUTTON);
    if (redBtn == LOW) {
      turnLeds();
      delay(delayTime);
    }

    greenBtn = digitalRead(GREEN_BUTTON);
    if (greenBtn == LOW) {
      switchColor();
      if (turnedOn)
        showColor();
      delay(delayTime);
    }
  }
}

void switchColor() {
  if (redState == HIGH) {
    redState = LOW;
    greenState = HIGH;
  }
  else if (greenState == HIGH) {
    greenState = LOW;
    blueState = HIGH;
  }
  else if (blueState == HIGH) {
    blueState = LOW;
    redState = HIGH;
  }
}

void showColor() {
  digitalWrite(LED_RED, redState);
  digitalWrite(LED_GREEN, greenState);
  digitalWrite(LED_BLUE, blueState);
}

void turnLeds() {
  if (turnedOn == true) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
    turnedOn = false;
  } else {
    digitalWrite(LED_RED, redState);
    digitalWrite(LED_GREEN, greenState);
    digitalWrite(LED_BLUE, blueState);
    turnedOn = true;
  }
}

void setup() {
  Initializer initializer = Initializer();
  initializer.initRGB();
  initializer.initButtons();

  initializeForTask1(initializer);
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

// //--------------------------main------------------