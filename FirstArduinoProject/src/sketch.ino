#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

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


void setup() {
  initLCD();
  initRGB();
  initButtons();

  testButtons2();
}

void loop() {
}