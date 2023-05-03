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
	
	LCD_init();     // Init LCD
	LCD_clear();    // Clear LCD's display

//    u8 count;
//    char buffer[5];
//
//    SPI_init();
//
//
//    while(1)
//    {
//        u8 data;
//        count = SPI_receive(&data);
//    }
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
	u8 u8_l_recData = 0;
	u8 u8_l_cardPAN[15] = { 0 };
	u8 u8_l_newPIN[10] = { 0 };
	u8 u8_l_confirmedPIN[10] = { 0 };
	u8 u8_l_index = 0;	
	
	/* Toggle Forever */
	while(1)
	{
		switch ( u8_gs_currentMode )
		{
			case APP_U8_PROG_MODE:
			
				///* Step 1: Display "Please Enter Card PAN" on terminal */
				//UART_transmitString( ( u8 * ) "Please Enter Card PAN\n\r" );
				//
				///* Step 2: Receive PAN value */
				//while ( u8_l_recData != 13 )
				//{
				//	UART_receiveByteBlock( UART_U8_POLLING_MODE, &u8_l_recData );
				//	u8_l_cardPAN[u8_l_index] = u8_l_recData;					
				//	u8_l_index++;
				//}
				//
				//u8_l_cardPAN[u8_l_index] = '\0';								
				//
				//u8_l_recData = 0;
				//u8_l_index = 0;	
				
				/* Step 3: Display "Please Enter New PIN" on terminal */
				UART_transmitString( ( u8 * ) "Please Enter New PIN\r" );
				
				/* Step 4: Receive New PIN value */
				while ( u8_l_recData != 13 )
				{
					UART_receiveByteBlock( UART_U8_POLLING_MODE, &u8_l_recData );
					u8_l_newPIN[u8_l_index] = u8_l_recData;
					u8_l_index++;
				}
				
				u8_l_newPIN[u8_l_index] = '\0';
								
				
				/* Step 5: Display "Please Confirm New PIN" on terminal */
				UART_transmitString( ( u8 * ) "Please Confirm New PIN\r" );
				
				u8_l_recData = 0;
				u8_l_index = 0;
								
				/* Step 6: Receive New PIN value */
				while ( u8_l_recData != 13 )
				{
					UART_receiveByteBlock( UART_U8_POLLING_MODE, &u8_l_recData );
					u8_l_confirmedPIN[u8_l_index] = u8_l_recData;
					u8_l_index++;
				}
								
				u8_l_confirmedPIN[u8_l_index] = '\0';
				
				//u8_l_recData = 0;
				//u8_l_index = 0;
				
				if ( !(strcmp( u8_l_newPIN, u8_l_confirmedPIN )) )
				{
					LCD_sendString( "OK" );					
				}
				else
				{
					LCD_sendString( "WRONG" );
				}
				
				LCD_setCursor ( LCD_LINE1, LCD_COL0 );
				
				LCD_sendString( ( u8 * )  u8_l_newPIN );
				//LCD_sendString( " " );
				LCD_sendString( ( u8 * )  u8_l_confirmedPIN );
				
				////while are not matched
				//{
				//	
				//	
				//	
				//	//UART_receiveByte();
				//	UART_transmitString( ( u8 * ) "Please Confirm New PIN\n\r" );
				//	//UART_receiveByte();
				//	// if PINs are matched
				//	break;
				//	// if PINs are not matched, not numeric, or > 4
				//	UART_transmitString( ( u8 * ) "Wrong PIN\n\r" );
				//}
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