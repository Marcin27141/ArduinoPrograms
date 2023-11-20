// #include <Arduino.h>
// #include <LedRGB.h>

// #define LED_RED 6
// #define LED_GREEN 5
// #define LED_BLUE 3

// LedRGB ledRgb(LED_RED, LED_GREEN, LED_BLUE);

// bool isValidNumber(String input) {
//   int result = input.toInt();
//   return input == "0" || (result > 0 && result <= 255);
// }

// bool validatePassedValues(String stringParams[], int length) {
//     String notValidMessage = " is not a valid number. Put a number from 0 to 255";

//     for (int i = 0; i < length; i++) {
//         if (!isValidNumber(stringParams[i])) {
//             Serial.println(stringParams[i] + notValidMessage);
//             return false;
//         }
//     }

//     return true;
// }

// void printSuccessfulCommand(String params[], int length) {
//     for (int i = 0; i < length; i++) {
//         Serial.print(params[i]);
//         Serial.print(" ");
//     }
//     Serial.println();
// }

// void lightLeds(String paramStrings[]) {
//     int r_intensity = paramStrings[0].toInt();
//     int g_intensity = paramStrings[1].toInt();
//     int b_intensity = paramStrings[2].toInt();

//     analogWrite(LED_RED, r_intensity);
//     analogWrite(LED_GREEN, g_intensity);
//     analogWrite(LED_BLUE, b_intensity);
// }


// const int VALID_NUMBER_OF_RGB_PARAMETERS = 3;

// void processRgbCommand(String command) {
//     int space1 = command.indexOf(' ');
//     int space2 = command.indexOf(' ', space1 + 1);
//     int space3 = command.indexOf(' ', space2 + 1);

//     if (space1 == -1 || space2 == -1 || space3 != -1) {
//         Serial.println("Incorrect line format. Separate 3 intensity values with single spaces");
//     }
//     else {
//         String paramStrings[] = {
//             command.substring(0, space1),
//             command.substring(space1 + 1, space2),
//             command.substring(space2 + 1)
//         };

//         bool valuesAreValid = validatePassedValues(paramStrings, VALID_NUMBER_OF_RGB_PARAMETERS);
//         if (valuesAreValid) {
//             ledRgb.lightRgb(paramStrings[0].toInt(), paramStrings[1].toInt(), paramStrings[2].toInt());
//             printSuccessfulCommand(paramStrings, VALID_NUMBER_OF_RGB_PARAMETERS);
//         }
//     }
// }

// void processColorCommand(String command) {
//     int color;
//     bool wasFound = true;
//     if (command.equals("red"))
//         color = RED;
//     else if (command.equals("green"))
//         color = GREEN;
//     else if (command.equals("blue"))
//         color = BLUE;
//     else if (command.equals("yellow"))
//         color = YELLOW;
//     else if (command.equals("cyan"))
//         color = CYAN;
//     else if (command.equals("magenta"))
//         color = MAGENTA;
//     else if (command.equals("black"))
//         color = BLACK;
//     else if (command.equals("white"))
//         color = WHITE;
//     else {
//         wasFound = false;
//         Serial.println("Color was not found");
//     }
        

//     if (wasFound)
//         ledRgb.lightPredefinedColor(color);
// }

// //message format: 'rgb:red green blue'
// //or: 'color:colorName'
// void processSerialCommand() {
//     String command = Serial.readStringUntil('\n');
//     command.trim();

//     if (command.startsWith("color:"))
//         processColorCommand(command.substring(6));
//     else if (command.startsWith("rgb:"))
//         processRgbCommand(command.substring(4));
//     else
//         Serial.println("Unrecognized command. Start with 'color:' or 'rgb:'");
// }

// void setup()
// {
//     Serial.begin(9600);
//     while (!Serial)
//     {
//     }
//     ledRgb.turnOn();
// }

// void loop()
// {
//     if (Serial.available() > 0)
//     {
//         processSerialCommand();
//     }
// }