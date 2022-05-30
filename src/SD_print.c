#include "SD_print.h"
#include "SD.h"
#include "usart.h"

//Error printing from R1
void SD_print_R1(uint8_t resp){

    if(resp & 0b10000000){ printf("\tError: MSB = 1\r \n"); return; }
    if(resp == 0){ printf("\tCard ready\r \n"); return; }
    if(PARAM_ERROR(resp)){ printf("\tParameter Error\r \n"); }
    if(ADDR_ERROR(resp)){ printf("\tAddress Error\r \n"); }
    if(ERASE_SEQ_ERROR(resp)){ printf("\tErase Sequence Error\r \n"); }
    if(CRC_ERROR(resp)){ printf("\tCRC Error\r \n"); }
    if(ILLEGAL_CMD(resp)){ printf("\tIlligal Command\r \n"); }
    if(ERASE_RESET(resp)){ printf("\tErase Reset Error\r \n"); }
    if(IN_IDLE(resp)){ printf("\tIn Idle State\r \n"); }

}

//Error printing for R7
void SD_print_R7(uint8_t *resp){

    SD_print_R1(resp[0]);

    if(resp[0] > 1) return;

    printf("\tCommand version: ");
    printf("\n" + CMD_VER(resp[1]));
    printf("\r\n");

    printf("\tVoltage Accepted: ");
    if(VOL_ACC(resp[3]) == VOLTAGE_ACC_27_33)
        printf("2.7 - 3.6V\r\n");
    else if(VOL_ACC(resp[3]) == VOLTAGE_ACC_LOW)
        printf("Low Voltage\r\n");
    else if(VOL_ACC(resp[3]) == VOLTAGE_ACC_RES1)
        printf("Reserved\r\n");
    else if(VOL_ACC(resp[3]) == VOLTAGE_ACC_RES2)
        printf("Reserved\r\n");
    else
        printf("Not Defined\r\n");

    printf("\tEcho: ");
    printf("\n" + CMD_VER(resp[4]));
    printf("\r\n");

}



