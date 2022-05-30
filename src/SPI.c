#include <stdio.h>
#include <avr/io.h>

#include "SPI.h"

//Initialization of SPI as master
void spi_init(void){

    //CS, MISO and SCK set to output
    DDR_SPI = (1 << CS) | (1 << MISO) | (1 << SCK);

    //Enable pullup on MISO
    DDR_SPI |= (1 << MISO);

    //Enable SPI, set as master, and set clock rate to fosc/128
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);

}

//Send and receive data over SPI
uint8_t SPI_transmit(uint8_t data){

    //Start transmission
    SPDR = data;

    //Wait for transmission to complete
    while(!(SPSR & (1 << SPIF)));

    return SPDR;

}

