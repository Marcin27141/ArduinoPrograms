#include <Initializer.h>
#include <DebounceButton.h>
#include <LedRGB.h>
#include <InterruptEncoder.h>
#include <LiquidCrystal_I2C.h>
#include <util/atomic.h>

LiquidCrystal_I2C lcd(0x27,16,2);
LedRGB ledRGB(LED_RED, LED_GREEN, LED_BLUE);
DebounceButton greenDebounceButton(GREEN_BUTTON);
DebounceButton redDebounceButton(RED_BUTTON);
InterruptEncoder encoder;

bool isScrollingMenu = true;
int menuVisibleItem = 0;

int colorIntensities[] = { 0, 0, 0 };
int colors[] = { LED_RED, LED_GREEN, LED_BLUE };

String menuOptions[] = {
  "LED Red",
  "LED Green",
  "LED Blue",
};
const int NUMBER_OF_MENU_OPTIONS = sizeof(menuOptions) / sizeof(menuOptions[0]);

String getColorName(int colorIdx) {
  switch (colorIdx) {
    case RED_LED_INDEX:
      return "RED";
    case GREEN_LED_INDEX:
      return "GREEN";
    case BLUE_LED_INDEX:
      return "BLUE";
    default:
      return "unknown";
  }
}

void printMenuTitle() {
    char buffer[17];
    String title = "RGB intensities";
    sprintf(buffer, "%-16s", title.c_str());
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

void checkMenuScroll() {
    bool wasScrolled = false;
    int scrollDirection = encoder.getDirection();
    if (scrollDirection == TURNED_RIGHT) {
        wasScrolled = true;
        menuVisibleItem = (menuVisibleItem + 1) % NUMBER_OF_MENU_OPTIONS;
    }
    if (scrollDirection == TURNED_LEFT) {
        wasScrolled = true;
        menuVisibleItem = (menuVisibleItem - 1 < 0) ? NUMBER_OF_MENU_OPTIONS - 1 : menuVisibleItem - 1;
    }       
    if (wasScrolled)
        printMenu();
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

void setColorIntensity(int colorIdx) {
  lcd.clear();
  printColorIntensityPercent(getColorName(colorIdx), colorIntensities[colorIdx]);

  while (!redDebounceButton.isPressed()) {
    bool intensityChanged = false;
    int scrollDirection = encoder.getDirection();
    if (scrollDirection == TURNED_RIGHT && colorIntensities[colorIdx] < 255) {
      colorIntensities[colorIdx] += 15;
      intensityChanged = true;
    }
        
    if (scrollDirection == TURNED_LEFT && colorIntensities[colorIdx] > 0) {
        colorIntensities[colorIdx] -= 15; 
        intensityChanged = true;
    }   
    if (intensityChanged) {
      printColorIntensityPercent(getColorName(colorIdx), colorIntensities[colorIdx]);
      analogWrite(colors[colorIdx], colorIntensities[colorIdx]);
    }
      
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
    Initializer initializer = Initializer();
    initializer.initLCD(&lcd);

    printMenu();
    Serial.begin(9600);
}

void loop()
{
  if (isScrollingMenu)
    checkMenuScroll();
  if (isScrollingMenu && greenDebounceButton.isPressed()) {
    isScrollingMenu = false;
    switchToChosenOption();
  }
}