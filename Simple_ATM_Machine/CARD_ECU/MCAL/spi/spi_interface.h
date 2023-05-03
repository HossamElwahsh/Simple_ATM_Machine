/*
 * spi_interface.h
 *
 * Created: 1/5/2023 5:18:17 PM
 *  Author: Hossam
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "spi_config.h"

/**
 * Initializes SPI protocol
 */
void SPI_init();

/**
 * Receive and Transmit one byte via SPI
 *
 * @param [in]u8_a_byte byte to send
 *
 * @return Received byte
 */
u8 SPI_transceiver(u8 u8Ptr_a_byte);

#endif /* SPI_INTERFACE_H_ */