/*
 * twi.h
 *
 * Created: 5/1/2023 4:24:00 PM
 *  Author: Mahmoud Mowafey
 */ 


#ifndef TWI_H_
#define TWI_H_

#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"
#include "twi_cfg.h"

#define WRITE                  0
#define READ                   1

#define ACK                    0
#define NACK                   1

#define EVENT_OK                0
#define START_NOT_SENT          1
#define REPEATED_START_NOT_SENT 2
#define SLAVE_W_ACK_SENT        3
#define SLAVE_W_NACK_SENT       4
#define SLAVE_R_ACK_SENT        5
#define SLAVE_R_NACK_SENT       6
#define SLAVE_RW_FAILED         7
#define DATA_WRITE_ACK_SENT     8
#define DATA_WRITE_NACK_SENT    9
#define DATA_WRITE_FAILED       10
#define DATA_READ_ACK_SENT      11
#define DATA_READ_NACK_SENT     12
#define DATA_READ_FAILED        13


/* I2C Status Bits in the TWSR Register */
#define START_STATE             0x08 // start has been sent
#define REPEATED_START_STATE    0x10 // repeated start
#define SLAVE_W_ACK_STATE       0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define SLAVE_W_NACK_STATE      0x20
#define SLAVE_R_ACK_STATE       0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define SLAVE_R_NACK_STATE      0x48
#define DATA_WRITE_ACK_STATE    0x28 // Master transmit data and ACK has been received from Slave.
#define DATA_WRITE_NACK_STATE   0x30
#define DATA_READ_ACK_STATE     0x50 // Master transmit data and ACK has been received from Slave.
#define DATA_READ_NACK_STATE    0x58

void TWI_init(void); 
u8 TWI_start(void);
u8 TWI_repeatedStart(void);


u8 TWI_addressSelect(u8 u8_l_address, u8 u8_l_readWrite);
u8 TWI_dataEvent(u8 *u8_l_data, u8 u8_l_readWrite, u8 u8_l_ack);
void TWI_stop(void);
u8 TWI_getStatus(void);
#endif /* TWI_H_ */