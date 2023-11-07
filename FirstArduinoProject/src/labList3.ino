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
// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27,16,2);

// DebounceButton* greenDebounceButton;
// DebounceButton* redDebounceButton;

// unsigned long lastTimeTurnedOn = 0UL;
// unsigned long timeElapsed = 0UL;
// bool stopwatchRunning = false;

// int getSecondsFromBeginning() {
//   return (timeElapsed + millis() - lastTimeTurnedOn)/1000;
// }

// void printSecondsFromStart() {
//   lcd.setCursor(0, 1);
//   lcd.print(getSecondsFromBeginning());
// }

// void switchTheStopwatchState() {
//   if (stopwatchRunning == false) {
//     lastTimeTurnedOn = millis();
//     stopwatchRunning = true;
//   }
//   else {
//     timeElapsed += (millis() - lastTimeTurnedOn);
//     stopwatchRunning = false;
//   }
// }

// void resetStopwatch() {
//   lcd.setCursor(0, 1);
//   lcd.print("                ");
//   stopwatchRunning = false;
//   lastTimeTurnedOn = 0UL;
//   timeElapsed = 0UL;
// }

// void setup() {
//     Initializer initializer = Initializer();
//     initializer.initButtons();

//     greenDebounceButton = new DebounceButton(GREEN_BUTTON);
//     redDebounceButton = new DebounceButton(RED_BUTTON);

//     initializer.initLCD(&lcd);
//     lcd.print("Time elapsed:");
// }

// void loop() {
//   if (greenDebounceButton->isPressed()) {
//     switchTheStopwatchState();
//   }
//   if (redDebounceButton->isPressed()) {
//     resetStopwatch();
//   }
//   if (stopwatchRunning == true) {
//     printSecondsFromStart();
//   }  
// }
