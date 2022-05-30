#include <stdio.h>
#include <avr/io.h>

#include "SPI.h" 

//Command definitions
#define CMD0            0
#define CMD0_arg        0x00000000
#define CMD0_CRC        0x94
#define CMD8            8
#define CMD8_arg        0x0000001AA
#define CMD8_CRC        0x86 //3.3V VHS

void SD_power_up_seq(void);
void SD_command(uint8_t cmd, uint32_t arg, uint8_t crc);
uint8_t SD_read_response_R1(void);
void SD_read_response_R7(uint8_t *resp);
uint8_t SD_go_idle_state(void);
void SD_send_if_cond(uint8_t *resp);

