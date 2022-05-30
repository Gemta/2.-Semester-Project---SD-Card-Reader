#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "SPI.h"
#include "SD.h"
#include "SD_print.h"
#include "usart.h"

//Main function
int main(void){

    uart_init();
    io_redirect();

    //Array for responses
    uint8_t resp[5];

    //Initialize SPI communication
    spi_init();

    //Start the power up sequence for the SD card
    SD_power_up_seq();

    //Set card to idle
    printf("Sending CMD0...\r\n");
    resp[0] = SD_go_idle_state();
    printf("Response: \r\n");
    SD_print_R1(resp[0]);

    //Send if conditions
    printf("\nSending CMD8...\r\n");
    SD_send_if_cond(resp);
    printf("Response: \r\n");
    SD_read_response_R7(resp);


    while(1){

    }

    return 0;
}

