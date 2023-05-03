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


#define EEPROM_24C256B

#ifdef EEPROM_24C16B
	#define BYTE_ADDRESS			0x0045
	#define MANDATORY_SEQUENCE	     0xA0
	#define	PAGE_MASK			     0x0700
	#define NEDDED_SHIFT_TIMES	     7
	u8 EEPROM_writeByte(u16 u16_l_byteAddress, u8 u8_l_byteData);
	u8 EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData);
#else
	#define BYTE_ADDRESS			 0x011
	#define MANDATORY_SEQUENCE_256   0xA0   // 10100 
	#define	PAGE_MASK_256			 0x0600
	#define NEDDED_SHIFT_TIMES_256	 7	
	#define SHIFT_THE_FIRST_BYTE	 8	
	u8 EEPROM_writeByte(u16 u16_l_byteAddress, u8 u8_l_byteData);
	u8 EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData);
#endif 

void EEPROM_init(void);
u8 EEPROM_writeByte(u16 u16_l_byteAddress, u8 u8_l_byteData);
u8 EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData);

 
#endif /* EXTERNAL_EEPROM_H_ */
