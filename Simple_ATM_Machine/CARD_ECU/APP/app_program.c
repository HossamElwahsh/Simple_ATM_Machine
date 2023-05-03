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
 Name: APP_initialization
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
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to start program.
*/
void APP_startProgram  ( void )
{
	/* Toggle Forever */
	while(1)
	{
		/* Check 1: Reset is pressed */
		if ( u8_gs_resetFlag == APP_U8_FLAG_UP )
		{
			u8 u8_l_userInput = 0;
			
			/* Step 1: Display "Please press 1 for entering user mode and 2 for programming mode:" on terminal */
			UART_transmitString( ( u8 * ) "Please press 1 for entering user mode and 2 for programming mode: " );
			
			/* Step 2: Receive UsrInput value */
			UART_receiveByteBlock( &u8_l_userInput );
			
			/* Check 1.1: Required usrInput */
			switch ( u8_l_userInput )
			{
				case '1': u8_gs_currentMode = APP_U8_USER_MODE; break;
				case '2': u8_gs_currentMode = APP_U8_PROG_MODE; break;
			}
		}
		
		/* Check 2: Required currentMode */
		switch ( u8_gs_currentMode )
		{
			case APP_U8_PROG_MODE:
			
				u8_gs_resetFlag = APP_U8_FLAG_UP;
				
				APP_programmerMode();
				
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
/*
 Name: APP_programmerMode
 Input: void
 Output: void
 Description: Function to start program.
*/
void APP_programmerMode( void )
{
	u8 u8_l_equalPINsFlag = APP_U8_FLAG_DOWN;
	u8 u8_l_charFlag =  APP_U8_FLAG_DOWN;
	
	u8 u8_l_recData = 0;
	u8 u8_l_cardPAN[20] = { 0 };
	u8 u8_l_newPIN[10] = { '\0' };
	u8 u8_l_confirmedPIN[10] = { '\0' };
	u8 u8_l_index = 0;
		
	/* Step 1: Display "Please Enter Card PAN" on terminal */
	UART_transmitString( ( u8 * ) "Please Enter Card PAN: " );
	
	/* Step 2: Receive PAN value */
	while ( ( u8_l_recData != UART_U8_ENTER_CHAR ) && ( u8_l_index < 19 ) )
	{
		UART_receiveByteBlock( &u8_l_recData );
		u8_l_cardPAN[u8_l_index] = u8_l_recData;
		u8_l_index++;
	}
	
	u8_l_cardPAN[u8_l_index] = '\0';
	
	UART_transmitString( ( u8 * ) "\r" );
	
	/* Loop: Until user enters two identical numeric PINs, and don't exceed 4 digits */
	while ( u8_l_equalPINsFlag == APP_U8_FLAG_DOWN )
	{
		memset( u8_l_newPIN, '\0', 10 );
		memset( u8_l_confirmedPIN, '\0', 10 );
		
		/* Update Flag */
		u8_l_charFlag == APP_U8_FLAG_DOWN;
		u8_l_equalPINsFlag = APP_U8_FLAG_UP;
		
		/* Step 3: Display "Please Enter New PIN" on terminal */
		UART_transmitString( ( u8 * ) "Please Enter New PIN: " );
		
		u8_l_recData = 0;
		u8_l_index = 0;
		
		/* Step 4: Receive New PIN value */
		while ( u8_l_recData != UART_U8_ENTER_CHAR )
		{
			UART_receiveByteBlock( &u8_l_recData );
			u8_l_newPIN[u8_l_index] = u8_l_recData;
			u8_l_index++;
		}
		
		u8_l_newPIN[u8_l_index - 1] = '\0';
		
		/* Step 5: Display "Please Confirm New PIN" on terminal */
		UART_transmitString( ( u8 * ) "Please Confirm New PIN: " );
		
		u8_l_recData = 0;
		u8_l_index = 0;
		
		/* Step 6: Receive New PIN value */
		while ( u8_l_recData != UART_U8_ENTER_CHAR )
		{
			UART_receiveByteBlock( &u8_l_recData );
			u8_l_confirmedPIN[u8_l_index] = u8_l_recData;
			u8_l_index++;
		}
		
		u8_l_confirmedPIN[u8_l_index - 1] = '\0';
		
		UART_transmitString( ( u8 * ) "\n\r" );
			
		/* Check 1: Two PINs are not identical */
		if ( strcmp( u8_l_newPIN, u8_l_confirmedPIN ) )
		{
			/* Display "Wrong PIN" on terminal */
			UART_transmitString( ( u8 * ) "Wrong PIN [Non Identical]\n\r" );
			u8_l_equalPINsFlag = APP_U8_FLAG_DOWN;
			continue;
		}
			
		u8_l_index = 0;
			
		/* Loop: Until the end of PIN */
		while ( u8_l_newPIN[u8_l_index] != '\0' )
		{
			if ( u8_l_newPIN[u8_l_index] < 48 || u8_l_newPIN[u8_l_index] > 57 )
			{
				u8_l_charFlag = APP_U8_FLAG_UP;
				break;
			}
			
			u8_l_index++;
		}
			
		/* Check 2: PIN is a non numeric */
		if ( u8_l_charFlag == APP_U8_FLAG_UP )
		{
			/* Display "Wrong PIN" on terminal */
			UART_transmitString( ( u8 * ) "Wrong PIN [Non Numeric]\n\r" );
			u8_l_equalPINsFlag = APP_U8_FLAG_DOWN;
			continue;
		}
			
		/* Check 3: PIN exceeds 4 digits */
		if ( u8_l_index < 4 || u8_l_index > 4 )
		{
			/* Display "Wrong PIN" on terminal */
			UART_transmitString( ( u8 * ) "Wrong PIN [Not 4 Digits]\n\r" );
			u8_l_equalPINsFlag = APP_U8_FLAG_DOWN;
			continue;
		}
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_userMode
 Input: void
 Output: void
 Description: Function to start program.
*/
void APP_userMode	   ( void )
{
	
}

/*******************************************************************************************************************************************************************/