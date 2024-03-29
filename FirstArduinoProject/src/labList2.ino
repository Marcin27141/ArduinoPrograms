#include <Initializer.h>
#include <DebounceButton.h>
#include <LedRGB.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//----------------------task1------------------------
//green button changes color, red button turns on/off
LedRGB ledRGB(LED_RED, LED_GREEN, LED_BLUE);
DebounceButton greenDebounceButton(GREEN_BUTTON);
DebounceButton redDebounceButton(RED_BUTTON);

void initializeForTask1() {
  ledRGB.setActiveColor(RED_LED_INDEX);
  ledRGB.turnOn();

  lcd.setCursor(0, 0);
  lcd.print("GREEN: COLOR");
  lcd.setCursor(0, 1);
  lcd.print("RED: TURN ON/OFF");
}

void runTask1() {
  int currentLedOn = RED_LED_INDEX;

  while (true)
  {
    if (redDebounceButton.isPressed()) {
        ledRGB.turnState();
    }
    if (greenDebounceButton.isPressed()) {
        currentLedOn = ledRGB.setFollowingColor(currentLedOn);
        ledRGB.showColorsIfTurnedOn();
    }
  }
}

void setup() {
  Initializer initializer = Initializer();
  initializer.initLCD(&lcd);

  initializeForTask1();
  runTask1();
}

void loop() {
}

//------------------------task2-----------------------------
//LED PWM presentation - red button makes led darker, green button - brighter
LedRGB ledRGB(LED_RED, LED_GREEN, LED_BLUE);
DebounceButton greenDebounceButton(GREEN_BUTTON);
DebounceButton redDebounceButton(RED_BUTTON);

void initializeForTask2() {
  lcd.setCursor(0, 0);
  lcd.print("GREEN: BRIGHTER");
  lcd.setCursor(0, 1);
  lcd.print("RED: DARKER");

  ledRGB.setActiveColor(GREEN_LED_INDEX);
  ledRGB.turnOn();
}

void runTask2() {
  int analogVal = 255;
  
  while (true) {
    if (greenDebounceButton.isPressed() && analogVal <= (255 - 15))
      analogVal += 15;

    if (redDebounceButton.isPressed() && analogVal >= 15)
      analogVal -= 15;

    ledRGB.lightOneColor(GREEN_LED_INDEX, analogVal);
  }
}

void setup() {
  Initializer initializer = Initializer();
  initializer.initLCD(&lcd);

  initializeForTask2();
  runTask2();
}

void loop() {
}

//------------------------task3-----------------------------
//on green button press, led fluently changes colors: red, green, blue, red, ... 
LedRGB ledRGB(LED_RED, LED_GREEN, LED_BLUE);
DebounceButton greenDebounceButton(GREEN_BUTTON);
DebounceButton redDebounceButton(RED_BUTTON);

int singleStep = 15;
int redAnalogVal = 255;
int greenAnalogVal = 0;
int blueAnalogVal = 0;

void initializeForTask3() {
  lcd.clear();
  lcd.print("PRESS GREEN TO");
  lcd.setCursor(0, 1);
  lcd.print("CHANGE COLOR");

  ledRGB.lightOneColor(RED_LED_INDEX, redAnalogVal);
  ledRGB.turnOn();
}

void runTask3() {  
  while (true) {
    if (greenDebounceButton.isPressed()) {
      changeColorIntensity();
      showUpdatedIntensity();
    }
  }
}

void changeColorIntensity() {
  if (redAnalogVal >= singleStep && blueAnalogVal == 0) {
    redAnalogVal -= singleStep;
    greenAnalogVal += singleStep;
  }
  else if (greenAnalogVal >= singleStep) {
    greenAnalogVal -= singleStep;
    blueAnalogVal += singleStep;
  }
  else if (blueAnalogVal >= singleStep) {
    blueAnalogVal -= singleStep;
    redAnalogVal += singleStep;
  }
}

void showUpdatedIntensity() {
  ledRGB.lightColor(RED_LED_INDEX, redAnalogVal);
  ledRGB.lightColor(GREEN_LED_INDEX, greenAnalogVal);
  ledRGB.lightColor(BLUE_LED_INDEX, blueAnalogVal);
}

void setup() {
  Initializer initializer = Initializer();
  initializer.initLCD(&lcd);

  initializeForTask3();
  runTask3();
}

void loop() {
}