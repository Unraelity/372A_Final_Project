// Author(s):       Benjamin Feuerborn, Tyler Dye, Nick Brown, Abdullah Al Shumais
// Due Date:        5/5/25
// Assignment:      Final Project
//----------------------------------------------------------------------

#include <Arduino.h>
#include "pwm.h"
#include "motor.h"
#include "spi.h"

// constant definitions
#define ACCELERATION_RATE 1  // per loop

// funciton definitions
void HandleFaceLogic();

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
led_display faceState = smiley_face;

int main() {

  // initialization functions
  initPWMTimer3();
  initPWMTimer4();

  // set baud rate for serial transmission, flush before printing anything
  Serial.begin(9600);

  // initialize SPI
  initSPI();

  while (1) {
    HandleFaceLogic();
  }

  return 0;
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