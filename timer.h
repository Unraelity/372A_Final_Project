#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <Arduino.h>

void initTimer1();
void delayUs(unsigned int delay);
void initTimer0();
void delayMs(unsigned int delay);

#endif
