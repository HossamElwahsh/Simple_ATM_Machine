/*
 * app_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This file contains all Application (APP) functions' implementation.
 */ 

/* APP */
#include "app_interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global variables */

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize Application.
*/
void APP_initialization( void )
{
    TIMER_timer0NormalModeInit(DISABLED);



    return;
    u8 count;
    char buffer[5];

    SPI_init();


    while(1)
    {
        u8 data;
        count = SPI_receive(&data);
    }
//	TIMER_timer0NormalModeInit(DISABLED);
//    TIMER_delay_ms(2000);

}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdStartProgram
 Input: void
 Output: void
 Description: Function to start program.
*/
void APP_startProgram  ( void )
{

//    SPI_send(0xFF); //H << 1
//    SPI_send(0xFF); //H << 1
    //TIMER_delay_ms(500);
//    SPI_send('H');
//	SPI_send('H');
//	SPI_send('H');
//    SPI_send('i');
//	SPI_send(0b00000001); // 1
//	SPI_send(0b10000000); // 127
//	SPI_send(0b00000010); // 2
//	SPI_send(0b00000011); // 3
//	SPI_send(0b00000100); // 4
    //TIMER_delay_ms(500);
}

/*******************************************************************************************************************************************************************/