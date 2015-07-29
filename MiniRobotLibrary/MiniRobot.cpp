#include "MiniRobot.h"
#include "Arduino.h"

// IR sensors
const byte LEFT_EDGE = A0;      // Arduino 19 pin; Atmega PC0 (ADC0/PCINT8)
const byte RIGHT_EDGE = A1;     // Arduino 20 pin; Atmega PC1 (ADC1/PCINT9)

// Motors
const byte LEFT_FORWARD = 5;    // Arduino 8 pin; Atmega PD5 (PCINT21/OC0B/T1)
const byte LEFT_BACK = 6;       // Arduino 9 pin; Atmega PD6 (PCINT22/OC0A/AIN0)
const byte RIGHT_FORWARD = 9;   // Arduino 12 pin; Atmega PB1 (PCINT1/OC1A)
const byte RIGHT_BACK = 10;     // Arduino 13 pin; Atmega PB2 (PCINT2/SS/OC1B)

// Ultrasonic sensor
const byte RANGE_ECHO = 7;      // Arduino 10 pin; Atmega PD7 (PCINT23/AIN1)
const byte RANGE_TRIG = 8;      // Arduino 11 pin; Atmega PB0 (PCINT0/CLKO/ICP1)

MiniRobot::MiniRobot(){
    // Input pins for IR sensors
    pinMode(LEFT_EDGE, INPUT);
    pinMode(RIGHT_EDGE, INPUT);

    // Output pins for motors control
    pinMode(LEFT_FORWARD, OUTPUT);
    pinMode(LEFT_BACK, OUTPUT);
    pinMode(RIGHT_FORWARD, OUTPUT);
    pinMode(RIGHT_BACK, OUTPUT);

    // Input and output pins for ultrasonis sensor
    pinMode(RANGE_TRIG, OUTPUT);
    pinMode(RANGE_TRIG, OUTPUT);
}

void MiniRobot::forward(){
    leftForward();
    rightForward();
}

void MiniRobot::back(){
    leftBack();
    rightBack();
}

void MiniRobot::stop(){
    leftStop();
    rightStop();
}

void MiniRobot::leftForward(){
    digitalWrite(LEFT_BACK, LOW);
    digitalWrite(LEFT_FORWARD, HIGH);
}

void MiniRobot::leftBack(){
    digitalWrite(LEFT_FORWARD, LOW);
    digitalWrite(LEFT_BACK, HIGH);
}

void MiniRobot::leftStop(){
    digitalWrite(LEFT_FORWARD, LOW);
    digitalWrite(LEFT_BACK, LOW);
}

void MiniRobot::rightForward(){
    digitalWrite(RIGHT_BACK, LOW);
    digitalWrite(RIGHT_FORWARD, HIGH);
}

void MiniRobot::rightBack(){
    digitalWrite(RIGHT_FORWARD, LOW);
    digitalWrite(RIGHT_BACK, HIGH);
}

void MiniRobot::rightStop(){
    digitalWrite(RIGHT_FORWARD, LOW);
    digitalWrite(RIGHT_BACK, LOW);
}

bool MiniRobot::leftEdge(){
    return !digitalRead(LEFT_EDGE);
}

bool MiniRobot::rightEdge(){
    return !digitalRead(RIGHT_EDGE);
}

int MiniRobot::distanceToEnemy(){
    long duration, distance;
    digitalWrite(RANGE_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(RANGE_TRIG, LOW);
    duration = pulseIn(RANGE_ECHO, HIGH);
    distance = (duration/2) / 29.1;
    if (distance > 60 || distance < 0) {
        distance = 0;
    }

    return distance;
}
