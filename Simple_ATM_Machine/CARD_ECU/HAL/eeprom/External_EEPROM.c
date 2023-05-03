/*
 * External_EEPROM.c
 * Created: 3/5/2023 3:40 AM
 * Author : Mahmoud Mowafey
 *
*/

#include "External_EEPROM.h"


void EEPROM_Init(void)
{
	TWI_Init(); // just initialize the TWI module inside the MC
}

#ifdef EEPROM_24C16B

u8 EEPROM_Write_Byte(u16 u16addr, u8 u8data)
{
	TWI_Start();
	if (TWI_Get_Status() != TW_START)
		return EEPROM_ERROR;
	
	//write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
	TWI_Write((u8)(0xA0 | ((u16addr & 0x0700)>>7)));
	if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
		return EEPROM_ERROR;
	
	//send the required location address
	TWI_Write((u8)(u16addr));
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
		return EEPROM_ERROR;
	
	//write byte to eeprom
	TWI_Write(u8data);
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
		return EEPROM_ERROR;
	
	TWI_Stop();
	
	return EEPROM_SUCCESS;
}

u8 EEPROM_Read_Byte(u16 u16addr, u8 *u8data)
{
	TWI_Start();
	if (TWI_Get_Status() != TW_START)
		return EEPROM_ERROR;
	
	//write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
	TWI_Write((u8)((0xA0) | ((u16addr & 0x0700)>>7)));
	if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
		return EEPROM_ERROR;
	
	//send the required location address
	TWI_Write((u8)(u16addr));
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
		return EEPROM_ERROR;
	
	//send a repeated start
	TWI_Start();
	if (TWI_Get_Status() != TW_REP_START)
		return EEPROM_ERROR;
	
	//write the device address and so we need to get A8 A9 A10 address bits and R/W=1 (Read)
	TWI_Write((u8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
	if (TWI_Get_Status() != TW_MT_SLA_R_ACK)
		return EEPROM_ERROR;
	
	*u8data = TWI_Read_With_NACK();
	if (TWI_Get_Status() != TW_MR_DATA_NACK)
		return EEPROM_ERROR;
	
	TWI_Stop();
	return EEPROM_SUCCESS;
}


#else

EN_eepromError_t EEPROM_readByte(u16 u16_l_byteAddress, u8* u8_l_byteData)
{
	TWI_start();
	if (TWI_getStatus() != TW_START)
	{
		return EEPROM_ERROR;
	}
	//Send the Device Address and R/W=0 bit
	TWI_write((u8)((MANDATORY_SEQUENCE_256) | ((u16_l_byteAddress & PAGE_MASK_256) >> NEDDED_SHIFT_TIMES_256)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return EEPROM_ERROR;
	}
	//Send the first word ( 7-MSBs)
	TWI_write((u8)(u16_l_byteAddress >> SHIFT_THE_FIRST_BYTE));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//Send the first word ( 8-LSBs)
	TWI_write((u8)(u16_l_byteAddress));
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//write byte to eeprom
	TWI_write(u8_l_byteData);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return EEPROM_ERROR;
	}
	//send a repeated start
	TWI_start();
	if (TWI_getStatus() != TW_REP_START)
	{
		return EEPROM_ERROR;
	}
	//Send the Device Address and R/W=0 bit
	TWI_write((u8)((MANDATORY_SEQUENCE_256) | ((u16_l_byteAddress & PAGE_MASK_256) >> NEDDED_SHIFT_TIMES_256) | 1));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return EEPROM_ERROR;
	}
	//Read the data from the eeprom	with NACK
	*u8_l_byteData = TWI_readWithNAck();
	if (TWI_getStatus() != TW_MR_DATA_NACK)
	{
		return EEPROM_ERROR;
	}

	TWI_stop();
	return EEPROM_SUCCESS;
}

#endif

u8 EEPROM_Write_Array(u16 u16addr, u8 *pstr)
{
	u8 i=0,x=0;
	u16 j = u16addr;
	while(pstr[i] != '\0')
	{
		x = EEPROM_Write_Byte(j++,pstr[i++]);
		TIMER_delay_ms(10);
		if(0==x)
			return EEPROM_ERROR;
	}
	EEPROM_Write_Byte(j,'\0');
	TIMER_delay_ms(10);
	return EEPROM_SUCCESS;
}
u8 * EEPROM_Read_Array(u16 address)
{
	u8 i=0;
	u8 *pstr;
	static u8 arr[20];
	do{
		EEPROM_Read_Byte(address,&arr[i]);
		TIMER_delay_ms(10);
		address++;
		i++;
	}while( ( arr[i-1] != '\0' ) && ( i != 19 ) );
	arr[i] = '\0';
	return arr;
}





u8 decimal_to_hex(u8 val)
{
	u8 msb, lsb, hex;
	msb = val / 10;
	lsb = val % 10;
	hex = ((msb << 4) + lsb);
	return hex;
}