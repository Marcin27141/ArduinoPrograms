#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void initLCD()
{
  lcd.init();
  lcd.clear();
  lcd.backlight();
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

void setup() {
  initLCD();
  testLCD();
  /*lcd.setCursor(2,0);
  lcd.print("Hello world!");
  
  lcd.setCursor(2,1);
  lcd.print("LCD Tutorial");*/
}

void loop() {}