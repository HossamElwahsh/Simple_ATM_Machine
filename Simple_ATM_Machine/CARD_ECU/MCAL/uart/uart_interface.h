/*
 * uart_interface.h
 *
 *     Created on: Aug 5, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Universal Asynchronous Receiver Transmitter (UART) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* UART Includes */

/* LIB */
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

/*******************************************************************************************************************************************************************/
/* UART Macros */

/* UART Interruption Modes */
#define UART_U8_POLLING_MODE      0
#define UART_U8_RXC_INT_MODE      1
#define UART_U8_UDRE_INT_MODE     2

/*******************************************************************************************************************************************************************/
/* UART Functions' prototypes */

vd UART_vdInitialization ( void );

u8 UART_u8ReceiveByte    ( u8 u8_a_interruptionMode, u8 *pu8_a_returnedReceiveByte );
u8 UART_u8TransmitByte   ( u8 u8_a_interruptionMode, u8 u8_a_transmitByte );

u8 UART_transmitString   ( u8 *pu8_a_string );

u8 UART_u8RXCSetCallBack ( void ( *vpf_a_RXCInterruptAction ) ( void ) );
u8 UART_u8UDRESetCallBack( void ( *vpf_a_UDREInterruptAction ) ( void ) );
u8 UART_u8TXCSetCallBack ( void ( *vpf_a_TXCInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* UART_INTERFACE_H_ */