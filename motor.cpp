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
    PORTD |= (1 << PD7);
    PORTB &= ~(1 << PB0);

    // move right motor forward
    PORTB |= (1 << PB1);
    PORTB &= ~(1 << PB3);
}

void moveBackward() {

    // move left motor backward
    PORTD &= ~(1 << PD7); 
    PORTB |= (1 << PB0);

    // move right motor backward
    PORTB &= ~(1 << PB1);
    PORTB |= (1 << PB3);
}

void turnLeft() {

    // move left motor backward
    PORTD &= ~(1 << PD7);
    PORTB |= (1 << PB0);

    // move right motor forward
    PORTB |= (1 << PB1);
    PORTB &= ~(1 << PB3);
}

void turnRight() {

    // move left motor forward
    PORTD |= (1 << PD7);
    PORTB &= ~(1 << PB0);

    // move right motor backward
    PORTB &= ~(1 << PB1);
    PORTB |= (1 << PB3);
}

void stopMotors() {

    // sets both motors speed to 0
    changeDutyCycle(0, 0);
}
