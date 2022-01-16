/*
 * adcTests.c
 *
 * Created: 14.01.2022 17:32:09
 *  Author: Admin
 */ 

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>

#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\tests.h"
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\adc.h"
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\usart.h"

#include <string.h>
#include <stdio.h>

uint16_t varResistorRead;
uint16_t varResistorAverageRead;

InputChannelSelection input[6] = {ADC0, ADC1, ADC2, ADC3, ADC4, ADC5};

void adc_test(TestType testType)
{
	if(testType == FIRST_TEST)
	{
		adc_default_init();
		usart_init(UBRR_ASYNC_NORMAL);
		usart_send_string("Init usart done");
		
		while(1)
		{
			varResistorRead = adc_single_read(ADC1);
			varResistorAverageRead = adc_average_single_read(ADC1, 25);
			_delay_ms(1000);
			char str[25];
			sprintf(str, "read/avr = %d/%d\n", varResistorRead, varResistorAverageRead);
			usart_send_string(str);
		}
	}
	else if (testType == SECOND_TEST)
	{
		adc_init(AVCC, DIVISION_BY_128);
		adc_
		usart_init(UBRR_ASYNC_NORMAL);
		usart_send_string("Init usart done");
		
		while(1)
		{
			for (int i = 0; i < 6; i++)
			{
				varResistorRead = adc_single_read(input[i]);
				varResistorAverageRead = adc_average_single_read(input[i], 25);
				char str[40];
				sprintf(str, "ADC%d read/avr = %d/%d\n", i, varResistorRead, varResistorAverageRead);
				usart_send_string(str);
			}
			_delay_ms(2000);
		}
	}
}
