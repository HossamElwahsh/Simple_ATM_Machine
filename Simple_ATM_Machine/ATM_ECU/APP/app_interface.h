/*
 * app_interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/* APP Includes */
/* LIB */
#include "../LIB/std.h"
#include "../LIB/bit_math.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* MCAL */
#include "../MCAL/timer/timer_interface.h"
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/spi/spi_interface.h"
#include "../MCAL/exi/exi_interface.h"

/* HAL */
#include "../HAL/lcd/lcd_interface.h"
#include "../HAL/kpd/kpd_interface.h"
#include "../HAL/buzzer/buzzer.h"

/* APP Macros */
#define APP_ACTION_SHOW_CURSOR LCD_changeCursor(1);
#define APP_ACTION_HIDE_CURSOR LCD_changeCursor(0);

/* APP Delays */
#define APP_DELAY_WELCOME_MSG 1000

/* APP STATES */
#define APP_STATE_LAUNCH        0
#define APP_STATE_RUNNING       1
#define APP_STATE_INSERT_PIN    2
#define APP_STATE_TRANSACTING   3
#define APP_STATE_RECEIVING     20
#define APP_STATE_LOCKED        51
#define APP_STATE_TEST     999

/* APP Buttons */

/* APP Actions */

/* APP Typedefs */
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
    float f32_balance;
    EN_accountState_t en_state;
    u8 u8_primaryAccountNumber[20];
}ST_accountsDB_t;



/* APP Functions' Prototypes */

/**
 *
 */
void APP_initialization(void);

/**
 * @return void.
 */
void APP_startProgram(void);

void APP_switchState(u8 u8_a_state);

void APP_trigger(void);
#endif /* APP_INTERFACE_H_ */