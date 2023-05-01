/*
 * app_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit Team
 *  Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "app_interface.h"

/* Declaration and Initialization */

/* Global variables */

/**
 *
 */
void APP_initialization(void) {
    EXI_enablePIE(MASTER_REQ_RECEIVE_INT, MASTER_REQ_RECEIVE_SENSE);
    EXI_intSetCallBack(MASTER_REQ_RECEIVE_INT,APP_trigger);
    SPI_init();

//    u8 data;
//    SPI_receive(&data);
    u8 test = 1;

// 	SPI_send('H');
// 	SPI_send('O');
// 	SPI_send('S');
// 	SPI_send('S');
// 	SPI_send('A');
// 	SPI_send('M');
//     while(1)
// 	{
// 		SPI_send('b');
// 	}
}


/**
 *
 */
void APP_startProgram(void) {

}

void APP_trigger(void) {
    // receive SPI data

}