#include <Initializer.h>
#include <DebounceButton.h>
#include <LedRGB.h>

//taks 1
//switch led into R>G>B>R>... whenever red or green button is pressed
// LedRGB* ledRGB;
// int led_index = RED_LED_INDEX;
// DebounceButton* greenDebounceButton;
// DebounceButton* redDebounceButton;

// void setup()
// {
//     Initializer initializer = Initializer();
//     initializer.initRGB();
//     initializer.initButtons();

//     ledRGB = new LedRGB(LED_RED, LED_GREEN, LED_BLUE);
//     greenDebounceButton = new DebounceButton(GREEN_BUTTON);
//     redDebounceButton = new DebounceButton(RED_BUTTON);

//     ledRGB->turnOn();
//     ledRGB->lightColor(RED_LED_INDEX);
// }


// void loop()
// {
//     for (int i = 0; i < 2; i++)
//         if (greenDebounceButton->isPressed() || redDebounceButton->isPressed()) {
//             led_index = ledRGB->setFollowingColor(led_index);
//             ledRGB->lightColor(led_index);
//         }
// }

//task 2
//"simultaneously" changing led lights
// LedRGB* ledRGB;
// int colorIndexes[] { RED_LED_INDEX, GREEN_LED_INDEX, BLUE_LED_INDEX };
// unsigned long lastChanged[] = {0UL, 0UL, 0UL};
// unsigned long turnTimes[] = {900UL, 1000UL, 1100UL};

// void setup()
// {
//     Initializer initializer = Initializer();
//     initializer.initRGB();

//     ledRGB = new LedRGB(LED_RED, LED_GREEN, LED_BLUE);
//     ledRGB->turnOn();
// }

// void blinkLedIfTime(int idx) {
//   if (millis() - lastChanged[idx] >= turnTimes[idx])
//   {
//     ledRGB->turnColor(colorIndexes[idx]);
//     lastChanged[idx] = millis();
//   }
// }


// void loop()
// {
//   for (int i = 0; i < 3; i++) {
//     blinkLedIfTime(i);
//   }
// }

//task 3
//stopwatch program, green button stops/resumes, red button resets
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long lastTimeTurnedOn = 0UL;
unsigned long timeElapsed = 0UL;
bool stopwatchRunning = false;

int getSecondsFromBeginning() {
  return (timeElapsed + millis() - lastTimeTurnedOn)/1000;
}

void printMillisFromStart() {
  lcd.setCursor(0, 1);
  lcd.print(getSecondsFromBeginning());
}

#define DEBOUNCE_PERIOD 10UL
int buttons[] = {GREEN_BUTTON, RED_BUTTON};
int debouncedStates[] = {HIGH, HIGH};
int previousReadings[] = {HIGH, HIGH};
unsigned long lastChanged[] = {0UL, 0UL};

bool isButtonPressed(int buttonId) {
    bool isPressed = false;
    int current_reading = digitalRead(buttons[buttonId]);

    if (previousReadings[buttonId] != current_reading)
    {
        lastChanged[buttonId] = millis();
    }

    if (millis() - lastChanged[buttonId] > DEBOUNCE_PERIOD)
    {
        if(current_reading != debouncedStates[buttonId])
        {
            if (debouncedStates[buttonId] == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debouncedStates[buttonId] = current_reading;
        }
    }

    previousReadings[buttonId] = current_reading;
    return isPressed;
}

void switchTheStopwatchState() {
  if (stopwatchRunning == false) {
    lastTimeTurnedOn = millis();
    stopwatchRunning = true;
  }
  else {
    timeElapsed += (millis() - lastTimeTurnedOn);
    stopwatchRunning = false;
  }
}

void resetStopwatch() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  stopwatchRunning = false;
  lastTimeTurnedOn = 0UL;
  timeElapsed = 0UL;
}

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);

  lcd.print("Time elapsed:");
}

int greenButtonId = 0;
int redButtonId = 1;

void loop() {
  if (isButtonPressed(greenButtonId)) {
    switchTheStopwatchState();
  }
  if (isButtonPressed(redButtonId)) {
    resetStopwatch();
  }
  if (stopwatchRunning == true) {
    printMillisFromStart();
  }  
}
