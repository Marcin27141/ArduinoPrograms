#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <util/atomic.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define ENCODER1 A2
#define ENCODER2 A3

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

void initEncoder()
{
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
}

#define DEBOUNCING_PERIOD 100

String menuOptions[] = {
  "LED Red",
  "LED Green",
  "LED Blue",
  "LED White",
  "LED None"
};
int numberOfMenuOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

int menuTopItem = 0;

void printMenu() {
  printMenuOption(0, menuTopItem);
  int nextItem = (menuTopItem + 1) % numberOfMenuOptions;
  printMenuOption(1, nextItem);
}

void printMenuOption(int row, int idx)
{
    char buffer[17];
    sprintf(buffer, "%-16s", menuOptions[idx].c_str());
    lcd.setCursor(0, row);
    lcd.print(buffer);
}

void printResults(int val)
{
    char buffer[40];
    sprintf(buffer, "Encoder: %3d", val);
    lcd.setCursor(2, 0);
    lcd.print(buffer);
}

void myAction(int val)
{
    printResults(val);
    analogWrite(LED_RED, val);
    analogWrite(LED_BLUE, 255 - val);
}

void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(ENCODER1, INPUT_PULLUP);
    pinMode(ENCODER2, INPUT_PULLUP);
    lcd.init();
    lcd.backlight();

    printMenu();

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);
}

volatile int encoder1 = HIGH;
volatile int encoder2 = HIGH;
volatile unsigned long encoderTimestamp = 0UL;

ISR(PCINT1_vect)
{
    encoder1 = digitalRead(ENCODER1);
    encoder2 = digitalRead(ENCODER2);
    encoderTimestamp = millis();
}

int encoderValue = 0;
int lastEn1 = LOW;
unsigned long lastChangeTimestamp = 0UL;


void loop()
{

    int en1;
    int en2;
    unsigned long timestamp;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        en1 = encoder1;
        en2 = encoder2;
        timestamp = encoderTimestamp;
    }

    if (en1 == LOW && timestamp > lastChangeTimestamp + DEBOUNCING_PERIOD)
    {
        if (en2 == HIGH)
        {
            menuTopItem = (menuTopItem + 1) % numberOfMenuOptions;
        }
        else
        {
            menuTopItem = (menuTopItem - 1 < 0) ? numberOfMenuOptions - 1 : menuTopItem - 1;
        }
        printMenu();
        lastChangeTimestamp = timestamp;
    }
    lastEn1 = en1;
}