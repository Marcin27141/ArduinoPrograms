// #include <Arduino.h>
// #include <LiquidCrystal_I2C.h>
// #include <util/atomic.h>

// LiquidCrystal_I2C lcd(0x27,16,2);

// #define LED_RED 6
// #define LED_GREEN 5
// #define LED_BLUE 3

// #define RED_BUTTON 2
// #define GREEN_BUTTON 4

// #define ENCODER1 A2
// #define ENCODER2 A3

// void initLCD()
// {
//   lcd.init();
//   lcd.clear();
//   lcd.backlight();
// }

// void initRGB()
// {

//   pinMode(LED_RED, OUTPUT);
//   pinMode(LED_GREEN, OUTPUT);
//   pinMode(LED_BLUE, OUTPUT);
// }

// void initButtons()
// {
//   pinMode(RED_BUTTON, INPUT_PULLUP);
//   pinMode(GREEN_BUTTON, INPUT_PULLUP);
// }

// void initEncoder()
// {
//   pinMode(ENCODER1, INPUT_PULLUP);
//   pinMode(ENCODER2, INPUT_PULLUP);
// }

// #define BUTTON_DEBOUNCE_PERIOD 100

// String menuOptions[] = {
//   "LED Red",
//   "LED Green",
//   "LED Blue",
//   "LED White",
//   "LED None"
// };
// int numberOfMenuOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

// int menuTopItem = 0;

// void printMenu() {
//     char fstBuffer[17];
//     sprintf(fstBuffer, ">>%-14s", menuOptions[menuTopItem].c_str());
//     lcd.setCursor(0, 0);
//     lcd.print(fstBuffer);

//     int nextItem = (menuTopItem + 1) % numberOfMenuOptions;

//     char sndBuffer[17];
//     sprintf(sndBuffer, "%-16s", menuOptions[nextItem].c_str());
//     lcd.setCursor(0, 1);
//     lcd.print(sndBuffer);
// }

// void printResults(int val)
// {
//     char buffer[40];
//     sprintf(buffer, "Encoder: %3d", val);
//     lcd.setCursor(2, 0);
//     lcd.print(buffer);
// }

// void setup()
// {
//   initButtons();
//     initRGB();
//     initEncoder();
//     initLCD();

//     printMenu();

//     PCICR |= (1 << PCIE1);
//     PCMSK1 |= (1 << PCINT10);
// }

// volatile int encoder1 = HIGH;
// volatile int encoder2 = HIGH;
// volatile unsigned long encoderTimestamp = 0UL;

// ISR(PCINT1_vect)
// {
//     encoder1 = digitalRead(ENCODER1);
//     encoder2 = digitalRead(ENCODER2);
//     encoderTimestamp = millis();
// }

// int encoderValue = 0;
// int lastEn1 = LOW;
// unsigned long lastChangeTimestamp = 0UL;

// void checkMenuScroll() {
//     int en1;
//     int en2;
//     unsigned long timestamp;

//     ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
//     {
//         en1 = encoder1;
//         en2 = encoder2;
//         timestamp = encoderTimestamp;
//     }

//     if (en1 == LOW && timestamp > lastChangeTimestamp + BUTTON_DEBOUNCE_PERIOD)
//     {
//         if (en2 == HIGH)
//         {
//             menuTopItem = (menuTopItem + 1) % numberOfMenuOptions;
//         }
//         else
//         {
//             menuTopItem = (menuTopItem - 1 < 0) ? numberOfMenuOptions - 1 : menuTopItem - 1;
//         }
//         printMenu();
//         lastChangeTimestamp = timestamp;
//     }
//     lastEn1 = en1;
// }

// #define ENCODER_DEBOUNCE_PERIOD 10UL
// int buttons[] = {GREEN_BUTTON, RED_BUTTON};
// int debouncedStates[] = {HIGH, HIGH};
// int previousReadings[] = {HIGH, HIGH};
// unsigned long lastChanged[] = {0UL, 0UL};

// bool isButtonPressed() {
//     int greenButtonId = 0;

//     bool isPressed = false;
//     int current_reading = digitalRead(buttons[greenButtonId]);

//     if (previousReadings[greenButtonId] != current_reading)
//     {
//         lastChanged[greenButtonId] = millis();
//     }

//     if (millis() - lastChanged[greenButtonId] > ENCODER_DEBOUNCE_PERIOD)
//     {
//         if(current_reading != debouncedStates[greenButtonId])
//         {
//             if (debouncedStates[greenButtonId] == HIGH && current_reading == LOW)
//             {
//                 isPressed = true;
//             }
//             debouncedStates[greenButtonId] = current_reading;
//         }
//     }

//     previousReadings[greenButtonId] = current_reading;
//     return isPressed;
// }

// void performMenuOption() {
//   switch (menuTopItem) {
//     case 0:
//       digitalWrite(LED_RED, HIGH);
//       digitalWrite(LED_GREEN, LOW);
//       digitalWrite(LED_BLUE, LOW);
//       break;
//     case 1:
//       digitalWrite(LED_RED, LOW);
//       digitalWrite(LED_GREEN, HIGH);
//       digitalWrite(LED_BLUE, LOW);
//       break;
//     case 2:
//       digitalWrite(LED_RED, LOW);
//       digitalWrite(LED_GREEN, LOW);
//       digitalWrite(LED_BLUE, HIGH);
//       break;
//     case 3:
//       digitalWrite(LED_RED, HIGH);
//       digitalWrite(LED_GREEN, HIGH);
//       digitalWrite(LED_BLUE, HIGH);
//       break;
//     case 4:
//       digitalWrite(LED_RED, LOW);
//       digitalWrite(LED_GREEN, LOW);
//       digitalWrite(LED_BLUE, LOW);
//       break;
//     default:
//       break;
//   }
// }

// void loop()
// {
//   checkMenuScroll();
//   if (isButtonPressed())
//     performMenuOption();
// }