#include <MiniRobot.h>

MiniRobot robot;

byte status;
/*
0 - don't need changes;
1 - counter only
2 - drive straight back;
3 - drive straight forward;
4 - spin around
 - enemy forward;
*/

unsigned long start_millis;
long delay_millis;
long dist;

void setup() {
  pinMode(A0,INPUT);   // set Pin as Input (default)
  pinMode(A1,INPUT);   // set Pin as Input (default)
  PCMSK1 |= bit(0) + bit(1);
  PCIFR  |= bit(1);
  PCICR  |= bit(1);
  status = 2;
}

ISR (PCINT1_vect)
{
  if (robot.leftEdge() || robot.rightEdge()) {
    status = 4;
  }
}

void loop() {
  Serial.println(status);
  switch (status) {
    case 1:      
      if ((millis() - start_millis) >= delay_millis) {
        status = 3;
      }
      break;
    case 2:
      robot.back();
      delay_millis = 600;
      start_millis = millis();
      status = 1;
      break;
    case 3:
      robot.forward();
      status = 0;
      break;
    case 4:
      robot.rightBack();
      robot.leftForward();
      delay_millis = 400;
      start_millis = millis();
      status = 5;
      break;
    case 5:
      dist = robot.distanceToEnemy();
      if (((millis() - start_millis) >= delay_millis) || (dist > 5)) {
        status = 3;
      }
      break;
  }
}
