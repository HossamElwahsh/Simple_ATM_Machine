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
ST_accountsDB_t  accountsDB[255] =							    /* Visa */                                  /* MasterCard */
								    /* Balance   |  State |        PAN        */  /* Balance    |  State |        PAN       */
							      { { 12000.0f   , BLOCKED, "4728459258966333" }, { 68600.3f   , RUNNING, "5183150660610263" },
									{ 5805.5f    , RUNNING, "4946084897338284" }, { 5000.3f    , RUNNING, "5400829062340903" },
									{ 90360.12f  , RUNNING, "4728451059691228" }, { 1800000.0f , RUNNING, "5191786640828580" },
									{ 16800.58f  , RUNNING, "4573762093153876" }, { 40800.0f   , RUNNING, "5367052744350494" },
									{ 520.9f     , RUNNING, "4127856791257426" }, { 18900.45f  , RUNNING, "5248692364161088" },
									{ 6900.33f   , RUNNING, "4946099660091878" }, { 1047751.0f , RUNNING, "5419558003040483" },
									{ 200000.0f  , RUNNING, "4834699064563433" }, { 3026239.0f , RUNNING, "5116136307216426" },
									{ 5000000.0f , RUNNING, "4946069587908256" }, { 9362076.0f , RUNNING, "5335847432506029" },
									{ 25600.0f   , RUNNING, "4946085117749481" }, { 10662670.0f, RUNNING, "5424438206113309" },
									{ 895000.0f  , RUNNING, "4946099683908835" }, { 1824.0f    , RUNNING, "5264166325336492" } };
/* Global variables */
// Current App State
u8 u8_g_appState = APP_STATE_LAUNCH;
u8 u8_g_bytesCountToRead = 0; // todo remove ?


void APP_initialization(void) {
	
	/** MCAL Initialization */
	// Init and enable external Interrupt
	EXI_enablePIE(MASTER_REQ_RECEIVE_INT, MASTER_REQ_RECEIVE_SENSE);
    EXI_intSetCallBack(MASTER_REQ_RECEIVE_INT,APP_trigger);

    SPI_init();  // Init SPI
    TIMER_timer0NormalModeInit(DISABLED); // Init timer0

    /** HAL Initialization */
    BUZZER_init();  // Init Buzzer
    KPD_initKPD();  // Init Keypad
    LCD_init();     // Init LCD
	LCD_clear();    // Clear LCD's display

    APP_switchState(u8_g_appState); // switch to entry point state
}


