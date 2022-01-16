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

#define REGISTER_SIZE 8

#define FALSE 0
#define TRUE 1

/**************************************************************************************\
* Custom datatypes
\**************************************************************************************/
typedef enum 
{
    LOW_LEVEL_GENERATE = 0,
    ANY_LEVEL_GENERATE = 1,
    FALLING_EDGE_GENERATE = 2,
    RISING_EDGE_GENERATE = 3
} ExternalInterruptSenseControl;

typedef enum
{
    EXT_INT0,
    EXT_INT1
} ExternalInterruptName;

typedef enum
{
	PCINT0_VAL = 0,
	PCINT1_VAL = 1,
	PCINT2_VAL = 2,
	PCINT3_VAL = 3,
	PCINT4_VAL = 4,
	PCINT5_VAL = 5,
	PCINT6_VAL = 6,
	PCINT7_VAL = 7,
	PCINT8_VAL = 8, //0
	PCINT9_VAL = 9,
	PCINT10_VAL = 10,
	PCINT11_VAL = 11,
	PCINT12_VAL = 12,
	PCINT13_VAL = 13,
	PCINT14_VAL = 14,
	PCINT16_VAL = 16, //0
	PCINT17_VAL = 17,
	PCINT18_VAL = 18,
	PCINT19_VAL = 19,
	PCINT20_VAL = 20,
	PCINT21_VAL = 21,
	PCINT22_VAL = 22,
	PCINT23_VAL = 23,
} PCINT_MAP;

typedef enum
{
	INPUT,
	INPUT_PULLUP,
	OUTPUT	
}PinMode;

typedef enum
{
	LOW = 0,
	HIGH = 1
}PinState;

/**************************************************************************************\
* Global macros
\**************************************************************************************/
/**
 * @brief Setting pin as input pullup
 */
#define gpio_set_pin_inputPullup(dirReg, portReg, pinNum) ({dirReg &= ~(1 << pinNum); portReg |= (1 << pinNum);})

/**
 * @brief Setting pin as input
 */
#define gpio_set_pin_input(dirReg, portReg, pinNum) ({dirReg &= ~(1 << pinNum); portReg &= ~(1 << pinNum);})

/**
 * @brief Setting pin as output
 */
#define gpio_set_pin_output(portReg, pinNum) (portReg |= (1 << pinNum))

/**
 * @brief Setting pin value as 1
 */
#define gpio_set_bit(portReg, pinNum) (portReg |= (1 << pinNum))

/**
 * @brief Setting pin value as 0
 */
#define gpio_reset_bit(portReg, pinNum) (portReg &= ~(1 << pinNum))

/**
 * @brief Changeing value to opposed
 */
#define gpio_toogle_bit(portReg, pinNum) (portReg ^= (1 << pinNum))

/**
 * @brief Check if pin value set
 */
#define gpio_is_bit_set(portReg, pinNum) (portReg & (1 << pinNum))


/**************************************************************************************\
* Prototypes
\**************************************************************************************/
void gpio_set_pin_mode(PCINT_MAP pin, PinMode mode);
void gpio_set_pin_state(PCINT_MAP pin, PinState mode);
void gpio_set_external_interrupt(uint8_t enable, ExternalInterruptName externalIntterupt,
                                    ExternalInterruptSenseControl senseControl, void (*callback)());

void gpio_set_interrupt(uint8_t enable, PCINT_MAP pcintNumber, void (*callback)());

void gpio_register_int0_callback(void (*callback)());
void gpio_deregister_int0_callback(void);
void gpio_register_int1_callback(void (*callback)());
void gpio_deregister_int1_callback(void);
void gpio_register_pcint0_callback(void (*callback)());
void gpio_deregister_pcint0_callback(void);
void gpio_register_pcint1_callback(void (*callback)());
void gpio_deregister_pcint1_callback(void);
void gpio_register_pcint2_callback(void (*callback)());
void gpio_deregister_pcint2_callback(void);

#endif
