#include "motor.h"

/*
MOTOR BEHAVIOR:

IN1      IN2      Motor A Behavior
 1        0       Spins forwards
 0        1       Spins backward
 1        1       Stops (immediate, brakes)
 0        0       Stops (slowly, coast)

IN3      IN4      Motor B Behavior
 1        0       Spins forwards
 0        1       Spins backward
 1        1       Stops (immediate, brakes)
 0        0       Stops (slowly, coast)
*/

// initialize motor direction pins
void initMotorPins() {
    
    DDRD |= (1 << PD7);  // set D7 to ouput -> IN1
    DDRB |= (1 << PB0);  // set B0 to ouput -> IN2
    DDRB |= (1 << PB1);  // set B1 to ouput -> IN3
    DDRB |= (1 << PB3);  // set B3 to ouput -> IN4
}

void moveForward() {

    // move left motor forward
    PORTD |= (1 << PD7);   // IN1 HIGH
    PORTB &= ~(1 << PB0);  // IN2 LOW

    // move right motor forward
    PORTB |= (1 << PB1);   // IN3 HIGH
    PORTB &= ~(1 << PB3);  // IN4 LOW
}

void moveBackward() {

    // move left motor backward
    PORTD &= ~(1 << PD7);  // IN1 LOW
    PORTB |= (1 << PB0);   // IN2 HIGH

    // move right motor backward
    PORTB &= ~(1 << PB1);  // IN3 LOW
    PORTB |= (1 << PB3);   // IN4 HIGH
}

void turnLeft() {
    // Left Motor Backward
    PORTD &= ~(1 << PD7);  // IN1 LOW
    PORTB |= (1 << PB0);   // IN2 HIGH

    // Right Motor Forward
    PORTB |= (1 << PB1);   // IN3 HIGH
    PORTB &= ~(1 << PB3);  // IN4 LOW
}

void turnRight() {
    // Left Motor Forward
    PORTD |= (1 << PD7);   // IN1 HIGH
    PORTB &= ~(1 << PB0);  // IN2 LOW

    // Right Motor Backward
    PORTB &= ~(1 << PB1);  // IN3 LOW
    PORTB |= (1 << PB3);   // IN4 HIGH
}

void stopMotors() {
    // Stop both motors
    changeDutyCycle(0, 0);
}
