#include "ultr_sonic.h"
#include "timer.h" 



void ultrasonic_begin() {
    // Set TRIG as output
    DDRE |= (1 << PE4);
    // Set ECHO as input
    DDRE &= ~(1 << PE5);

    
}

unsigned long measure_pulse() {
    unsigned long count = 0;

    // Wait for echo pin to go HIGH
    while (!(PINE & (1 << PE5)));

    // Count how long echo pin stays HIGH
    while (PINE & (1 << PE5)) {
        count++;
        delayUs(1);  
    }

    return count;
}

unsigned long ultrasonic_read() {
    // Trigger pulse
    PORTE &= ~(1 << PE4);  // LOW
    delayUs(2);
    PORTE |= (1 << PE4);   // HIGH
    delayUs(10);
    PORTE &= ~(1 << PE4);  // LOW

    // Measure echo pulse width
    unsigned long duration = measure_pulse();

    // Convert pulse duration to distance (inches)
    unsigned long distance = duration * 0.00675; 

    return distance;
}




