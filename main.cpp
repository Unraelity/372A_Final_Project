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

// constant definitions
#define LOOP_DELAY 100       // delay between loops
#define ACCELERATION_RATE 1  // per loop

// funciton definitions
void HandleSpeedLogic();
void HandleTurnLogic();
void HandleFaceLogic();
void Accelerate();
void Deccelerate();
bool IsSpeedUnderMax();
bool IsSpeedAtLeastMin();

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
  left,
  right
};

enum led_display {
  smiley_face,
  frowny_face
};

// variable definitions
car_movement carState = stopped;
led_display faceState = smiley_face;
uint16_t carSpeed = 0;

int main() {

  // initialization functions
  initPWMTimer3();
  initPWMTimer4();
  // initialize SPI
  initSPI();
  // initialize Timer
  initTimer0();
  // initialize Motor
  initMotorPins();

  // set baud rate for serial transmission, flush before printing anything
  Serial.begin(9600);

  while (1) {

    HandleSpeedLogic();
    HandleTurnLogic();
    HandleFaceLogic();
    delayMs(LOOP_DELAY);
  }

  return 0;
}

void HandleSpeedLogic() {

  switch (carState) {
    case cruising:
      break;

    case accelerating:
      Accelerate();
      break;

    case deccerating:
      Deccelerate();
      break;

    case stopped:
      break;
  }
}

void HandleTurnLogic() {

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
    carState = cruising;
  }
}

void Deccelerate() {

  if (IsSpeedAtLeastMin()) {
    carSpeed -= ACCELERATION_RATE;
  }
  else {
    carState = stopped;
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