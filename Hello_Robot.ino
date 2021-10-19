// Include Libraries
#include "Arduino.h"
#include "Servo.h"

// Pin Definitions
#define SERVO_PIN       2
#define ECHO_PIN        6
#define TRIG_PIN        7

Servo servo;
long duration, cm;          // declaring variables
int limit = 10;             // this variable sets the limit of our sensor

void setup() 
{   
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
  
    Serial.begin(9600);
    while (!Serial);            // wait for serial port to connect
    Serial.println("Starting");
    servo.attach(SERVO_PIN);
}

void loop() 
{
    duration = get_pulse_duration();
    cm = ms_to_cm(duration);
    Serial.println("Distance is: " + cm);
    if (cm < limit) {wave(0, 40);}
}

long get_pulse_duration() { // Sends a pulse from the trigger, and calculates how long it takes to return
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    return pulseIn(ECHO_PIN, HIGH);
}

long ms_to_cm(long microseconds) {          // d = v * t
    double speed_sound = 0.0343;            // in centimetres per microseconds
    return microseconds * speed_sound / 2;  // divide by 2 to account for pulse travelling forward and backward
}

void wave(int angle1, int angle2) {                // Angle2 > Angle1
    for (int pos = angle1; pos < angle2; pos++) {  // Slowly rotate towards angle2
        servo.write(pos);
        delay(10);
    }
    delay(400);
    for (int pos = angle2; pos > angle1; pos--) {  // Slowly rotate towards angle1
        servo.write(pos);
        delay(10);
    }
    delay(400);
}
