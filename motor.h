#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#include <Arduino.h>
#include "pwm.h"

void initMotorPins();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stopMotors();

#endif