#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

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

//task 1
//notify button states using Serial
#define DEBOUNCE_PERIOD 10UL
int buttons[] = {GREEN_BUTTON, RED_BUTTON};
int debouncedStates[] = {HIGH, HIGH};
int previousReadings[] = {HIGH, HIGH};
unsigned long lastChanged[] = {0UL, 0UL};

bool notifyButtonsStateChanges(int buttonId) {
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
            String buttonColor = buttonId == 0 ? "Green" : "Red";
            if (debouncedStates[buttonId] == HIGH && current_reading == LOW)
            {
                isPressed = true;
                Serial.println(buttonColor + " button pushed");
            }
            else {
              Serial.println(buttonColor + " button released");
            }
            debouncedStates[buttonId] = current_reading;
        }
    }

    previousReadings[buttonId] = current_reading;
    return isPressed;
}

void setup() {
  initButtons();

  Serial.begin(9600);
  while (!Serial) {
  }
}


void loop() {
  for (int i = 0; i < 2; i++)
    notifyButtonsStateChanges(i);
}
