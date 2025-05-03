#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <Arduino.h>

// constant definitions
#define MIN_DUTY_CYCLE 450
#define MAX_DUTY_CYCLE 1024

void initPWMTimer3();
void initPWMTimer4();
void changeDutyCycle(uint16_t leftMotorSpeed, uint16_t rightMotorSpeed);

#endif