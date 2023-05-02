/*
 * app_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "app_interface.h"

/* Declaration and Initialization */
/* Accounts Database */
//ST_accountsDB_t  accountsDB[255] =							    /* Visa */                                  /* MasterCard */
//								    /* Balance   |  State |        PAN        */  /* Balance    |  State |        PAN       */
//							      { { 12000.0f   , BLOCKED, "4728459258966333" }, { 68600.3f   , RUNNING, "5183150660610263" },
//									{ 5805.5f    , RUNNING, "4946084897338284" }, { 5000.3f    , RUNNING, "5400829062340903" },
//									{ 90360.12f  , RUNNING, "4728451059691228" }, { 1800000.0f , RUNNING, "5191786640828580" },
//									{ 16800.58f  , RUNNING, "4573762093153876" }, { 40800.0f   , RUNNING, "5367052744350494" },
//									{ 520.9f     , RUNNING, "4127856791257426" }, { 18900.45f  , RUNNING, "5248692364161088" },
//									{ 6900.33f   , RUNNING, "4946099660091878" }, { 1047751.0f , RUNNING, "5419558003040483" },
//									{ 200000.0f  , RUNNING, "4834699064563433" }, { 3026239.0f , RUNNING, "5116136307216426" },
//									{ 5000000.0f , RUNNING, "4946069587908256" }, { 9362076.0f , RUNNING, "5335847432506029" },
//									{ 25600.0f   , RUNNING, "4946085117749481" }, { 10662670.0f, RUNNING, "5424438206113309" },
//									{ 895000.0f  , RUNNING, "4946099683908835" }, { 1824.0f    , RUNNING, "5264166325336492" } };
/* Global variables */

/**
 *
 */
void APP_initialization(void) {
	
	/* MCAL Initialization */
	GLI_enableGIE();
	
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

//  u8 data;
//  SPI_receive(&data);
//  u8 test = 1;

// 	SPI_send('H');
// 	SPI_send('O');
// 	SPI_send('S');
// 	SPI_send('S');
// 	SPI_send('A');
// 	SPI_send('M');

//  while(1)
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

void APP_trigger(void) {
    // receive SPI data

}