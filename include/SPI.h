#include <stdio.h>
#include <avr/io.h>

//Pins
#define DDR_SPI     DDRB
#define PORT_SPI    PORTB
#define CS          PCINT2
#define MOSI        PCINT3
#define MISO        PCINT4
#define SCK         PCINT5

#define SD_enable()     PORT_SPI &= ~(1 << CS)
#define SD_disable()    PORT_SPI |= (1 << CS)

void spi_init(void);
uint8_t SPI_transmit(uint8_t);

