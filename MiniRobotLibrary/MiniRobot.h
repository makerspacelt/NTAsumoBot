#ifndef MiniRobot_h
#define MiniRobot_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class MiniRobot {
public:
    MiniRobot();
    void forward();
    void backward();
    void stop();
    void leftForward();
    void leftBackward();
    void leftStop();
    void rightForward();
    void rightBackward();
    void rightStop();
    bool leftEdge();
    bool rightEdge();
    int distanceToEnemy();
};

#endif
