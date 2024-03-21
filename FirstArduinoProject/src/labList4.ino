#include <Initializer.h>
#include <DebounceButton.h>


//task 1
//notify button states using Serial
DebounceButton greenDebounceButton(GREEN_BUTTON);
DebounceButton redDebounceButton(RED_BUTTON);

void setup() {
    Serial.begin(9600);
    while (!Serial) {
    }
}

void notifyButtonPressed(String button) {
    Serial.print(button);
    Serial.println(" button was pressed");
}


void loop() {
    if (greenDebounceButton.isPressed())
        notifyButtonPressed("Green");
    if (redDebounceButton.isPressed())
        notifyButtonPressed("Red");
}

//task 2
//light RGB led colors based on Serial input
bool isValidNumber(String input) {
  int result = input.toInt();
  return input == "0" || (result > 0 && result <= 255);
}

bool validatePassedValues(String stringParams[], int length) {
    String notValidMessage = " is not a valid number. Put a number from 0 to 255";

    for (int i = 0; i < length; i++) {
        if (!isValidNumber(stringParams[i])) {
            Serial.println(stringParams[i] + notValidMessage);
            return false;
        }
    }

    return true;
}

void printSuccessfulCommand(String params[], int length) {
    for (int i = 0; i < length; i++) {
        Serial.print(params[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void lightLeds(String paramStrings[]) {
    int r_intensity = paramStrings[0].toInt();
    int g_intensity = paramStrings[1].toInt();
    int b_intensity = paramStrings[2].toInt();

    analogWrite(LED_RED, r_intensity);
    analogWrite(LED_GREEN, g_intensity);
    analogWrite(LED_BLUE, b_intensity);
}

//message format: red_percent, green_percent, blue_percent
const int VALID_NUMBER_OF_PARAMETERS = 3;

void processSerialCommand() {
    String command = Serial.readStringUntil('\n');
    command.trim();
    int space1 = command.indexOf(' ');
    int space2 = command.indexOf(' ', space1 + 1);
    int space3 = command.indexOf(' ', space2 + 1);

    if (space1 == -1 || space2 == -1 || space3 != -1) {
        Serial.println("Incorrect line format. Separate 3 intensity values with single spaces");
    }
    else {
        String paramStrings[] = {
            command.substring(0, space1),
            command.substring(space1 + 1, space2),
            command.substring(space2 + 1)
        };

        bool valuesAreValid = validatePassedValues(paramStrings, VALID_NUMBER_OF_PARAMETERS);
        if (valuesAreValid) {
            lightLeds(paramStrings);
            printSuccessfulCommand(paramStrings, VALID_NUMBER_OF_PARAMETERS);
        }
    }
}

void setup()
{
    Initializer initializer = Initializer();
    initializer.initRGB();

    Serial.begin(9600);
    while (!Serial)
    {
    }
}

void loop()
{
    if (Serial.available() > 0)
    {
        processSerialCommand();
    }
}

//task 3
//showing on lcd potentiometer real and read value
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);


void printSensorValue(int sensor) {
  lcd.setCursor(12, 0);
  char paddedSensorValue[5];
  sprintf(paddedSensorValue, "%4d", sensor);
  lcd.print(paddedSensorValue);
}

void printRealVoltage(float voltage) {
    lcd.setCursor(12, 1);
    char paddedRealValue[10];
    dtostrf(voltage, 3, 2, paddedRealValue);
    lcd.print(paddedRealValue);
}

float getRealSensorValue(int readValue) {
    static const float REF_VOLTAGE = 5.0;
    static const int RESOLUTION = 1024;

    return REF_VOLTAGE / RESOLUTION * readValue;
}

void setup()
{
  Initializer initializer = Initializer();
  initializer.initLCD(&lcd);

  lcd.setCursor(0, 0);
  lcd.print("Sensor:");
  lcd.setCursor(0, 1);
  lcd.print("Real:");

  Serial.begin(9600);
}

int sensorValue = 0; 
float sensorRealValue = 0;

void loop()
{
    sensorValue = analogRead(POTENTIOMETER);
    sensorRealValue = getRealSensorValue(sensorValue);
    printSensorValue(sensorValue);
    printRealVoltage(sensorRealValue);
}

//task 4
//oberving sensor readings on serial monitor and serial plotter
void setup()
{
  Serial.begin(9600);
  while(!Serial) {}

}

int sensorValue = 0; 

void loop()
{
    sensorValue = analogRead(POTENTIOMETER);
    Serial.println(sensorValue);
}