void APP_startProgram(void) {
    while(1)
    {
        switch (u8_g_appState) {
            case APP_STATE_TEST:
                LCD_sendString((u8 *)"STARTING...");
                LCD_setCursor(LCD_LINE1, LCD_COL0);

                LCD_sendString((u8 *) "Sending: ");

                // ss enable
                DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_LOW);
                u8 count = 0;
                char buffer[5];
                while(1)
                {
                    SPI_transceiver(count);
                    sprintf(buffer, "%d", count);
                    LCD_setCursor(LCD_LINE1, LCD_COL10);
                    LCD_sendString((u8 *) buffer);
                    count++;
                    TIMER_delay_ms(1000);
                    if(count == 250) count = 0;
                }
                break;
            case APP_STATE_LAUNCH:
                // no more actions waiting for interrupt signal from CARD ECU
                break;
            case APP_STATE_INSERT_PIN:
                // todo 3 trials only, if failed lock and sound Alarm
                LCD_setCursor(LCD_LINE1, LCD_COL6); // first pin digit position
                APP_ACTION_SHOW_CURSOR
                u8 trials = 0;
                u8 currentPin[5];
                while(trials < 3)
                {
                    u8 currentPosition = 0;

                    // Poll keypad
                    u8 u8_l_btn = KPD_U8_KEY_NOT_PRESSED;
                    /* Wait for 4 digits pin input */
                    while(currentPosition < 4)
                    {
                        KPD_getPressedKey( &u8_l_btn );
                        if ( u8_l_btn == KPD_U8_KEY_NOT_PRESSED ) continue;
                        currentPin[currentPosition] = u8_l_btn;
//                        LCD_sendChar( currentPin[currentPosition] ); // todo update with * starts instead
                        LCD_sendChar( '*' ); // todo update with * starts instead
                        currentPosition++;
                    }
                    // verify PIN
                    LCD_clear();
                    LCD_setCursor(LCD_LINE0, LCD_COL1);
                    LCD_sendString((u8 *) "Please wait...");
                    TIMER_delay_ms(1500);
                    // todo wait for long 0 press then SPI verify PIN
                    // if wrong
                    trials++;
                    /*u8 str_l_wrongPinMessage[16];
                    sprintf((char *) str_l_wrongPinMessage, "Wrong PIN (%d/3)", trials);
                    LCD_sendString(str_l_wrongPinMessage);
                    TIMER_delay_ms(700);*/
                    // if OK
                    break;
                }
                APP_ACTION_HIDE_CURSOR
                if(trials < 3) // PIN OK
                {
                    APP_switchState(APP_STATE_TRANSACTING);
                }else{ // Wrong PIN for 3 trials lock the system
                    APP_switchState(APP_STATE_LOCKED);
                }

                break;

            case APP_STATE_TRANSACTING:
                APP_ACTION_SHOW_CURSOR

                LCD_setCursor(LCD_LINE1, LCD_COL4);
                u8 currentPosition = 0;
                // Poll keypad
                u8 Loc_u8BTNValue = KPD_U8_KEY_NOT_PRESSED;

                /* Wait for 6 digits pin input */
                while(currentPosition < 7)
                {
                    KPD_getPressedKey( &Loc_u8BTNValue );
                    if ( Loc_u8BTNValue == KPD_U8_KEY_NOT_PRESSED ) continue;
                    LCD_sendChar( Loc_u8BTNValue );

                    if(currentPosition == 3) {
                        // skip decimal point placeholder on LCD
                        currentPosition += 2;
                        LCD_setCursor(LCD_LINE1, LCD_COL9);
                    }
                    else currentPosition++;

                    if(currentPosition == 7) // repeat from start if reached end of number placeholders
                    {
                        currentPosition = 0;
                        LCD_setCursor(LCD_LINE1, LCD_COL4);
                    }

                    // todo
                }

                APP_ACTION_HIDE_CURSOR
                break;
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
            default:
                // Ignored
                break;
        }
    }
}


/**
 * @brief Used to switch between app states to initialize standard UI elements before main app flow (loop)
 *
 * @param [in]u8_a_state state to set (APP_STATE_RUNNING, APP_STATE_...)
 *
 * @return void
 */
void APP_switchState(u8 u8_a_state){
    LCD_clear();
    switch (u8_a_state) {
        case  APP_STATE_LAUNCH:
            LCD_sendString((u8 *)" Welcome to ATM");    // Display welcome message on LCD for 1 second
            LCD_sendString((u8 *)"\n Hacker  Kermit");  // Display team name
            TIMER_delay_ms(APP_DELAY_WELCOME_MSG);
            LCD_clear();
            LCD_sendString((u8 *) "  Insert Card");     // Display Insert card message and wait
            break;
        case APP_STATE_INSERT_PIN:
            LCD_setCursor(LCD_LINE0, LCD_COL1);  // Center of first line for the next msg
            LCD_sendString((u8 *) "Enter Your PIN");    // Display "Enter Your PIN" message and wait
            LCD_setCursor(LCD_LINE1, LCD_COL6);  // Center of second line for the next msg
            LCD_sendString((u8 *) "____");              // Display Placeholders for PIN
            break;
        case APP_STATE_TRANSACTING:
            LCD_setCursor(LCD_LINE0, LCD_COL2);  // Center of first line for the next msg
            LCD_sendString((u8 *) "Enter Amount");      // Display "Enter Amount" message and wait
            LCD_setCursor(LCD_LINE1, LCD_COL4);  // Center of first line for the next msg
            LCD_sendString((u8 *) "0000.00");           // Display Placeholders for Amount

            break;
        case APP_STATE_LOCKED:
            LCD_setCursor(LCD_LINE0, LCD_COL1);
            LCD_sendString((u8 *)"System Locked");
            KPD_disableKPD();   // Disable keypad
            BUZZER_on();        // Alarm ON
        default:
            // ignored
            break;
    }
    u8_g_appState = u8_a_state; // globally set new app state
}

// Ran when an INT0 interrupt is fired / Card inserted
void APP_trigger(void) {
    // receive SPI data
    if(u8_g_appState == APP_STATE_LAUNCH) APP_switchState(APP_STATE_INSERT_PIN);
}