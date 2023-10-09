#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27,16,2);

OneWire oneWire(A1);
DallasTemperature sensors(&oneWire);

#define POTENTIOMETER A0

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define ENCODER1 A2
#define ENCODER2 A3

volatile bool redPressed = false;


void initEncoder()
{
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
}

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

void initSensors()
{
  sensors.begin();
}

//buttons demonstration
void runTask1() {
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  lcd.clear();
  lcd.print("Press a button");
  lcd.setCursor(0, 1);
  delay(1000);
  int b1 = HIGH;
  int b2 = HIGH;
  while ((b1 == HIGH) && (b2 == HIGH))
  {
    b1 = digitalRead(RED_BUTTON);
    if (b1 == LOW) {
      digitalWrite(LED_RED, HIGH);
      lcd.print("RED PRESSED");
    }
    else
      digitalWrite(LED_RED, LOW);

    b2 = digitalRead(GREEN_BUTTON);
    if (b2 == LOW) {
      digitalWrite(LED_GREEN, HIGH);
      lcd.print("GREEN PRESSED");
    }
    else
      digitalWrite(LED_GREEN, LOW);
  }
  delay(1000);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  while ((b1 == LOW) || (b2 == LOW))
  {
    b1 = digitalRead(RED_BUTTON);
    b2 = digitalRead(GREEN_BUTTON);
  }
  delay(1000);
  digitalWrite(LED_BLUE, LOW);
  lcd.clear();
}

//LED PWM presentation - intensity changes on button press
void runTask2() {
  int analogVal = 150;
  analogWrite(LED_RED, analogVal);
  int b1 = HIGH;
  int b2 = HIGH;
  
  while (true) {
    b1 = digitalRead(RED_BUTTON);
    if (b1 == LOW && analogVal < (255 - 10)) {
      analogVal = analogVal + 10;
    }

    b2 = digitalRead(GREEN_BUTTON);
    if (b2 == LOW && analogVal > (0 + 10)) {
      analogVal = analogVal - 10;
    }
    analogWrite(LED_RED, analogVal);
    delay(200);
  }
  analogWrite(LED_RED, 64);
  delay(1000);
  analogWrite(LED_RED, 255);
  delay(1000);
}

void setup() {
  initLCD();
  initRGB();
  initButtons();

  runTask2();
}

void loop() {
  
}