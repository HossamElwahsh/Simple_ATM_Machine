


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#define EEPROM_ERROR 0
#define EEPROM_SUCCESS 1

#include "../../MCAL/twi/twi.h"
#include "../../MCAL/timer/timer_interface.h"
#include "../../LIB/bit_math.h"
#include "../../LIB/std.h"

void EEPROM_Init(void);
u8 EEPROM_Write_Byte(u16 u16addr,u8 u8data);
u8 EEPROM_Read_Byte(u16 u16addr,u8 *u8data);
u8 * EEPROM_Read_Array(u16 address);
u8 EEPROM_Write_Array(u16 u16addr, u8 *pstr);
 
#endif /* EXTERNAL_EEPROM_H_ */
