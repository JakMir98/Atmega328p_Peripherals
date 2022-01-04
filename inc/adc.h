/*
 * adc.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

const int ADC_SAMPLES = 5;
/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief Analog to digital converter initialization
 */
void ADC_init();

/**
 * @brief Read ADC value from selected channel
 *
 * @param channel of adc
 */
uint16_t ADC_read(uint8_t ADCchannel);

/**
 * @brief Read ADC few values from selected channel and avr them
 *
 * @param channel of adc
 */
uint16_t ADC_average_read(uint8_t ADCchannel);

#endif /* ADC_H_ */
