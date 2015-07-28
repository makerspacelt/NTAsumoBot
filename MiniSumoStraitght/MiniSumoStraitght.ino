#include <MiniRobot.h>

MiniRobot robot;

void setup() {
}

void loop() {
  if (robot.leftEdge() && robot.distanceToEnemy() == 0) {
    robot.leftBack();
  } else {
    robot.leftForward();
  }
  if (robot.rightEdge() && robot.distanceToEnemy() == 0) {
    robot.rightBack();
  } else {
    robot.rightForward();
  }
}
