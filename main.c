/*
 * Atmega328p_Peripherals.cpp
 *
 * Created: 03.01.2022 14:56:10
 * Author : Admin
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "gpio.h"
#include "sleepModes.h"
#include "spi.h"
#include "usart.h"

#include "tests.h"


int main(void)
{
	
	//gpio_test();
	//usart_test(FIRST_TEST);
	//adc_test(SECOND_TEST);
	//sleepModes_test();
	
    while (1) 
    {
		
    }
}

