// Rafael Ramírez Salas
// Ingeniería de Computadores, Universidad de Málaga
// Trabajo de Fin de Grado 2024: Fail Tolerant DualNano

#include <Arduino.h>
#include <LiquidCrystal.h>

// Initialize the LCD library by associating any LCD pin with the Arduino pin number it's connected to.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Digital inputs.
#define _INPUT_VALVE 0x00  // Inlet valve
#define _OUTPUT_VALVE 0x01 // Outlet valve
#define _HEATER 0x02       // Heater
#define _COOLER 0x03       // Cooler
#define _AGITATOR 0x04     // Stirrer
// Digital outputs.
#define _HIGH_FLOATER 0x10 // High floater
#define _LOW_FLOATER 0x11  // Low floater
#define _MIN_TEMP 0x12     // Low temperature
#define _MAX_TEMP 0x13     // High temperature
// Analog inputs.
#define _TEMP_IN_MIN 0x20  // Minimal temperature alarm trigger level
#define _TEMP_IN_MAX 0x21  // Maximal temperature alarm trigger level
// Analog outputs.
#define _VOLUME 0x30       // Volume
#define _TEMP 0x31         // Temperature

// Actions.
#define _TURN_ON 0x01
#define _TURN_OFF 0x00
unsigned int initialValue;

void setup(void){
    // Initialize serial communication.
    Serial.begin(19200);

    // Initialize LCD.
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Connect srtank");
    lcd.setCursor(0, 1);
    lcd.print("and press PD6");

    // Set up a pin for button press.
    pinMode(6, INPUT);
    
    // Wait for the user to press the button connected to PD6.
    while(digitalRead(6) == 0){
        delay(1);
    }
    
    // Synchronize communication with the simulator.
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);

    // Send initialization data for the maximum temperature analog input.
    Serial.write(_TEMP_IN_MAX);
    initialValue = 28;
    Serial.write((initialValue & 0xFF00) >> 8);
    Serial.write(initialValue & 0x00FF);
}

unsigned char valueH, valueL;
char buffer[6];

// Function to measure & display volume & temperature.
void volume(void){
    // Request the simulator to measure volume.
    Serial.write(_VOLUME);
    while(!Serial.available());
    valueH = Serial.read();
    while(!Serial.available());
    valueL = Serial.read();
    initialValue = (valueH << 8) | valueL;

    // Display volume & temperature on LCD.
    lcd.setCursor(0, 1);
    lcd.print("v=");
    lcd.print(initialValue);
    lcd.print("l  t=");
    
    // Request the simulator to measure temperature.
    Serial.write(_TEMP);
    while(!Serial.available());
    valueH = Serial.read();
    while(!Serial.available());
    valueL = Serial.read();
    initialValue = (valueH << 8) | valueL;
    lcd.print(initialValue);
    lcd.print("C ");
}

unsigned char value;

void loop(void){
    // Perform a series of simulated tank control actions.

    // Turn on the input valve.
    Serial.write(_INPUT_VALVE);
    Serial.write(_TURN_ON);

    // Turn off the output valve.
    Serial.write(_OUTPUT_VALVE);
    Serial.write(_TURN_OFF);

    // Display "Filling" message on LCD.
    lcd.setCursor(0, 0);
    lcd.print("Filling ");
    // delay(1000);

    do {
        // Request the simulator to open the fill valve.
        Serial.write(_HIGH_FLOATER);
        while(!Serial.available());
        value = Serial.read();
        volume(); // Measure & display volume & temperature.
    } while(value == 0);

    // Turn off the input valve.
    Serial.write(_INPUT_VALVE);
    Serial.write(_TURN_OFF);

    // Turn on the heater.
    Serial.write(_HEATER);
    Serial.write(_TURN_ON);

    // Display "Heating" message on LCD.
    lcd.setCursor(0, 0);
    lcd.print("Heating ");
    // delay(1000);

    do {
        // Request the simulator to set the maximum temperature.
        Serial.write(_MAX_TEMP);
        while(!Serial.available());
        value = Serial.read();
        volume(); // Measure & display volume & temperature.
    } while(value == 0);

    // Turn off the heater.
    Serial.write(_HEATER);
    Serial.write(_TURN_OFF);

    // Turn on the output valve.
    Serial.write(_OUTPUT_VALVE);
    Serial.write(_TURN_ON);

    // Display "Emptying" message on LCD.
    lcd.setCursor(0, 0);
    lcd.print("Emptying");
    // delay(1000);

    do {
        // Request the simulator to open the bottom empty valve.
        Serial.write(_LOW_FLOATER);
        while(!Serial.available()); 
        value = Serial.read();
        volume(); // Measure & display volume & temperature.
    } while(value == 1);
}
