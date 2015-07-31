#include <MiniRobot.h>

MiniRobot robot;

byte status;
unsigned long start_millis;
long delay_millis, enemy_millis = 5;
long dist, dist_before, dist_good = 0;
int good_count = 3;

void setup() {
  pinMode(A0,INPUT);   // set Pin as Input (default)
  pinMode(A1,INPUT);   // set Pin as Input (default)
  PCMSK1 |= bit(0) + bit(1);
  PCIFR  |= bit(1);
  PCICR  |= bit(1);
  status = 2;
  delay(5000);
  start_millis = millis();
}

//interupt for IR sensor changes
ISR (PCINT1_vect)
{
  if (robot.leftEdge() || robot.rightEdge()) {
    status = 4;
  }
}

void loop() {
  switch (status) {
    case 1:
      if ((millis() - start_millis) >= delay_millis) {
        status = 3;
      }
      break;
    case 2:
      robot.backward();
      delay_millis = 600;
      start_millis = millis();
      status = 1;
      break;
    case 3:
      robot.forward();
      status = 0;
      break;
    case 4:
      robot.rightBackward();
      robot.leftStop();
      delay_millis = 80;
      start_millis = millis();
      status = 5;
      break;
    case 5:
      if (start_millis + enemy_millis <= millis()){
        dist = robot.distanceToEnemy();
        start_millis = millis();
        if(dist + 2 >= dist_good && dist - 2 <= dist_good){
          good_count--;
        } else {
          good_count = 3;
          dist_good = dist;
        }
        if(dist != 0 && dist_good == 0){
          dist_good = dist;
        }
      }
      if (((millis() - start_millis) >= delay_millis) || (good_count <= 0 && dist_good > 0 && dist_good < 40)) {
        status = 3;
        good_count = 3;
      }
      break;
  }
}
