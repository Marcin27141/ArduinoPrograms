#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define ENCODER1 A2
#define ENCODER2 A3

#define SW A1
#define DT A2
#define CLK A3

void initEncoder()
{
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
}

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

void testLCD()
{
  lcd.print("LCD Test");
  lcd.setCursor(1, 1);
  lcd.print("Wait & watch");
  delay(1000);
  for (int i = 0; i < 3; i++)
  {
    lcd.noBacklight();
    delay(200);
    lcd.backlight();
    delay(200);
  }
  delay(1000);
  lcd.clear();
}

void testRGB()
{
  lcd.print("RGB LED Test");
  lcd.setCursor(0, 1);
  lcd.print("Check R>G>B>R>..");

  delay(1000);
  const int time = 500;

  for (int i = 0; i < 2; i++)
  {
    digitalWrite(LED_RED, HIGH);
    delay(time);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    delay(time);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
    delay(time);
    digitalWrite(LED_BLUE, LOW);
  }
  lcd.clear();
}

void testButtons1()
{
  lcd.print("Buttons: Press");
  lcd.setCursor(0, 1);
  lcd.print("Red & Green Btns");
  delay(1000);
  int b1 = HIGH;
  int b2 = HIGH;
  while ((b1 == HIGH) || (b2 == HIGH))
  {
    b1 = digitalRead(RED_BUTTON);
    if (b1 == LOW)
      digitalWrite(LED_RED, HIGH);
    else
      digitalWrite(LED_RED, LOW);

    b2 = digitalRead(GREEN_BUTTON);
    if (b2 == LOW)
      digitalWrite(LED_GREEN, HIGH);
    else
      digitalWrite(LED_GREEN, LOW);
  }
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  while ((b1 == LOW) || (b2 == LOW))
  {
    b1 = digitalRead(RED_BUTTON);
    b2 = digitalRead(GREEN_BUTTON);
  }
  digitalWrite(LED_BLUE, LOW);
  lcd.clear();
}

void testButtons2()
{
  lcd.print("Buttons: Press");
  lcd.setCursor(0, 1);
  lcd.print("Red & Green Btns");
  bool redPressed = false;
  bool greenPressed = false;

  while (!redPressed || !greenPressed)
  {
    if (digitalRead(RED_BUTTON) == LOW)
    {
      redPressed = true;
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
    }
    if (digitalRead(GREEN_BUTTON) == LOW)
    {
      greenPressed = true;
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED, LOW);
    }
  }

  delay(1000);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  lcd.clear();
}

void testEncoder()
{
  lcd.print("Encoder: ");
  lcd.setCursor(0, 1);
  lcd.print("Turn encoder");
  delay(1000);
  int state1 = digitalRead(ENCODER1);
  int state2 = digitalRead(ENCODER2);
  int counter1 = 0, counter2 = 0;
  int e1, e2;
  bool ledRedState = LOW;
  bool ledGreenState = LOW;
  while (counter1 < 4 || counter2 < 4)
  {
    e1 = digitalRead(ENCODER1);
    e2 = digitalRead(ENCODER2);

    if (state1 != e1 && e1 == HIGH) {
      if (e1 != e2) {
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
      }
      else {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
      }
    }
    
    if (state1 != e1 & e1 == HIGH)
    {
      if (e1 != e2)
      {
        counter1++;
        Serial.print("counter 1 increased: ");
      }
      else {
        counter2++;
        Serial.print("counter 2 increased: ");
      }
    }
    state1 = e1;

  }
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
  digitalWrite(LED_BLUE, LOW);

  lcd.clear();
}

/*int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;*/

void setup() {
  initLCD();
  initRGB();
  initButtons();
  initEncoder();
  Serial.begin(9600);

  /*pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
  lastStateCLK = digitalRead(CLK);*/

  testEncoder();
}

void loop() {
  /*currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
			currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";
		}

		Serial.print("Direction: ");
		Serial.print(currentDir);
		Serial.print(" | Counter: ");
		Serial.println(counter);
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial.println("Button pressed!");
		}

		// Remember last button press event
		lastButtonPress = millis();
	}

	// Put in a slight delay to help debounce the reading
	delay(1);*/
}