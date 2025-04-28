// Author:       Nick Brown
//----------------------------------------------------------------------

#include "pwm.h"

void initPWMTimer3() {

    // set to FAST PWM 10-bit mode, non-inverting
    TCCR3A |= (1 << COM3A1); // sets COM3A1 to 1
    // (clear  OCnA/OCnB on compare match, set OCnA/OCnB/OCnC at BOTTOM (non-inverting mode))
    TCCR3B |= (1 << WGM33);  // set WGM33 to 1
    TCCR3B |= (1 << WGM32);  // sets WGM32 to 1
    TCCR3A |= (1 << WGM31);  // sets WGM31 to 1
    TCCR3A &= ~(1 << WGM30); // sets WGM30 to 0

    // table 17-6, set prescaler to 8 (010)
    TCCR3B &= ~((1 << CS32) | (1 << CS30));
    TCCR3B |= (1 << CS31);

    DDRE |= (1 << DDE3); // set Pin 5 on board to output, which is OC4C, PORTH5, PWM}

    // duty cycle 0%
    OCR3A = 0;
    ICR3 = 1023;
}

void initPWMTimer4() {

    TCCR4B |= (1 << WGM43);  // sets WGM43 to 1
    TCCR4A |= (1 << WGM41);  // sets WGM41 to 1
    TCCR4B |= (1 << WGM42);  // sets WGM42 to 1
    TCCR4A &= ~(1 << WGM40); // sets WGM40 to 0
    // table 17-4, Fast PWM non-inverting mode
    TCCR4A &= ~(1 << COM4A0);
    TCCR4A |= (1 << COM4A1);
    // table 17-6, set prescaler to 8 (010)
    TCCR4B &= ~((1 << CS42) | (1 << CS40));
    TCCR4B |= (1 << CS41);
    DDRH |= (1 << DDH3); // set Pin 6 on board to output, which is OC4C, PORTH5, PWM}

    ICR4 = 1023;
    OCR4A = 1023;
}

void changeDutyCycle(uint16_t leftMotorSpeed, uint16_t rightMotorSpeed) {

    if (leftMotorSpeed > 1023) {
        leftMotorSpeed = 1023;
    }

    if (rightMotorSpeed > 1023) {
        rightMotorSpeed = 1023;
    }

    OCR3A = leftMotorSpeed;   // Left Motor
    OCR4A = rightMotorSpeed;  // Right Motor
}
