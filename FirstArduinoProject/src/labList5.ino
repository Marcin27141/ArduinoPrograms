#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <util/atomic.h>
#include <Initializer.h>

LiquidCrystal_I2C lcd(0x27,16,2);

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

#define BUTTON_DEBOUNCE_PERIOD 100
#define DEBOUNCING_PERIOD 100
bool isScrollingMenu = true;

int colorIntensities[] = { 0, 0, 0 };
int colors[] = { LED_RED, LED_GREEN, LED_BLUE };

String getColorName(int colorIdx) {
  switch (colorIdx) {
    case 0:
      return "RED";
    case 1:
      return "GREEN";
    case 2:
      return "BLUE";
    default:
      return "unknown";
  }
}

String menuOptions[] = {
  "LED Red",
  "LED Green",
  "LED Blue",
};
int numberOfMenuOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

int menuVisibleItem = 0;

void printMenuTitle() {
    char buffer[17];
    String title = "Sterowanie RGB";
    sprintf(buffer, "%-14s", title.c_str());
    lcd.setCursor(0, 0);
    lcd.print(buffer);
}

int getPercentOfIntensity(int intensity) {
    return intensity * 100 / 255;
}

String getMenuOptionText(int optionIdx) {
    return menuOptions[optionIdx] + " " + getPercentOfIntensity(colorIntensities[optionIdx]) + "%";
}

void printScrollableMenuOption() {
    String menuOption = getMenuOptionText(menuVisibleItem);
    char buffer[17];
    sprintf(buffer, "%-16s", menuOption.c_str());
    lcd.setCursor(0, 1);
    lcd.print(buffer);
}

void printMenu() {
    printMenuTitle();
    printScrollableMenuOption();
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

void checkMenuScroll() {
    int en1;
    int en2;
    unsigned long timestamp;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        en1 = encoder1;
        en2 = encoder2;
        timestamp = encoderTimestamp;
    }

    if (en1 == LOW && timestamp > lastChangeTimestamp + BUTTON_DEBOUNCE_PERIOD)
    {
        if (en2 == HIGH)
        {
            menuVisibleItem = (menuVisibleItem + 1) % numberOfMenuOptions;
        }
        else
        {
            menuVisibleItem = (menuVisibleItem - 1 < 0) ? numberOfMenuOptions - 1 : menuVisibleItem - 1;
        }
        printMenu();
        lastChangeTimestamp = timestamp;
    }
    lastEn1 = en1;
}

#define ENCODER_DEBOUNCE_PERIOD 10UL
int buttons[] = {GREEN_BUTTON, RED_BUTTON};
int debouncedStates[] = {HIGH, HIGH};
int previousReadings[] = {HIGH, HIGH};
unsigned long lastChanged[] = {0UL, 0UL};

bool isButtonPressed(int buttonIdx) {
    bool isPressed = false;
    int current_reading = digitalRead(buttons[buttonIdx]);

    if (previousReadings[buttonIdx] != current_reading)
    {
        lastChanged[buttonIdx] = millis();
    }

    if (millis() - lastChanged[buttonIdx] > ENCODER_DEBOUNCE_PERIOD)
    {
        if(current_reading != debouncedStates[buttonIdx])
        {
            if (debouncedStates[buttonIdx] == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debouncedStates[buttonIdx] = current_reading;
        }
    }

    previousReadings[buttonIdx] = current_reading;
    return isPressed;
}

void printColorIntensityPercent(String color, int val)
{
    char buffer[40];
    lcd.setCursor(0, 0);
    lcd.print(color);
    lcd.setCursor(0, 1);
    sprintf(buffer, "Percent: %3d", getPercentOfIntensity(val));
    lcd.print(buffer);
}

bool isSettingIntensity = false;

int intensityValue = 0;
int lastEn1Intensity = LOW;
unsigned long lastIntensityChangeTimestamp = 0UL;

void setColorIntensity(int colorIdx) {
  lcd.clear();
  printColorIntensityPercent(getColorName(colorIdx), colorIntensities[colorIdx]);
  isSettingIntensity = true;

  while (!isButtonPressed(1)) {
    int en1;
    int en2;
    unsigned long timestamp;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        en1 = encoder1;
        en2 = encoder2;
        timestamp = encoderTimestamp;
    }

    if (en1 == LOW && lastEn1 == HIGH && timestamp > lastIntensityChangeTimestamp + DEBOUNCING_PERIOD)
    {
        if (en2 == HIGH)
        {
            if (colorIntensities[colorIdx] < 255)
                colorIntensities[colorIdx] += 15;
        }
        else
        {
            if (colorIntensities[colorIdx] > 0)
                colorIntensities[colorIdx] -= 15;
        }
        lastIntensityChangeTimestamp = timestamp;

        printColorIntensityPercent(getColorName(colorIdx), colorIntensities[colorIdx]);
        analogWrite(colors[colorIdx], colorIntensities[colorIdx]);
    }
    lastEn1Intensity = en1;
  }
}

void goBackToMenu() {
    isScrollingMenu = true;
    lcd.clear();
    printMenu();
}

void switchToChosenOption() {
  switch (menuVisibleItem) {
    case 0:
      setColorIntensity(0);
      break;
    case 1:
      setColorIntensity(1);
      break;
    case 2:
      setColorIntensity(2);
      break;
    default:
      break;
  }
  goBackToMenu();
}

void setup()
{
    initButtons();
    initRGB();
    initEncoder();
    initLCD();

    printMenu();

    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT10);
}

void loop()
{
  if (isScrollingMenu)
    checkMenuScroll();
  if (isScrollingMenu && isButtonPressed(0)) {
    isScrollingMenu = false;
    switchToChosenOption();
  }
}