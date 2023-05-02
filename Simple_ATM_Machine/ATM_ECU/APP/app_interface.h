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
#include "../MCAL/gli/gli_interface.h"

/* HAL */
#include "../HAL/lcd/lcd_interface.h"
#include "../HAL/kpd/kpd_interface.h"
#include "../HAL/buzzer/buzzer.h"

/* APP Macros */

/* APP Delays */

/* APP STATES */
#define APP_STATE_RUNNING   0
#define APP_STATE_RECEIVING 1

/* APP Buttons */

/* APP Actions */

/* APP Functions' Prototypes */

/**
 *
 */
void APP_initialization(void);

/**
 * @return void.
 */
void APP_startProgram(void);

void APP_trigger(void);
#endif /* APP_INTERFACE_H_ */