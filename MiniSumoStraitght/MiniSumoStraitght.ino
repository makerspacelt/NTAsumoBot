#include <MiniRobot.h>

MiniRobot robot;

byte status = 2;
/*
0 - don't need changes;
1 - counter only
2 - drive straight back;
3 - drive straight forward;
4 - spin around
 - enemy forward;
*/

int count = 0;

void setup() {
  PCMSK1 |= bit(0) | bit(1);
  PCIFR  |= bit(1);
  PCICR  |= bit(1);
  pinMode(A0,INPUT);   // set Pin as Input (default)
  digitalWrite(A0,HIGH);  // enable pullup resistor
  pinMode(A1,INPUT);   // set Pin as Input (default)
  digitalWrite(A1,HIGH);  // enable pullup resistor
}

ISR (PCINT1_vect)
{
  if (robot.leftEdge() || robot.rightEdge()) {
    status = 4;
  }
}

void loop() {
  switch (status) {
    case 1:
      count--;
      if (count <= 0) {
        status = 3;
      }
      break;
    case 2:
      robot.back();
      count = 15;
      status = 1;
      break;
    case 3:
      robot.forward();
      status = 0;
      break;
    case 4:
      robot.leftBack();
      robot.rightForward();
      count = 10;
      status = 1;
      break;
  }
}
