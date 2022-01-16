/*
 * i2c.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 
#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>
/**************************************************************************************\
* Private constants
\**************************************************************************************/

#define I2C_SCL_PIN PORTC5
#define I2C_SDA_PIN PORTC4

#define I2C_READ_ACK 1
#define I2C_READ_NACK 0

/**************************************************************************************\
* Custom datatypes
\**************************************************************************************/
typedef enum
{
    PRESCALLER_1 = 0,
    PRESCALLER_4 = 1,
    PRESCALLER_16 = 2,
    PRESCALLER_64 = 3
} I2cBitRatePrescaller;

/**************************************************************************************\
* Prototypes
\**************************************************************************************/
void i2c_enable_interrupt(uint8_t enable);
void i2c_register_callback(void (*callback)());
void i2c_deregister_callback(void);
void i2c_set_prescaller(I2cBitRatePrescaller prescaller);

/**
 * @brief I2C Init
 * @param frequency mode 1 = 100KHz, 2 = 250KHz, 3 = 400KHz
 * @param should enable internall pullup -> 1 = true
 */
void i2c_init(uint8_t freqMode, uint8_t pullupEnable);

/**
 * @brief I2C transmit data to slave as master
 */
uint16_t i2c_transmit(uint8_t slave_addr, uint8_t* p_data, uint8_t len, uint8_t repeat_start);

/**
 * @brief I2C receive data from slave 
 */
uint16_t i2c_receive(uint8_t slave_addr, uint8_t* p_data, uint8_t len);

#endif /* I2C_H_ */
