// Author(s):       Benjamin Feuerborn, Tyler Dye, Nick Brown, Abdullah Al Shumais
// Due Date:        5/7/25
// Assignment:      Final Project
//----------------------------------------------------------------------
// File Author:       Nick Brown
//----------------------------------------------------------------------

#include <Arduino.h>
#include "timer.h"
#include "pwm.h"
#include "motor.h"
#include "spi.h"
#include "ultr_sonic.h"

// constant definitions
#define LOOP_DELAY 100         // delay between loops
#define ACCELERATION_RATE 10    // per loop
#define STOP_PROXIMITY 16      // distance object be within to cause car to stop 
#define TURN_THRESHOLD 8       // distance car must at least be away from object in order to turn

// funciton definitions
void HandleSpeedLogic();
void HandleTurnLogic();
void HandleFaceLogic();
void Accelerate();
void Deccelerate();
bool IsSpeedUnderMax();
bool IsSpeedAtLeastMin();
bool IsWithinStopProximity();
void CheckTurnThreshold();
void GetCarDirection();
void RightTurnLogic();
void LeftTurnLogic();

// enum definitions
// state machine that controls car movement (acceleration, decceleration, constant and stopped)
enum car_movement {
  cruising,
  accelerating,
  deccerating,
  stopped
};

// state machine that controls car direction
enum car_dir {
  forward,
  backward,
  right,
  left
};

enum led_display {
  smiley_face,
  frowny_face
};

// variable definitions
car_movement carMovementState = accelerating;
car_dir carDirState = forward;
led_display faceState = smiley_face;
uint16_t carSpeed = 0;
bool obstacleDetected = false;
car_dir lastTurnedDirection = left;
long distanceToObject = 1000000; 

int main() {

  // set baud rate for serial transmission, flush before printing anything
  Serial.begin(9600);

  // initialization functions
  initPWMTimer3();
  initPWMTimer4();
  // initialize SPI
  initSPI();
  // initialize Timer
  initTimer0();
  initTimer1();
  // initialize Motor
  initMotorPins();
  ultrasonic_begin();

  while (1) {

    Serial.println(carSpeed);
    distanceToObject = ultrasonic_read();
    HandleSpeedLogic();
    HandleTurnLogic();
    //HandleFaceLogic();
    delayMs(LOOP_DELAY);
  }

  return 0;
}

void HandleSpeedLogic() {

  switch (carMovementState) {
    case cruising:
      Serial.println("Cruising");
      break;

    case accelerating:
      Serial.println("Accelerating");
      Accelerate();
      changeDutyCycle(carSpeed, carSpeed);
      break;

    case deccerating:
      Serial.println("Deccerating");
      Deccelerate();
      changeDutyCycle(carSpeed, carSpeed);
      break;

    case stopped:
      Serial.println("Stopped");
      break;
  }
}

void HandleTurnLogic() {

  switch (carDirState) {
    case forward:
      Serial.println("Moving Forward");
      if (!IsWithinStopProximity()) {
        moveForward();
      }
      else {
        carSpeed = 0;
        carMovementState = accelerating;
        CheckTurnThreshold();
      }
      break;
    case backward:
      Serial.println("Moving Backward");
      CheckTurnThreshold();
      break;
    case right:
      Serial.println("Moving Right");
      RightTurnLogic();
      break;
    case left:
    Serial.println("Moving Left");
      LeftTurnLogic();
      break;
  }
}

void HandleFaceLogic() {

  switch (faceState) {
    case smiley_face:
      smile();
      break;
    case frowny_face:
      frown();
      break;
    }
}

void Accelerate() {

  if (IsSpeedUnderMax()) {
    carSpeed += ACCELERATION_RATE;
  }
  else {
    carSpeed = MAX_DUTY_CYCLE;
    carMovementState = cruising;
  }
}

void Deccelerate() {

  if (IsSpeedAtLeastMin()) {
    carSpeed -= ACCELERATION_RATE;
  }
  else {
    carSpeed = MIN_DUTY_CYCLE;
    carMovementState = stopped;
  }
}

bool IsSpeedUnderMax() {

  if (carSpeed < MAX_DUTY_CYCLE) {
    return true;
  }

  return false;
}

bool IsSpeedAtLeastMin() {

  if (carSpeed >= MIN_DUTY_CYCLE) {
    return true;
  }

  return false;
}

// check if object is within a certain distance
bool IsWithinStopProximity() {
  // if below STOP_PROXIMITY:
  if (distanceToObject < STOP_PROXIMITY) {
    Serial.println("Detected object");
    faceState = frowny_face;
    return true;
  }
  return false;
}

// check that object is far away enough to turn
void CheckTurnThreshold() {
  
  if (distanceToObject < TURN_THRESHOLD) {
    moveBackward();
    carDirState = backward;
  }
  else {
    GetCarDirection();
    carSpeed = 0;
    carMovementState = accelerating;
  }
}

void GetCarDirection() {

  if (lastTurnedDirection == right) {
    carDirState = left;
    lastTurnedDirection = left;
  }
  else {
    carDirState = right;
    lastTurnedDirection = right;
  }
}

void RightTurnLogic() {

  if (IsWithinStopProximity()) {
    turnRight();
  }
  else {
    moveForward();
    faceState = smiley_face;
    carDirState = forward;
  }
}

void LeftTurnLogic() {

  if (IsWithinStopProximity()) {
    turnLeft();
  }
  else {
    moveForward();
    faceState = smiley_face;
    carDirState = forward;
  }
}