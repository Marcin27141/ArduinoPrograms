#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

LiquidCrystal_I2C lcd(0x27,16,2);

void initLCD()
{
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void initRGB()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, LOW);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

//taks 1
//switch led into R>G>B>R>... whenever red or green button is pressed
// int leds[] = {LED_RED, LED_GREEN, LED_BLUE};
// int led_index = 0;

// #define DEBOUNCE_PERIOD 10UL
// int buttons[] = {GREEN_BUTTON, RED_BUTTON};
// int debouncedStates[] = {HIGH, HIGH};
// int previousReadings[] = {HIGH, HIGH};
// unsigned long lastChanged[] = {0UL, 0UL};

// bool isButtonPressed(int buttonId) {
//     bool isPressed = false;
//     int current_reading = digitalRead(buttons[buttonId]);

//     if (previousReadings[buttonId] != current_reading)
//     {
//         lastChanged[buttonId] = millis();
//     }

//     if (millis() - lastChanged[buttonId] > DEBOUNCE_PERIOD)
//     {
//         if(current_reading != debouncedStates[buttonId])
//         {
//             if (debouncedStates[buttonId] == HIGH && current_reading == LOW)
//             {
//                 isPressed = true;
//             }
//             debouncedStates[buttonId] = current_reading;
//         }
//     }

//     previousReadings[buttonId] = current_reading;
//     return isPressed;
// }

// void switchLed() {
//   digitalWrite(leds[led_index], LOW);
//   led_index = ++led_index % 3;
//   digitalWrite(leds[led_index], HIGH);
// }

// void setup()
// {
//     initButtons();
//     initRGB();
//     digitalWrite(LED_RED, HIGH);
// }


// void loop()
// {
//     for (int i = 0; i < 2; i++)
//         if (isButtonPressed(i))
//             switchLed();
// }

//task 2
//"simultaneously" changing led lights
// int leds[] = {LED_RED, LED_GREEN, LED_BLUE};
// int ledsStates[] {LOW, LOW, LOW};
// unsigned long turnTimes[] = {900UL, 1000UL, 1100UL};
// unsigned long lastChanged[] = {0UL, 0UL, 0UL};

// void setup()
// {
//     initRGB();
//     initButtons();
// }

// void blinkLedIfTime(int i) {
//   if (millis() - lastChanged[i] >= turnTimes[i])
//   {
//     if (ledsStates[i] == HIGH) {
//       ledsStates[i] = LOW;
//     }
//     else {
//       ledsStates[i] = HIGH;
//     }
//     digitalWrite(leds[i], ledsStates[i]);
//     lastChanged[i] += turnTimes[i];
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
  initLCD();
  initButtons();

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
