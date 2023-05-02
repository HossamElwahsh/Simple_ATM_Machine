/*
 * app_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hossam Elwahsh - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
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
u8 u8_g_appState = APP_STATE_RUNNING;
u8 u8_g_bytesCountToRead = 0;

/**
 *
 */
void APP_initialization(void) {
	
	/* MCAL Initialization */
	
	EXI_enablePIE(MASTER_REQ_RECEIVE_INT, MASTER_REQ_RECEIVE_SENSE);
    EXI_intSetCallBack(MASTER_REQ_RECEIVE_INT,APP_trigger);
    SPI_init();
    TIMER_timer0NormalModeInit(DISABLED);

    LCD_init();
    BUZZER_init();
	LCD_clear();
    LCD_sendString((u8 *)"STARTING...");
    LCD_setCursor(LCD_LINE1, LCD_COL0);

    LCD_sendString((u8 *) "Sending: ");

    // ss enable
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_LOW);
    u8 count = 0;
    char buffer[5];
    while(1)
    {
        SPI_send(count);
        sprintf(buffer, "%d", count);
        LCD_setCursor(LCD_LINE1, LCD_COL10);
        LCD_sendString((u8 *) buffer);
        count++;
        TIMER_delay_ms(1000);
    }


//    SPI_send('H');
}


void APP_startProgram(void) {
    while(1)
    {
        switch (u8_g_appState) {
            case APP_STATE_RUNNING:
//                SPI_send(12);
                BUZZER_on();
                TIMER_delay_ms(500);
                BUZZER_off();
                TIMER_delay_ms(500);
//                SPI_send(2);
//                SPI_send(3);
//                SPI_send(4);
//                SPI_send(5);
//                SPI_send('H'); // 0x48

                if(u8_g_bytesCountToRead > 0) u8_g_appState = APP_STATE_RECEIVING;
                break;
            case APP_STATE_RECEIVING: {
                BUZZER_on();
                while(u8_g_bytesCountToRead > 0)
                {
                    u8 rec = SPI_send('H');
                    LCD_sendChar(rec);
                    TIMER_delay_ms(1500);
//                    u8_g_bytesCountToRead--;
                }
                u8_g_appState = APP_STATE_RUNNING;
                break;
            }
        }
    }
}

void APP_trigger(void) {
    // receive SPI data
    u8_g_bytesCountToRead++;
    if(u8_g_bytesCountToRead > 250) u8_g_bytesCountToRead = 1;
//    u8_g_appState = APP_STATE_RECEIVING;
}