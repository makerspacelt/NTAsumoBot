#include <MiniRobot.h>

MiniRobot robot;

byte drive_state;
byte next_drive_state;
/*
0 - don't need changes
2 - drive straight back;
1 - drive straight forward;
3 - turn right
4 - turn left
 - enemy forward;
*/
#define DRIVE_KEEP 0
#define DRIVE_FORWARD 1
#define DRIVE_BACK 2
#define DRIVE_RIGHT 3
#define DRIVE_LEFT 4

struct DriveEvent {
  byte state;
  long time;
};

DriveEvent queue[8];
int queue_size;

boolean executing_queue;
DriveEvent current;
long current_started;

void push_event(byte state, long time) {
  queue[queue_size] = {state, time};
  queue_size++;
}

long left_edge_time = 0;
long right_edge_time = 0;

void setup() {
  PCMSK1 |= bit(0) | bit(1);
  PCIFR  |= bit(1);
  PCICR  |= bit(1);
  
  pinMode(A0,INPUT);   // set Pin as Input (default)
  digitalWrite(A0,HIGH);  // enable pullup resistor
  pinMode(A1,INPUT);   // set Pin as Input (default)
  digitalWrite(A1,HIGH);  // enable pullup resistor

  // Setup state
  drive_state = 0;
  next_drive_state = -1;
  
  queue_size = 0;
  push_event( DRIVE_BACK, 500);
  
  executing_queue = false;

  left_edge_time = 0;
  right_edge_time = 0;
  
  Serial.begin(9600);
}

ISR (PCINT1_vect)
{
  boolean left = robot.leftEdge();
  boolean right = robot.rightEdge();

//  Serial.print("Left: ");
//  Serial.print(left);
//  Serial.print(" Right: ");
//  Serial.print(right);
//  Serial.print("\nRight: ");
//  Serial.print(right_edge_time);
//  Serial.print(" Left: ");
//  Serial.print(left_edge_time);
//  Serial.print("\n");
  
  if (left) {
    if(left_edge_time == 0)
      left_edge_time = millis();
  } else {
    if(left_edge_time > 0)
      left_edge_time = 0;
  }
  
  if (right) {
    if(right_edge_time == 0)
      right_edge_time = millis();
  } else {
    if(right_edge_time > 0)
      right_edge_time = 0;
  }

  if( queue_size == 0 && (left || right)  && drive_state != DRIVE_RIGHT && drive_state != DRIVE_LEFT) {
    if(left_edge_time > 0) {
      if(right_edge_time > 0) {
        if(left_edge_time < right_edge_time) {
          push_event(DRIVE_RIGHT, 500);
        } else {
          push_event(DRIVE_LEFT, 500);
        }
      } else {
          push_event(DRIVE_RIGHT, 500);
      }
    } else {
      push_event(DRIVE_LEFT, 500);
    }
  }
}

void freetime() {
  int dist = robot.distanceToEnemy();
  if( dist > 5 && dist < 40 && executing_queue) {
    Serial.println("Enemy seen!");
    executing_queue = false;
    next_drive_state = DRIVE_FORWARD;
  }
}

void drive(int state) {
  switch (state) {
    case DRIVE_FORWARD:
      robot.forward();
      Serial.print("Forward at ");
      Serial.println(millis());
      break;
    case DRIVE_BACK:
      robot.back();
      Serial.print("Backward at ");
      Serial.println(millis());
      break;
    case DRIVE_RIGHT:
      robot.leftForward();
      robot.rightBack();
      Serial.print("Right at ");
      Serial.println(millis());
      break;
    case DRIVE_LEFT:
      robot.leftBack();
      robot.rightForward();
      Serial.print("Left at ");
      Serial.println(millis());
      break;
  }
  
  drive_state = state; 
}
void loop() {
  if(next_drive_state != -1) {
    drive(next_drive_state);
    next_drive_state = -1;
  }
  
  if(executing_queue) {
    if(current.time + current_started <= millis()) {
      executing_queue = false;
      next_drive_state = DRIVE_FORWARD;
    }
  }
  
  if(!executing_queue && queue_size > 0) {
    executing_queue = true;
    
    current = queue[0];

    next_drive_state = current.state;
    current_started = millis();
    
    memmove(queue, queue + 1, sizeof(DriveEvent) * 8 - queue_size);
    queue_size--;
  } else {
    freetime();
  }
}

