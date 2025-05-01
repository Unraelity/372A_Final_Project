// Author:       Benjamin Feuerborn
//----------------------------------------------------------------------

#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
	// CTC setting in the timer register
    TCCR1A &=~ (1 << WGM10);
    TCCR1A &=~ (1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B &=~ (1 << WGM13);

    // set the bits for the prescaler (1) 
    TCCR1B |=  (1 << CS10);
    TCCR1B &=~ (1 << CS11);
    TCCR1B &=~ (1 << CS12);

    // CTC compare value (1us)
    OCR1A = 16;
    // slide 14 lecture 7
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    unsigned int delayCnt = 0;
    TCNT1 = 0; // starting the timer at 0
    TIFR1 |= (1 << OCF1A); // set compare flag to start timer

    // POLL OCF0A flag
    while (delayCnt < delay) {
        if (TIFR1 & (1 << OCF1A)) { // increment only while the flag is set (timer reached maxval = OCR0A)
            delayCnt++;
            TIFR1 |= (1 << OCF1A); // re-start timer, will go to 0 before reaching the if statement above
        }
    }
}

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    // CTC setting in the timer register
    TCCR0A &=~ (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &=~ (1 << WGM02);

    // set the bits for the prescaler (64) 
    TCCR0B |=  (1 << CS00);
    TCCR0B |= (1 << CS01);
    TCCR0B &=~ (1 << CS02);

    // CTC compare value (1ms)
    OCR0A = 249;
    // calculations done with formula in slide 8 lecture 7
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
   
    unsigned int delayCnt = 0;
    TCNT0 = 0; // starting the timer at 0
    TIFR0 |= (1 << OCF0A); // set compare flag to start timer

    // POLL OCF0A flag
    while (delayCnt < delay) {
        if (TIFR0 & (1 << OCF0A)) { // increment only while the flag is set (timer reached maxval = OCR0A)
            delayCnt++;
            TIFR0 |= (1 << OCF0A); // re-start timer, will go to 0 before reaching the if statement above
        }
    }
}
