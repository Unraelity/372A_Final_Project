// Author:       Nick Brown
//----------------------------------------------------------------------

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
    
    DDRA |= (1 << PA0);  // set A2 to output -> IN1
    DDRA |= (1 << PA1);  // set A0 to output -> IN2
    DDRA |= (1 << PA2);  // set A1 to output -> IN3
    DDRA |= (1 << PA3);  // set A3 to output -> IN4



}

void moveForward() {

    // move left motor forward
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);

    // move right motor forward
    PORTA |= (1 << PA2);
    PORTA &= ~(1 << PA3);
}

void moveBackward() {

    // move left motor backward
    PORTA &= ~(1 << PA0); 
    PORTA |= (1 << PA1);

    // move right motor backward
    PORTA &= ~(1 << PA2);
    PORTA |= (1 << PA3);
}

void turnLeft() {

    // move left motor backward
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);

    // move right motor forward
    PORTA |= (1 << PA2);
    PORTA &= ~(1 << PA3);
}

void turnRight() {

    // move left motor forward
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);

    // move right motor backward
    PORTA &= ~(1 << PA2);
    PORTA |= (1 << PA3);
}

// stops over time
void stopMotors() {

    // turn off left motor
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA1);

    // turn off right motor
    PORTA &= ~(1 << PA2);
    PORTA &= ~(1 << PA3);
}

void brake() {

    // brake left wheel
    PORTA |= (1 << PA0);
    PORTA |= (1 << PA1);

    // brake right wheel
    PORTA |= (1 << PA2);
    PORTA |= (1 << PA3);
}
