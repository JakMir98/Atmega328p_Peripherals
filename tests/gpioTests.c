/*
 * gpioTests.c
 *
 * Created: 14.01.2022 16:58:38
 *  Author: Admin
 */ 
#ifndef F_CPU
	#define F_CPU 16000000
#endif

#include <util/delay.h>
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\tests\tests.h"
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\gpio.h"

volatile uint8_t testLedState = 0;
volatile uint8_t testLedState2 = 0;

void gpio_interrupt_function()
{
	testLedState ^= 1;
}

void gpio_test()
{
	gpio_set_pin_mode(PCINT23_VAL, OUTPUT);
	gpio_set_pin_mode(PCINT21_VAL, OUTPUT);
	gpio_set_pin_mode(PCINT22_VAL, INPUT_PULLUP);
	gpio_set_pin_mode(PCINT0_VAL, INPUT_PULLUP);
	
	gpio_set_pin_state(PCINT23_VAL, HIGH);
	gpio_set_pin_state(PCINT21_VAL, HIGH);
	gpio_set_pin_state(PCINT22_VAL, LOW);
	gpio_set_pin_state(PCINT0_VAL, LOW);
	
	gpio_set_interrupt(TRUE, PCINT0_VAL, gpio_interrupt_function);
	gpio_set_interrupt(TRUE, PCINT22_VAL, gpio_interrupt_function);
	
	while (1)
	{
		gpio_set_pin_state(PCINT23_VAL, HIGH);
		_delay_ms(1000);
		gpio_set_pin_state(PCINT23_VAL, LOW);
		_delay_ms(1000);
		
		if (testLedState == 1)
		{
			gpio_set_pin_state(PCINT21_VAL, HIGH);
		}
		else
		{
			gpio_set_pin_state(PCINT21_VAL, LOW);
		}
	}
}
