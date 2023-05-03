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
static u8 u8_gs_currentMode = APP_U8_PROG_MODE;
static u8 u8_gs_resetFlag = APP_U8_FLAG_DOWN;

/*******************************************************************************************************************************************************************/
/*
 Name: APP_vdInitialization
 Input: void
 Output: void
 Description: Function to initialize Application.
*/
void APP_initialization( void )
{
	UART_initialization();

    TIMER_timer0NormalModeInit(DISABLED);


    u8 count;
    char buffer[5];

    SPI_init();


    while(1)
    {
        u8 data;
        count = SPI_receive(&data);
    }
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
	/* Toggle Forever */
	while(1)
	{
		switch ( u8_gs_currentMode )
		{
			case APP_U8_PROG_MODE:
				UART_transmitString( ( u8 * ) "Please Enter Card PAN\n\r" );
				//UART_receiveByte();
				//while are not matched
				{
					UART_transmitString( ( u8 * ) "Please Enter New PIN\n\r" );
					//UART_receiveByte();
					UART_transmitString( ( u8 * ) "Please Confirm New PIN\n\r" );
					//UART_receiveByte();
					// if PINs are matched
					break;
					// if PINs are not matched, not numeric, or > 4
					UART_transmitString( ( u8 * ) "Wrong PIN\n\r" );
				}
				u8_gs_currentMode = APP_U8_USER_MODE;
				break;
				
			case APP_U8_USER_MODE:
				
				break;
		}
	}

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