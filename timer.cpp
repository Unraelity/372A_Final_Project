// Author:       Benjamin Feuerborn
//----------------------------------------------------------------------

#include "timer.h"

// initialize timer 0 to debounce states
void initTimer0() {
    /*
        for a millisecond delay:
        prescaler = 64 (CS0 = 011)
        OCR0A = 250
    */

    // configure Timer0
    // WGM0 = 010 (CTC mode)
    TCCR0B &= ~(1 << WGM02);
    TCCR0A |= (1 << WGM01);
    TCCR0A &= ~(1 << WGM00);
}

// millisecond delay
void delayMs(unsigned int delay) {

    unsigned int delayCount = 0;

    // define the prescaler
    // 64 prescaler (CS0 = 011)
    TCCR0B &= ~(1 << CS02); // 0
    TCCR0B |= (1 << CS01);  // 1
    TCCR0B |= (1 << CS00);  // 1

    // define the output compare register
    OCR0A = 249;

    while (delayCount < delay) {
        
        TIFR0 |= (1 << OCF0A); // set timer flag to 1
        TCNT0 = 0;             // set timer register to 0

        // wait for the timer flag to be set
        while (!(TIFR0 & (1 << OCF0A)))
            ;

        delayCount++; // increment delay count
    }
}