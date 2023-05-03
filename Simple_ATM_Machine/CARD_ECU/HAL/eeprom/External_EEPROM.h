/*
 * External_EEPROM.c
 * Created: 3/5/2023 3:40 AM
 * Author : Mahmoud Mowafey
 *
*/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


#include "../../MCAL/twi/twi.h"
#include "../../MCAL/timer/timer_interface.h"
#include "../../LIB/bit_math.h"
#include "../../LIB/std.h"

typedef enum {
	EEPROM_ERROR,
	EEPROM_SUCCESS
}EN_eepromError_t;
#define BYTE_ADDRESS   0x0001

#ifdef EEPROM_24C256B

#else

#endif // DEBUG


void EEPROM_Init(void);
u8 EEPROM_Write_Byte(u16 u16addr,u8 u8data);
u8 EEPROM_Read_Byte(u16 u16addr,u8 *u8data);
u8 * EEPROM_Read_Array(u16 address);
u8 EEPROM_Write_Array(u16 u16addr, u8 *pstr);
 
#endif /* EXTERNAL_EEPROM_H_ */
