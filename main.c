/*
 * Atmega328p_Peripherals.cpp
 *
 * Created: 03.01.2022 14:56:10
 * Author : Admin
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include "inc/adc.h"
#include "inc/gpio.h"
#include "inc/sleepModes.h"
#include "inc/spi.h"
#include "inc/usart.h"

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

