// Author(s):       Benjamin Feuerborn, Tyler Dye, Nick Brown, Abdullah Al Shumais
// Due Date:        5/5/25
// Assignment:      Final Project
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
void HandleMotorLogic();
void HandleFaceLogic();
void Accerate();
void Deccerate();
bool IsSpeedUnderMax();
bool IsSpeedAtLeastMin();

// enum definitions
enum car_movement {
  cruising,
  accelerating,
  deccerating,
  stopped
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

  // set baud rate for serial transmission, flush before printing anything
  Serial.begin(9600);

  // initialize SPI
  initSPI();

  while (1) {

    HandleMotorLogic();
    HandleFaceLogic();
    delayMs(LOOP_DELAY);
  }

  return 0;
}

void HandleMotorLogic() {

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