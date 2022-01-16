/*
 * spi.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 
#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************\
* Private constants
\**************************************************************************************/

#define DATA_REGISTER_SPI DDRB

#define MOSI_PIN PINB3
#define SCK_PIN PINB5
#define MISO_PIN PINB4
#define SS_PIN PINB2

/**************************************************************************************\
* Custom datatypes
\**************************************************************************************/
typedef enum
{
    MSB_FIRST = 0,
    LSB_FIRST = 1
} SpiDataOrder;

typedef enum
{
    LEADING_EDGE_RISING = 0,
    LEADING_EDGE_FALLING = 1
} SpiClockPolarity;

typedef enum
{
    LEADING_EDGE_SAMPLE = 0,
    LEADING_EDGE_SETUP = 1
} SpiClockPhase;

typedef enum
{
    FOSC_DIVIDED_BY_4 = 0,
    FOSC_DIVIDED_BY_16 = 1,
    FOSC_DIVIDED_BY_64 = 2,
    FOSC_DIVIDED_BY_128 = 3
} SpiClkOcilatorRelation;

/**************************************************************************************\
* Prototypes
\**************************************************************************************/
void spi_enable(void);
void spi_disable(void);
void spi_setup_as_master(void);
void spi_interrupt_enable(uint8_t enable);
void spi_register_callback(void (*callback)());
void spi_deregister_callback(void);
void spi_set_data_order(SpiDataOrder order);
void spi_set_clock_polarity(SpiClockPolarity clockPolarity);
void spi_set_clock_phase(SpiClockPhase clockPhase);
void spi_set_clk_oscilattor_relation(SpiClkOcilatorRelation clkRelation, uint8_t doubleSpiSpeed);

/**
 * @brief Init SPI as master
 */
void spi_master_default_init(void);
void spi_master_init(uint8_t interruptEnable, void (*callback)(), SpiDataOrder order, 
                        SpiClockPolarity clockPolarity, SpiClockPhase clockPhase,
                        SpiClkOcilatorRelation clkRelation, uint8_t doubleSpiSpeed);

/**
 * @brief Send data via SPI as master
 */
void spi_master_transmit(char cData);

/**
 * @brief Init SPI as slave
 */
void spi_slave_default_init(void);

/**
 * @brief Receive data via SPI as slave
 */
char spi_slave_receive(void);


#endif /* SPI_H_ */
