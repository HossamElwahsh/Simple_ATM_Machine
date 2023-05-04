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
#include <string.h>

/* MCAL */
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/timer/timer_interface.h"
#include "../MCAL/twi/twi.h"
#include "../MCAL/spi/spi_interface.h"
#include "../MCAL/uart/uart_interface.h"

/* HAL */
#include "../HAL/eeprom/External_EEPROM.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP Modes */
#define APP_U8_PROG_MODE		0
#define APP_U8_USER_MODE		1

/* APP Flag States */
#define APP_U8_FLAG_DOWN		0
#define APP_U8_FLAG_UP			1

/* APP PAN & PIN Addresses */
#define APP_U16_PAN_ADDRESS		0x0000
#define APP_U16_PIN_ADDRESS		0x002C

/* APP Data (PAN & PIN) in Memory (EEPROM) */
#define APP_U8_DATA_NOT_FOUND	0
#define APP_U8_DATA_FOUND		1

/* APP SPI Commands */
#define APP_CMD_PIN_READY		0xC1
#define APP_CMD_RECV_READY		0xC2
#define APP_CMD_RECV_PIN		0xA0
#define APP_CMD_PIN_WRONG		0xF0
#define APP_CMD_PIN_OK			0xF1

/* APP Typedefs */
typedef enum EN_cardData_t
{
	APP_EN_PAN, APP_EN_PIN
}EN_cardData_t;

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

void APP_initialization   ( void );
void APP_startProgram	  ( void );

u8   APP_checkDataInMemory( void );
void APP_checkUserInput	  ( void );

void APP_programmerMode   ( void );
void APP_userMode	      ( void );

void APP_receiveATMData   ( EN_cardData_t en_a_cardData );

/*******************************************************************************************************************************************************************/

#endif /* APP_INTERFACE_H_ */