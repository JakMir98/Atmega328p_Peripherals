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

const int MOSI_PIN = DDB3;
const int DD_SCK = DDB5;
const int MISO_PIN = DDB4;

/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief Init SPI as master
 */
void SPI_master_init(void);

/**
 * @brief Send data via SPI as master
 */
void SPI_master_transmit(char cData);

/**
 * @brief Init SPI as slave
 */
void SPI_slave_init(void);

/**
 * @brief Receive data via SPI as slave
 */
char SPI_slave_receive(void);


#endif /* SPI_H_ */
