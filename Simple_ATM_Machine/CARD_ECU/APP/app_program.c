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
static u8 u8_gs_appMode = APP_U8_PROG_MODE;

static u8 u8_gs_cardPAN[25] = { 0 };
static u8 u8_gs_newPIN1[10] = { 0 };

/*******************************************************************************************************************************************************************/
/*
 Name: APP_initialization
 Input: void
 Output: void
 Description: Function to initialize Application.
*/
void APP_initialization   ( void )
{
	/* MCAL Initialization */
	DIO_init( DIO_U8_PIN_0, PORT_B, DIO_OUT );
	
	TIMER_timer0NormalModeInit(DISABLED);
	SPI_init();
	UART_initialization();

	/* HAL Initialization */
	EEPROM_init();
	
	
    //u8 count = SPI_U8_DUMMY_VAL;
	//
    //SPI_init();
	//
    //while(1)
    //{
    //    count = SPI_transceiver(count);
    //}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_startProgram
 Input: void
 Output: void
 Description: Function to Start Program.
*/
void APP_startProgram	  ( void )
{
	/* Check 1: There is Data (PAN & PIN) previously stored in Memory (EEPROM) */			
	if ( APP_checkDataInMemory() == APP_U8_DATA_FOUND )
	{
		APP_checkUserInput();
	}
	
	/* Toggle Forever */
	while(1)
	{		
		/* Check 2: Required currentMode */
		switch ( u8_gs_appMode )
		{
			case APP_U8_PROG_MODE:				
				APP_programmerMode();				
				u8_gs_appMode = APP_U8_USER_MODE;				
				break;
				
			case APP_U8_USER_MODE:
				APP_userMode();
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
 Name: APP_checkUserInput
 Input: void
 Output: void
 Description: Function to validate user's input.
*/
void APP_checkUserInput	  ( void )
{
	u8 u8_l_userInput = 0;
	
	/* Loop: Until user enters a valid input */
	while ( ( u8_l_userInput != '1' ) || ( u8_l_userInput != '2' ) )
	{
		/* Step 1: Display "Please press 1 for entering user mode and 2 for programming mode:" on terminal */
		UART_transmitString( ( u8 * ) "Please choose:\r(1) For User Mode\r(2) For Programming Mode\r<< Your Input: " );
		
		/* Step 2: Receive UsrInput value */
		UART_receiveByteBlock( &u8_l_userInput );
		
		/* Check 1.1: Required usrInput */
		switch ( u8_l_userInput )
		{
			case '1': u8_gs_appMode = APP_U8_USER_MODE; break;
			case '2': u8_gs_appMode = APP_U8_PROG_MODE; break;
			default : UART_transmitString( ( u8 * ) ">> Wrong Input, Try Again\r\r" );
		}
	}
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_checkDataInMemory
 Input: void
 Output: u8 DataFlag status Found or not Found
 Description: Function to check for valid Data (PAN & PIN) previously stored in Memory (EEPROM).
*/
u8   APP_checkDataInMemory( void )
{
	u8 u8_l_dataFlag = APP_U8_DATA_FOUND;
		
	u8 *pu8_l_PANCheck = NULL;
	u8 *pu8_l_PINCheck = NULL;
	
	u8 u8_l_index = 0;
	
	/* Step 1: Check for PAN in its address */
	pu8_l_PANCheck = EEPROM_readArray( APP_U16_PAN_ADDRESS );
	
	/* Loop: Until the end of Data */
	while ( *pu8_l_PANCheck != '\0' )
	{
		/* Check 1: Retrieved Data is not a valid Numeric PAN */
		if ( *pu8_l_PANCheck < 48 || *pu8_l_PANCheck > 57 )
		{
			/* Update DataFlag = DATA_NOT_FOUND */
			u8_l_dataFlag = APP_U8_DATA_NOT_FOUND;
			break;
		}
		/* Check 2: Retrieved Data is a valid Numeric PAN */
		else
		{
			/* Store retrieved PAN in CardPAN */
			u8_gs_cardPAN[u8_l_index] = *pu8_l_PANCheck;
		}
		
		pu8_l_PANCheck++;
		u8_l_index++;
	}
	
	u8_l_index--;
	
	/* Check 3: Retrieved Data has not a valid size of PAN */
	if ( u8_l_index < 16 || u8_l_index > 19 )
	{
		/* Update DataFlag = DATA_NOT_FOUND */
		u8_l_dataFlag = APP_U8_DATA_NOT_FOUND;
	}
	
	/* Check 4: DataFlag is updated to DATA_NOT_FOUND, in order not to proceed other checks */
	if ( u8_l_dataFlag == APP_U8_DATA_NOT_FOUND )
	{
		return u8_l_dataFlag;
	}
	
	u8_l_index = 0;
	
	/* Step 2: Check for PIN in its address */
	pu8_l_PINCheck = EEPROM_readArray( APP_U16_PIN_ADDRESS );
	
	/* Loop: Until the end of Data */
	while ( *pu8_l_PINCheck != '\0' )
	{
		/* Check 5: Retrieved Data is not a valid Numeric PIN */
		if ( *pu8_l_PINCheck < 48 || *pu8_l_PINCheck > 57 )
		{
			/* Update DataFlag = DATA_NOT_FOUND */
			u8_l_dataFlag = APP_U8_DATA_NOT_FOUND;
			break;
		}
		/* Check 6: Retrieved Data is a valid Numeric PIN */
		else
		{
			/* Store retrieved PIN in NewPIN1 */
			u8_gs_newPIN1[u8_l_index] = *pu8_l_PINCheck;
		}
		
		pu8_l_PINCheck++;
		u8_l_index++;
	}
	
	u8_l_index--;
	
	/* Check 7: Retrieved Data has not a valid size of PIN */
	if ( u8_l_index < 4 || u8_l_index > 4 )
	{
		/* Update DataFlag = DATA_NOT_FOUND */
		u8_l_dataFlag = APP_U8_DATA_NOT_FOUND;
	}
	
	return u8_l_dataFlag;
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_programmerMode
 Input: void
 Output: void
 Description: Function to implement Programmer Mode flow.
*/
void APP_programmerMode   ( void )
{
	u8 u8_l_validPANFlag  = APP_U8_FLAG_DOWN;
	u8 u8_l_validPINsFlag = APP_U8_FLAG_DOWN;
	u8 u8_l_charFlag = APP_U8_FLAG_DOWN;
	
	u8 u8_l_newPIN2[10] = { 0 };
	
	u8 u8_l_recData = 0;	
	u8 u8_l_index = 0;
	
	/* Loop: Until user enters a valid PAN */
	while ( u8_l_validPANFlag == APP_U8_FLAG_DOWN )
	{
		memset( u8_gs_cardPAN, '\0', 25 );
		
		/* Update Flags */
		u8_l_charFlag = APP_U8_FLAG_DOWN;
		u8_l_validPANFlag = APP_U8_FLAG_UP;
		
		/* Step 1: Display "Please Enter Card PAN" on terminal */
		UART_transmitString( ( u8 * ) "Please Enter Card PAN: " );
		
		u8_l_recData = 0;
		u8_l_index = 0;
		
		/* Step 2: Receive PAN value */
		while ( u8_l_recData != UART_U8_ENTER_CHAR )
		{
			UART_receiveByteBlock( &u8_l_recData );
			u8_gs_cardPAN[u8_l_index] = u8_l_recData;
			u8_l_index++;
		}
		
		u8_gs_cardPAN[u8_l_index - 1] = '\0';
		
		u8_l_index = 0;
		
		/* Loop: Until the end of PAN */
		while ( u8_gs_cardPAN[u8_l_index] != '\0' )
		{
			if ( u8_gs_cardPAN[u8_l_index] < 48 || u8_gs_cardPAN[u8_l_index] > 57 )
			{
				u8_l_charFlag = APP_U8_FLAG_UP;
				break;
			}
			
			u8_l_index++;
		}
				
		/* Check 1: PAN is a non numeric */
		if ( u8_l_charFlag == APP_U8_FLAG_UP )
		{
			/* Display "Wrong PAN" on terminal */
			UART_transmitString( ( u8 * ) ">> Wrong PAN [Non Numeric]\n\r" );
			u8_l_validPANFlag = APP_U8_FLAG_DOWN;
			continue;
		}
				
		/* Check 2: PAN is not in the valid range */
		if ( u8_l_index < 16 || u8_l_index > 19 )
		{
			/* Display "Wrong PAN" on terminal */
			UART_transmitString( ( u8 * ) ">> Wrong PAN [Not in valid range]\n\r" );
			u8_l_validPANFlag = APP_U8_FLAG_DOWN;
			continue;
		}
	}
	
	EEPROM_writeArray( APP_U16_PAN_ADDRESS, u8_gs_cardPAN );
		
	UART_transmitString( ( u8 * ) "\r          <<<<<<<<<<<>>>>>>>>>>          \r\r" );
	
	/* Loop: Until user enters valid PINs */
	while ( u8_l_validPINsFlag == APP_U8_FLAG_DOWN )
	{
		memset( u8_gs_newPIN1, '\0', 10 );
		memset( u8_l_newPIN2, '\0', 10 );
		
		/* Update Flags */
		u8_l_charFlag = APP_U8_FLAG_DOWN;
		u8_l_validPINsFlag = APP_U8_FLAG_UP;
		
		/* Step 3: Display "Please Enter New PIN" on terminal */
		UART_transmitString( ( u8 * ) "Please Enter New PIN: " );
		
		u8_l_recData = 0;
		u8_l_index = 0;
		
		/* Step 4: Receive New PIN value */
		while ( u8_l_recData != UART_U8_ENTER_CHAR )
		{
			UART_receiveByteBlock( &u8_l_recData );
			u8_gs_newPIN1[u8_l_index] = u8_l_recData;
			u8_l_index++;
		}
		
		u8_gs_newPIN1[u8_l_index - 1] = '\0';
		
		/* Step 5: Display "Please Confirm New PIN" on terminal */
		UART_transmitString( ( u8 * ) "Please Confirm New PIN: " );
		
		u8_l_recData = 0;
		u8_l_index = 0;
		
		/* Step 6: Receive New PIN value */
		while ( u8_l_recData != UART_U8_ENTER_CHAR )
		{
			UART_receiveByteBlock( &u8_l_recData );
			u8_l_newPIN2[u8_l_index] = u8_l_recData;
			u8_l_index++;
		}
		
		u8_l_newPIN2[u8_l_index - 1] = '\0';
			
		/* Check 1: Two PINs are not identical */
		if ( strcmp( u8_gs_newPIN1, u8_l_newPIN2 ) )
		{
			/* Display "Wrong PIN" on terminal */
			UART_transmitString( ( u8 * ) ">> Wrong PIN [Non Identical]\n\r\r" );
			u8_l_validPINsFlag = APP_U8_FLAG_DOWN;
			continue;
		}
			
		u8_l_index = 0;
			
		/* Loop: Until the end of PIN */
		while ( u8_gs_newPIN1[u8_l_index] != '\0' )
		{
			if ( u8_gs_newPIN1[u8_l_index] < 48 || u8_gs_newPIN1[u8_l_index] > 57 )
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
			UART_transmitString( ( u8 * ) ">> Wrong PIN [Non Numeric]\n\r\r" );
			u8_l_validPINsFlag = APP_U8_FLAG_DOWN;
			continue;
		}
			
		/* Check 3: PIN exceeds 4 digits */
		if ( u8_l_index < 4 || u8_l_index > 4 )
		{
			/* Display "Wrong PIN" on terminal */
			UART_transmitString( ( u8 * ) ">> Wrong PIN [Not 4 Digits]\n\r\r" );
			u8_l_validPINsFlag = APP_U8_FLAG_DOWN;
			continue;
		}
	}
	
	EEPROM_writeArray( APP_U16_PIN_ADDRESS, u8_gs_newPIN1 );
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_userMode
 Input: void
 Output: void
 Description: Function to implement User Mode flow.
*/
void APP_userMode	      ( void )
{
	APP_receiveATMData( APP_EN_PIN );
	//APP_receiveATMData( APP_EN_PAN );
}

/*******************************************************************************************************************************************************************/
/*
 Name: APP_receiveATMData
 Input: void
 Output: void
 Description: Function to implement User Mode flow.
*/
void APP_receiveATMData   ( EN_cardData_t en_a_cardData )
{
	u8 u8_l_dummyData = 'H';
	u8 u8_l_recPIN[5] = { 0 };
		
	/* Step 1: Send a notification to ATM ECU to receive data (falling edge) */
	DIO_write( DIO_U8_PIN_0, PORT_B, DIO_U8_PIN_HIGH);
	DIO_write( DIO_U8_PIN_0, PORT_B, DIO_U8_PIN_LOW );
		
	/* Step 2: Receive response "PIN_READY" from ATM ECU */
	/* Loop: Until response is received using SPI */
	while ( SPI_transceiver( u8_l_dummyData ) != APP_CMD_PIN_READY );
		
	/* Step 3: Send response "RECV_READY" to ATM ECU */
	SPI_transceiver( APP_CMD_RECV_READY );
	
	u8_l_dummyData = 0xFF;
	
	/* Step 4: Receive PIN from ATM ECU */
	/* Loop: Until PIN is received using SPI */
	for ( u8 u8_l_index = 0; u8_l_index < 4; u8_l_index++ )
	{
		/* Step 5: Send response "RECV_PIN" to ATM ECU */
		SPI_transceiver( APP_CMD_RECV_PIN + u8_l_index );
		/* Step 6: Receive response PIN value byte by byte from ATM ECU */
		u8_l_recPIN[u8_l_index] = SPI_transceiver( u8_l_dummyData );
	}
		
	u8_l_recPIN[4] = '\0';
		
	/* Step 7: Compare PIN from Card ECU with the PIN received from ATM ECU */
	/* Check 1: PINs are Identical */
	if ( !( strcmp( u8_gs_newPIN1, u8_l_recPIN ) ) )
	{
		/* Step 8A: Send response "PIN_OK" to ATM ECU */
		SPI_transceiver( APP_CMD_PIN_OK );
	}
	/* Check 2: PINs are not Identical */
	else
	{
		/* Step 8B: Send response "PIN_WRONG" to ATM ECU */
		SPI_transceiver( APP_CMD_PIN_WRONG );
	}
}

/*******************************************************************************************************************************************************************/