/*
 * usartTests.c
 *
 * Created: 14.01.2022 17:38:19
 *  Author: Admin
 */ 

#ifndef F_CPU
	#define F_CPU 16000000
#endif

#include <util/delay.h>

#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\tests.h"
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\gpio.h"
#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\usart.h"

#include <stdio.h>
#include <string.h>

#define BUFFER_MAX_SIZE 50
volatile char received;
volatile char receivedBuffer[BUFFER_MAX_SIZE];
volatile int charCounter = 0;

static void usart_interrupt_function()
{
	//received = usart_receive();
	receivedBuffer[charCounter++] = usart_receive();
	if(charCounter >= BUFFER_MAX_SIZE - 1)
	{
		charCounter = 0;
	}
}

void usart_test(TestType testType)
{
	if (testType == FIRST_TEST)
	{
		usart_init(UBRR_ASYNC_NORMAL);
		usart_send_string("Init done");
		
		while (1)
		{
			_delay_ms(1000);
			charCounter++;
			char str[25];
			sprintf(str, "Counter = %d", charCounter);
			usart_send_string(str);
			usart_send_string(" \n");
		}
	}
	else
	{
		usart_init_interrupts(UBRR_ASYNC_NORMAL, TRUE, usart_interrupt_function, FALSE, 0);
		usart_send_string("Init done");
		
		while (1)
		{
			_delay_ms(1000);
			char arr[BUFFER_MAX_SIZE];
			strcpy(arr, receivedBuffer);
			usart_send_string(arr);
		}
	}
}
