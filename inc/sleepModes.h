/*
 * sleepModes.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 
#ifndef SLEEPMODES_H_
#define SLEEPMODES_H_

#include <avr/sleep.h>
#include <avr/power.h>

/**************************************************************************************\
* Custom datatypes
\**************************************************************************************/
typedef enum
{
    IDLE = 0,
    ADC_NOISE_REDUCTION = 1,
    POWER_DOWN = 2,
    POWER_SAVE = 3,
    STANDBY = 6,
    EXTENDED_STANDBY = 7
} SleepModes;

/**************************************************************************************\
* Prototypes
\**************************************************************************************/
/**
 * @brie Go to sleep
 */
void sleepmodes_go_to_sleep(SleepModes mode, uint8_t adcDisable, uint8_t spiDisable, 
                            uint8_t timer0Disable, uint8_t timer1Disable, uint8_t timer2Disable, 
                            uint8_t i2cDisable, uint8_t usartDisable);

#endif /* SLEEPMODES_H_ */
