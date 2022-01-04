/*
 * uart.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 

#ifndef UART_H
#define UART_H                  

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

/**************************************************************************************\
* Private constants
\**************************************************************************************/
#define MYUBRR (((FOSC / (BAUD * 16UL))) - 1)

const uint32_t FOSC = 16000000; // Clock Speed
const int BAUD = 9600;

/**************************************************************************************\
* Private prototypes
\**************************************************************************************/

/**
 * @brief USART initialization
 */
void USART_init(unsigned int ubrr);

/**
 * @brief Transmit character through USART
 */
void USART_transmit(char data);

/**
 * @brief Receive character from USART
 */
char USART_receive(void);

/**
 * @brief Send string through USART
 */
void USART_send_string(char string[]);

/**
 * @brief Flush data from usart register
 */
void USART_flush( void );

#endif
