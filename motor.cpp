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
    
    DDRB |= (1 << PB3);  // set B3 to output -> IN1
    DDRB |= (1 << PB1);  // set B1 to output -> IN2
    DDRB |= (1 << PB0);  // set B0 to output -> IN3
    DDRB |= (1 << PB2);  // set B2 to output -> IN4
}

void moveForward() {

    //Serial.println("In forward function");

    // move left motor forward
    PORTB |= (1 << PB3);
    PORTB &= ~(1 << PB1);

    // move right motor forward
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB2);
}

void moveBackward() {

    //Serial.println("In backward function");

    // move left motor backward
    PORTB &= ~(1 << PB3); 
    PORTB |= (1 << PB1);

    // move right motor backward
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB2);
}

void turnLeft() {

    //Serial.println("In left function");

    // move left motor backward
    PORTB &= ~(1 << PB3);
    PORTB |= (1 << PB1);

    // move right motor forward
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB2);
}

void turnRight() {

    //Serial.println("In right function");

    // move left motor forward
    PORTB |= (1 << PB3);
    PORTB &= ~(1 << PB1);

    // move right motor backward
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB2);
}

// stops over time
void stopMotors() {

    //Serial.println("In stop function");

    // turn off left motor
    PORTB &= ~(1 << PB3);
    PORTB &= ~(1 << PB1);

    // turn off right motor
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB2);
}

void brake() {

    //Serial.println("In break function");

    // brake left wheel
    PORTB |= (1 << PB3);
    PORTB |= (1 << PB1);

    // brake right wheel
    PORTB |= (1 << PB0);
    PORTB |= (1 << PB2);
}
