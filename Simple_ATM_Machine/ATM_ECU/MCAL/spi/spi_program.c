/*
 * spi_program.c
 *
 * Created: 1/5/2023 5:18:05 PM
 *  Author: Hossam
 */ 

#include "spi_interface.h"
#include "spi_private.h"

/*
 * Initializes SPI protocol
 */
void SPI_init()
{
    /* Set SPI data order */
    WRITE_BIT(SPI_U8_SPCR_REG, SPI_SPCR_DODR_BIT, SPI_DORD);

    /* Init SPI Pins */
#if SPI_MODE == SPI_MODE_MASTER
    /* Init SPI port pins */
    DIO_init(SPI_MISO, SPI_PORT, DIO_IN);
    DIO_portInit(SPI_PORT, DIO_PORT_OUT, SPI_MASTER_OUT_PINS);

    /* SET slave select pin to high */
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_HIGH);

    /* Init SPI Clock Speed in master only */
    //region Init Clock Speed
#if SPI_CLOCK == SPI_CLOCK_FOSC_4
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_16
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_64
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_128
    // disable speed doubler
    CLR_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_2
    // enable speed doubler
    SET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_8
    // enable speed doubler
    SET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#elif SPI_CLOCK == SPI_CLOCK_FOSC_32
    // enable speed doubler
    SET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPI2X_BIT);

    // set corresponding clock selection bits
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR0_BIT);
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPR1_BIT);
#endif
    //endregion

    /* SET SPI mode to master */
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_MSTR_BIT);

    /* SPI Enable */
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPE_BIT);

#elif SPI_MODE == SPI_MODE_SLAVE
    /* Init SPI port pins */
    DIO_portInit(SPI_PORT, DIO_PORT_IN, SPI_SLAVE_IN_PINS);
    DIO_init(SPI_MISO, SPI_PORT, DIO_OUT);

    /* Init SPI slave GPIO Notify pin as OUTPUT */
    DIO_init(SPI_SLAVE_SEND_NOTIFY_PIN, SPI_PORT, DIO_OUT);

    /* SET SPI mode to slave */
    CLR_BIT(SPI_U8_SPCR_REG, SPI_SPCR_MSTR_BIT);

    /* SPI Enable */
    SET_BIT(SPI_U8_SPCR_REG, SPI_SPCR_SPE_BIT);
#endif

}

/**
 * Receive one byte via SPI
 *
 * @param [out]u8Ptr_a_byte ptr to variable to put received data in
 *
 * @return STD_OK if receive success, STD_NOK if receive fail
 */
u8 SPI_receive(u8 * u8Ptr_a_byte)
{
#if SPI_MODE == SPI_MODE_MASTER
    /* Write dummy data in SPDR */
    SPI_U8_SPDR_REG = U8_DUMMY_VAL;

    /* wait for reception to complete */
    while(!GET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPIF_BIT));

    /* Read data and flush */
    *u8Ptr_a_byte = SPI_U8_SPDR_REG;
    return STD_OK;

#elif SPI_MODE == SPI_MODE_SLAVE

    SPI_U8_SPDR_REG = U8_DUMMY_VAL;

    while(!GET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPIF_BIT));

    *u8Ptr_a_byte = SPI_U8_SPDR_REG;
    return STD_OK;
#endif
}

/**
 * Send one byte via SPI
 *
 * @param [in]u8_a_byte byte to send
 *
 * @return STD_OK if send success, STD_NOK if send fail
 */
u8 SPI_send(u8 u8_a_byte)
{
#if SPI_MODE == SPI_MODE_MASTER

    /* Pull SS pin to low to start SPI */
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_LOW);

    /* write data to SPI data register */
    SPI_U8_SPDR_REG = u8_a_byte;

    /* Block till transmission is complete */
    while(!GET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPIF_BIT));

    /* flush received noise data */
    u8 u8_l_flushBuffer = SPI_U8_SPDR_REG;

    /* Bring SS high again to stop SPI */
    DIO_write(SPI_SS, SPI_PORT, DIO_U8_PIN_HIGH);

    return STD_OK;

#elif SPI_MODE == SPI_MODE_SLAVE

    // set byte to be sent
    SPI_U8_SPDR_REG = u8_a_byte;

    // Notify master to receive data (falling edge)
    DIO_write(SPI_SLAVE_SEND_NOTIFY_PIN, SPI_PORT, DIO_U8_PIN_HIGH);
    DIO_write(SPI_SLAVE_SEND_NOTIFY_PIN, SPI_PORT, DIO_U8_PIN_LOW);

    // wait for transmission to finish
    while(!GET_BIT(SPI_U8_SPSR_REG, SPI_SPSR_SPIF_BIT));

    // flush data
    u8 u8_l_flush = SPI_U8_SPDR_REG;

    return STD_OK;
#endif

}