/*
 * twi.c
 *
 * Created: 5/1/2023 4:23:43 PM
 *  Author: Mahmoud Mowafey
 */ 
#include "twi.h"
void TWI_init(void)
{
	
	//TWI_U8_TWBR_REG = BITRATE(TWI_U8_TWSR_REG);
	TWI_U8_TWBR_REG = 0x02;
	TWI_U8_TWSR_REG = 0x00;
}

u8 TWI_start(void)
{
    /*
     * Clear the TWINT flag before sending the start bit TWINT=1
     * send the start bit by TWSTA=1
     * Enable TWI Module TWEN=1
    */
    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(!(TWI_U8_TWCR_REG & (1<<TWINT)));
    if( (TWI_U8_TWSR_REG & 0xF8) != START_STATE )
	{
            return START_NOT_SENT;
	}
    else
	{
            return EVENT_OK;
	}
}

u8 TWI_repeatedStart(void)
{
    /*
     * Clear the TWINT flag before sending the start bit TWINT=1
     * send the start bit by TWSTA=1
     * Enable TWI Module TWEN=1
    */
    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(!(TWI_U8_TWCR_REG & (1<<TWINT)));
    if( (TWI_U8_TWSR_REG & 0xF8) != REPEATED_START_STATE )
       return REPEATED_START_NOT_SENT;
    else
       return EVENT_OK;
}

u8 TWI_addressSelect(u8 u8_l_address, u8 u8_l_readWrite)
{
    u8 u8_l_state ;
    if( u8_l_readWrite == WRITE )
    {
        TWI_U8_TWDR_REG = u8_l_address + 0;
    }
    else if( u8_l_readWrite == READ )
    {
        TWI_U8_TWDR_REG = u8_l_address + 1;
    }
    else
    {

    }

    TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWEN);
    while(!(TWI_U8_TWCR_REG & (1<<TWINT)));
    u8_l_state = TWI_getStatus();
    if( u8_l_state == SLAVE_W_ACK_STATE)
    {
        return SLAVE_W_ACK_SENT;
    }
    else if( u8_l_state ==  SLAVE_W_NACK_STATE)
    {
        return SLAVE_W_NACK_SENT;
    }
    if( u8_l_state == SLAVE_R_ACK_STATE)
    {
        return SLAVE_R_ACK_SENT;
    }
    else if( u8_l_state ==  SLAVE_R_NACK_STATE)
    {
        return SLAVE_R_NACK_SENT;
    }
    else
    {
        return SLAVE_RW_FAILED;
    }
}

u8 TWI_dataEvent(u8 *u8_l_data, u8 u8_l_readWrite, u8 u8_l_ack)
{
    u8 u8_l_state ;
    if( u8_l_readWrite == WRITE )
    {
        TWI_U8_TWDR_REG = *u8_l_data;
        TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWEN);
        while(!(TWI_U8_TWCR_REG & (1<<TWINT)));
        u8_l_state = TWI_U8_TWSR_REG & 0xF8;
        if( u8_l_state == DATA_WRITE_ACK_STATE)
        {
            return DATA_WRITE_ACK_SENT;
        }
        else if( u8_l_state ==  DATA_WRITE_NACK_STATE)
        {
            return DATA_WRITE_NACK_SENT;
        }
        else
        {
            return DATA_WRITE_FAILED;
        }
    }
    else if( u8_l_readWrite == READ )
    {
        if( u8_l_ack == ACK )
        {
            TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        }
        else if( u8_l_ack == NACK  )
        {
            TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWEN);
        }
        while(!(TWI_U8_TWCR_REG & (1<<TWINT)));
		*u8_l_data = TWI_U8_TWDR_REG;
        u8_l_state = TWI_U8_TWSR_REG & 0xF8;
        if( u8_l_state == DATA_READ_ACK_STATE)
        {
            return DATA_READ_ACK_SENT;
        }
        else if( u8_l_state ==  DATA_READ_NACK_STATE)
        {
            return DATA_READ_NACK_SENT;
        }
        else
        {
            return DATA_READ_FAILED;
        }
    }
}

void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
   TWI_U8_TWCR_REG = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
  // while(!(TWI_U8_TWCR_REG & (1<<TWSTO)));
}

u8 TWI_getStatus(void)
{
    u8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits)
	 * TWI_U8_TWSR_REG & 0b11111000, to remove the prescaler bits and the reserved bit.
	 */
    status = (TWI_U8_TWSR_REG & 0xF8);
    return status;
}
