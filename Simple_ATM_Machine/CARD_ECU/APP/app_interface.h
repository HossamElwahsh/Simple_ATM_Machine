/*
 * app_interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/HossamElwahsh/Simple_ATM_Machine.git
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */

/* LIB */
#include "../LIB/std.h"
#include "../LIB/bit_math.h"

/* MCAL */
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/timer/timer_interface.h"
//#include "../MCAL/i2c/i2c_interface.h"
#include "../MCAL/spi/spi_interface.h"
#include "../MCAL/uart/uart_interface.h"

/* HAL */
//#include "../HAL/eeprom/eeprom_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP Modes */
#define APP_U8_PROG_MODE	0
#define APP_U8_USER_MODE	1

/* APP Flag States */
#define APP_U8_FLAG_DOWN	0
#define APP_U8_FLAG_UP		1

/* APP Actions */

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

void APP_initialization( void );
void APP_startProgram  ( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */