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

void setRedPressed()
{
  redPressed = true;
}

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

void testLCD()
{
  lcd.print("LCD Test");
  lcd.setCursor(1, 1);
  lcd.print("Wait & watch");
  delay(1000);
  for (int i = 0; i < 3; i++)
  {
    lcd.noBacklight();
    delay(200);
    lcd.backlight();
    delay(200);
  }
  delay(1000);
  lcd.clear();
}

void testRGB()
{
  lcd.print("RGB LED Test");
  lcd.setCursor(0, 1);
  lcd.print("Check R>G>B>R>..");

  delay(1000);
  const int time = 500;

  for (int i = 0; i < 2; i++)
  {
    digitalWrite(LED_RED, HIGH);
    delay(time);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    delay(time);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
    delay(time);
    digitalWrite(LED_BLUE, LOW);
  }
  lcd.clear();
}

void testButtons1()
{
  lcd.print("Buttons: Press");
  lcd.setCursor(0, 1);
  lcd.print("Red & Green Btns");
  delay(1000);
  int b1 = HIGH;
  int b2 = HIGH;
  while ((b1 == HIGH) || (b2 == HIGH))
  {
    b1 = digitalRead(RED_BUTTON);
    if (b1 == LOW)
      digitalWrite(LED_RED, HIGH);
    else
      digitalWrite(LED_RED, LOW);

    b2 = digitalRead(GREEN_BUTTON);
    if (b2 == LOW)
      digitalWrite(LED_GREEN, HIGH);
    else
      digitalWrite(LED_GREEN, LOW);
  }
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  while ((b1 == LOW) || (b2 == LOW))
  {
    b1 = digitalRead(RED_BUTTON);
    b2 = digitalRead(GREEN_BUTTON);
  }
  digitalWrite(LED_BLUE, LOW);
  lcd.clear();
}

void testButtons2()
{
  lcd.print("Buttons: Press");
  lcd.setCursor(0, 1);
  lcd.print("Red & Green Btns");
  bool redPressed = false;
  bool greenPressed = false;

  while (!redPressed || !greenPressed)
  {
    if (digitalRead(RED_BUTTON) == LOW)
    {
      redPressed = true;
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
    }
    if (digitalRead(GREEN_BUTTON) == LOW)
    {
      greenPressed = true;
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED, LOW);
    }
  }

  delay(1000);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  lcd.clear();
}

void testEncoder()
{
  lcd.print("Encoder: ");
  lcd.setCursor(0, 1);
  lcd.print("Turn encoder");
  delay(1000);
  int state1 = digitalRead(ENCODER1);
  int state2 = digitalRead(ENCODER2);
  int counter1 = 0, counter2 = 0;
  int e1, e2;
  bool ledRedState = LOW;
  bool ledGreenState = LOW;
  while (counter1 < 4 || counter2 < 4)
  {
    e1 = digitalRead(ENCODER1);
    e2 = digitalRead(ENCODER2);

    if (state1 != e1 && e1 == HIGH) {
      if (e1 != e2) {
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
      }
      else {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
      }
    }
    
    if (state1 != e1 & e1 == HIGH)
    {
      if (e1 != e2)
      {
        counter1++;
        Serial.print("counter 1 increased: ");
      }
      else {
        counter2++;
        Serial.print("counter 2 increased: ");
      }
    }
    state1 = e1;

  }
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
  digitalWrite(LED_BLUE, LOW);

  lcd.clear();
}

void testPotencjometer()
{
  lcd.print("Potenciometer: ");
  lcd.setCursor(0, 1);
  lcd.print("Turn full range");

  int refval = analogRead(POTENTIOMETER);
  int val = refval;
  while (refval - 10 < val & val < refval + 10)
  {
    val = analogRead(POTENTIOMETER);
  }

  int min = val;
  int max = val;

  lcd.clear();
  lcd.print("Potentiometer");
  while (min > 100 || max < 1023 - 100)
  {
    val = analogRead(POTENTIOMETER); // read the input pin
    //Serial.println(val);
    lcd.setCursor(5, 1);
    lcd.print("ADC =     ");
    lcd.setCursor(11, 1);
    lcd.print(val);

    if (val < min)
    {
      min = val;
    }

    if (val > max)
    {
      max = val;
    }

    delay(20);
  }
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
  digitalWrite(LED_BLUE, LOW);
  lcd.clear();
}

void initSensors()
{
  sensors.begin();
}

void testSensors()
{
  lcd.clear();
  lcd.print("Temp. 1|Temp. 2");
  lcd.setCursor(0, 1);
  lcd.print("Stop: Red Btn");
  delay(2000);
  lcd.clear();
  lcd.print("Temp. 1|Temp. 2");

  EIFR |= (1 << INTF0);
  attachInterrupt(digitalPinToInterrupt(RED_BUTTON), setRedPressed, FALLING);
  redPressed = false;
  while (redPressed == false)
  {
    sensors.requestTemperatures();
    float temp1 = sensors.getTempCByIndex(0);
    float temp2 = sensors.getTempCByIndex(1);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(temp1);
    lcd.print("  |");
    lcd.print(temp2);

    Serial.print("Temp. 1 = ");
    Serial.print(temp1);
    Serial.print(" Temp. 2 = ");
    Serial.println(temp2);
  }
  detachInterrupt(digitalPinToInterrupt(RED_BUTTON));
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
  digitalWrite(LED_BLUE, LOW);
  lcd.clear();
}

void setup() {
  initLCD();
  initRGB();
  initButtons();
  initEncoder();
  initSensors();

  testSensors();
}

void loop() {
}