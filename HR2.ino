
// Include Libraries
#include "Arduino.h"
#include "Servo.h"


// Pin Definitions
#define S_PIN       2



// Global variables and defines
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

// object initialization
Servo servo;



// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{ 
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    servo.attach(S_PIN);
}


// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    long duration, inches, cm;
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
    // Serial.println(duration);
    Serial.println(cm);
    if (cm < 15) {
        for (int pos = 0; pos < 40; pos++) {
          servo.write(pos);
          delay(10);
        }
        delay(400);
        for (int pos = 40; pos > 0; pos--) {
          servo.write(pos);
          delay(10);
        }
        delay(400);
    }
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds * 343 * 0.1 * 0.001 / 2;
}
