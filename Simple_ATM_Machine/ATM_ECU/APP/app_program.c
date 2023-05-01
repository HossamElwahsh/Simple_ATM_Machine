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
void APP_initialization( void )
{
	TIMER_timer0NormalModeInit( DISABLED );
	TIMER_timer2NormalModeInit( ENABLED );
	
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
}


/**
 *
 */
void APP_startProgram  ( void )
{
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
