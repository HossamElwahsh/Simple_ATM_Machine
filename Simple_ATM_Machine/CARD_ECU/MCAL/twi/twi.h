/*
 * twi.h
 *
 * Created: 5/1/2023 4:24:00 PM
 *  Author: Mahmoud Mowafey
 */ 


#ifndef TWI_H_
#define TWI_H_


#include "../../LIB/bit_math.h"
#include "../../LIB/std.h"
#include "twi_cfg.h"


/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(u8 data);
u8 TWI_Read_With_ACK(void); //read with send Ack
u8 TWI_Read_With_NACK(void); //read without send Ack
u8 TWI_Get_Status(void);


#endif /* TWI_H_ */