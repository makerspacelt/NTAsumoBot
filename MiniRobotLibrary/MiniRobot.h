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
    void back();
    void stop();
    void leftForward();
    void leftBack();
    void leftStop();
    void rightForward();
    void rightBack();
    void rightStop();
    bool leftEdge();
    bool rightEdge();
    int distanceToEnemy();
};

#endif
