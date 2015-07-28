#include <MiniRobot.h>

MiniRobot robot;
int steps;

void setup() {
}

void loop() {
  if ((robot.leftEdge() || robot.rightEdge()) && steps > 0) {
    steps--;
    robot.leftBack();
    robot.rightBack();
  } else if (robot.distanceToEnemy() > 0) {
    steps = 100;
    robot.leftForward();
    robot.rightForward();
  } else {
    steps = 100;
    robot.leftBack();
    robot.rightForward();
  } 
}
