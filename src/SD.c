#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "SD.h"
#include "usart.h"

//SD card reader power up sequence
void SD_power_up_seq(void){

    //Deselect the SD card reader
    SD_disable();

    //Delay to give SD crad reader time to power up
    _delay_ms(10);

    //Send 80 clock cycles to synchronize
    for(uint8_t i; i < 10; i++){ //There is 8 clock cycles per byte, hence send 10
        SPI_transmit(0xFF);
    }

    //Deselect SD card reader
    SD_disable();
    SPI_transmit(0xFF);

}

//Send command to SD card reader
void SD_command(uint8_t cmd, uint32_t arg, uint8_t crc){

    /*A 8-bit command index is send,
    then a 32-bit argument for it,
    and finally a 8-bit CRC (Cyclic Redundancy Check)*/


    //Send command to SD card reader
    SPI_transmit(cmd|0x40); //bitwise OR with 0x40 in order to set bit 47 to 1

    //Send arguments
    SPI_transmit((uint8_t)(arg >> 24));
    SPI_transmit((uint8_t)(arg >> 16));
    SPI_transmit((uint8_t)(arg >> 8));
    SPI_transmit((uint8_t)(arg));

    //Send the CRC
    SPI_transmit(crc|0x01);

}

//Response from SD card, after sending CMD0
uint8_t SD_read_response_R1(void){

    uint8_t i = 0, resp_R1;

    //Pull for R1 response until data is received
    while((resp_R1 = SPI_transmit(0xFF)) == 0xFF){

        i++;

        //Break if no data has been received for 8 bytes
        if(i > 8) break;

    }

    return resp_R1;
}

//Response from SD card, after sending CMD8
void SD_read_response_R7(uint8_t *resp){

    //Read response 1 in R7
    resp[0] = SD_read_response_R1();

    //If there is an error reading R1, return
    if(resp[0] > 1) return;

    //Read remaining bytes in R7
    resp[1] = SPI_transmit(0xFF);
    resp[2] = SPI_transmit(0xFF);
    resp[3] = SPI_transmit(0xFF);
    resp[4] = SPI_transmit(0xFF);

}

//Use CMD0 to set SD card to idle state
uint8_t SD_go_idle_state(void){
    
    //Assert chip select
    SPI_transmit(0xFF); //Ensures the card regonizes the change
    SD_enable();
    SPI_transmit(0xFF); //Ensures the card regonizes the change

    //Send CMD0
    SD_command(CMD0, CMD0_arg, CMD0_CRC);
    
    //Read response
    uint8_t resp_R1 = SD_read_response_R1();

    //Deassert chip select
    SPI_transmit(0xFF); //Ensures the card regonizes the change
    SD_disable();
    SPI_transmit(0xFF); //Ensures the card regonizes the change

    return resp_R1;
}

//Use CMD8 to check version/status
void SD_send_if_cond(uint8_t *resp){

    //Assert chip select
    SPI_transmit(0xFF); //Ensures the card regonizes the change
    SD_enable();
    SPI_transmit(0xFF); //Ensures the card regonizes the change

    //Send CMD8
    SD_command(CMD8, CMD8_arg, CMD8_CRC);

    //Read response
    SD_read_response_R7(resp);

    //Deassert chip select
    SPI_transmit(0xFF); //Ensures the card regonizes the change
    SD_disable();
    SPI_transmit(0xFF); //Ensures the card regonizes the change

}



