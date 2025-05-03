// Author:       Benjamin Feuerborn
//----------------------------------------------------------------------

#include "spi.h"

/*
    1. All communication with the 8x8 led matrix must be done over the SPI related pins.
    2. Read the 8x8 MAX7219 datasheet for setting up SPI mode.
*/

void initSPI()
{
    // set MOSI, SCK, and CS as ouptut
    DDRB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
    // PB2: pin 51 -> DIN
    // PB1: pin 52 -> CLK
    // PB0: pin 53 -> CS

    // enable SPI, master mode, and set clock rate fosc/16
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);

    // enable and configure 8x8 led matrix
    spi_write(0x09, 0x00); // no decode
    spi_write(0x0A, 0x03); // intensity (0x00-0x0F)
    spi_write(0x0B, 0x07); // scan limit = all 8 digits
    spi_write(0x0C, 0x01); // shutdown mode = 1 (normal)
    spi_write(0x0F, 0x00); // display test = off
}

void spi_read(unsigned char data)
{
    // start transmission
    SPDR = data;

    // wait for transmission to complete
    while (!(SPSR & (1 << SPIF)))
        ;
}

void spi_write(unsigned char address, unsigned char data)
{
    PORTB &= ~(1 << PB0);
    spi_read(address);
    spi_read(data);
    PORTB |= (1 << PB0);
}

void display(const unsigned char *data)
{
    for (unsigned char i = 0; i < 8; i++)
    {
        spi_write(i + 1, data[i]);
    }
}

void upArrow() {
    unsigned char up[8] = {0x00, 0x04, 0x06, 0xFF, 0xFF, 0x06, 0x04, 0x00};
    display(up);
}

void leftArrow() {
    unsigned char left[8] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18};
    display(left);
}

void rightArrow() {
    unsigned char right[8] = {0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18};
    display(right);
}

void allRed() {
    unsigned char all[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    display(all);
}