// Description: Function prototypes for spi.cpp
//----------------------------------------------------------------------//

#ifndef SPI_H
#define SPI_H

#include <Arduino.h>
#include <avr/io.h>

void initSPI();
void spi_read(unsigned char data);
void spi_write(unsigned char address, unsigned char data);
void upArrow();
void downArrow();
void leftArrow();
void rightArrow();
void allRed();

#endif