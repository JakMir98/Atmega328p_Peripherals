/*
 * gpio.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 

#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief All GPIO initialization
 */
void GPIO_init(void);

/**
 * @brief Setting pin as input pullup
 */
void GPIO_set_pin_inputPullup(uint8_t directionRegister, uint8_t portRegister, uint8_t pinNumber);

/**
 * @brief Setting pin as output
 */
void GPIO_set_pin_output(uint8_t portRegister, uint8_t pinNumber);

/**
 * @brief Setting pin value as 1
 */
void GPIO_set_bit(uint8_t portRegister, uint8_t pinNumber);

/**
 * @brief Setting pin value as 0
 */
void GPIO_reset_bit(uint8_t portRegister, uint8_t pinNumber);

/**
 * @brief Changeing value to opposed
 */
void GPIO_toogle_bit(uint8_t portRegister, uint8_t pinNumber);

/**
 * @brief Check if pin value set
 */
uint8_t GPIO_is_bit_set(uint8_t portRegister, uint8_t pinNumber);

#endif
