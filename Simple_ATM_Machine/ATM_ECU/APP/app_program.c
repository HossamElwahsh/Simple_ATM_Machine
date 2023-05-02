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
	
	/* MCAL Initialization */
	EXI_enablePIE(MASTER_REQ_RECEIVE_INT, MASTER_REQ_RECEIVE_SENSE);
    EXI_intSetCallBack(MASTER_REQ_RECEIVE_INT,APP_trigger);

	TIMER_timer0NormalModeInit( DISABLED );
	TIMER_timer2NormalModeInit( ENABLED );

	SPI_init();
	
	/* HAL Initialization */
	LCD_init();
	KPD_initKPD();
	
	LCD_clear();
	// Jump to 1st line Center
	LCD_setCursor(0,4);
	// Show welcome Message
	LCD_sendString((u8 *)"Welcome\n Hacker  Kermit");
	TIMER_delay_ms(500);
	LCD_clear();

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
void APP_startProgram  (void) {

	u8 Loc_u8BTNValue = KPD_U8_KEY_NOT_PRESSED;
		
	/* Toggle Forever */
	while(1)
	{
		KPD_getPressedKey( &Loc_u8BTNValue );
			
		if ( Loc_u8BTNValue != KPD_U8_KEY_NOT_PRESSED )
		{
			LCD_sendChar( Loc_u8BTNValue );
		}
	}
}

void APP_trigger       (void) {
    // receive SPI data

}