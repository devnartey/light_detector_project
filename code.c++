#include <LiquidCrystal.h>

// Constants
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin = 12;    // LED pin at Arduino pin 12
const int buttonPin = 2;  // Push button pin at Arduino pin 2
const int buzzerPin = 3;  // Buzzer pin at Arduino pin 3

// Variables
int value; // Store value from photoresistor (0-1023)

// LCD configuration
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // RS, EN, D4, D5, D6, D7

void setup()
{
    Serial.begin(9600);

    pinMode(ledPin, OUTPUT);          // Set ledPin as an output
    pinMode(pResistor, INPUT);        // Set pResistor as an input
    pinMode(buttonPin, INPUT_PULLUP); // Set buttonPin as an input with internal pull-up resistor
    pinMode(buzzerPin, OUTPUT);       // Set buzzerPin as an output

    lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows

    // Beep the buzzer once
    beepBuzzer(1);

    // Display initial message
    lcd.setCursor(0, 0);
    lcd.print("Photo/Light detection device is on");
    delay(2000); // Display message for 2 seconds

    lcd.clear(); // Clear the LCD

    lcd.setCursor(0, 0);
    lcd.print("Detecting light...");
}

void loop()
{
    value = analogRead(pResistor);
    Serial.print("\n");
    Serial.print(value);

    if (value > 600)
    {
        digitalWrite(ledPin, LOW);                   // Turn LED off
        lcd.clear();                                 // Clear the LCD
        lcd.setCursor(0, 0);                         // Set cursor to the first row, first column
        lcd.print("Light Detected, Buzzer beeping"); // Display "Hair cut done" message
        beepBuzzer(2);                               // Beep the buzzer twice
        delay(2000);                                 // Wait for 2 seconds
        lcd.clear();                                 // Clear the LCD
        lcd.setCursor(0, 0);                         // Set cursor to the first row, first column
        lcd.print("About to start");                 // Display "About to start" message
    }
    else
    {
        digitalWrite(ledPin, HIGH);      // Turn LED on
        lcd.clear();                     // Clear the LCD
        lcd.setCursor(0, 0);             // Set cursor to the first row, first column
        lcd.print("Detecting light..."); // Display "Detecting hair..." message
    }

    // Check if the button is pressed
    if (digitalRead(buttonPin) == LOW)
    {
        // Perform certain actions when the button is pressed
        // For example, you can display a message on the LCD
        lcd.clear();                          // Clear the LCD
        lcd.setCursor(0, 0);                  // Set cursor to the first row, first column
        lcd.print("Light is being detected"); // Display "Hair cutting" message
        delay(1000);                          // Wait for 1 second
    }

    delay(1000); // Small delay
}

void beepBuzzer(int times)
{ // this is function for handling the buzzer beeping
    for (int i = 0; i < times; i++)
    {
        digitalWrite(buzzerPin, HIGH); // Turn buzzer on
        delay(100);                    // Delay for beep duration
        digitalWrite(buzzerPin, LOW);  // Turn buzzer off
        delay(100);                    // Delay between beeps
    }
}
