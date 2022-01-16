/*
 * sleepModesTests.c
 *
 * Created: 14.01.2022 18:02:24
 *  Author: Admin
 */ 
#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\tests.h"
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\sleepModes.h"
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\usart.h"

#include <stdio.h>
#include <string.h>

volatile char received;

typedef enum
{
	SLEEP_MODE,
	BLINK_MODE
}TestModes;

static void usart_interrupt_function()
{
	received = usart_receive();
	if (received == 'b')
	{
		testMode = BLINK_MODE;
	}
	else if(received == 's')
	{
		testMode = SLEEP_MODE;
	}
}

volatile TestModes testMode = SLEEP_MODE;

void sleepModes_test()
{
	usart_init_interrupts(UBRR_ASYNC_NORMAL, 1, usart_interrupt_function, 0, 0);
	gpio_set_pin_mode(PCINT23_VAL, OUTPUT);
	while (1)
	{
		if (testMode == BLINK_MODE)
		{
			gpio_set_pin_state(PCINT23_VAL, HIGH);
			_delay_ms(1000);
			gpio_set_pin_state(PCINT23_VAL, LOW);
			_delay_ms(1000);
		}
		else
		{
			sleepmodes_go_to_sleep(IDLE, 1, 1, 1, 1, 1, 1, 0); //leave usart to wakeup
		}
	}
}
