#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <Arduino.h>

void initPWMTimer3();
void initPWMTimer4();
void changeDutyCycle(uint16_t leftMotorSpeed, uint16_t rightMotorSpeed);

#endif