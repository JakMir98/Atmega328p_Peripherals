#include "/Projekty/C(C++) projects/AVR projects/Atmega328p_Peripherals/Atmega328p_Peripherals/inc/uart.h"

void USART_init(unsigned int ubrr)
{
	UBRR0H = (MYUBRR >> 8);
	UBRR0L = MYUBRR;
	
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// Set frame format: 8 data bits, parity None, 1 stop bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	//enable receive interrupt
	UCSR0B |= ( 1 << RXCIE0);
}

void USART_transmit(char data)
{
	// Wait for empty transmit buffer
	while (!(UCSR0A & (1<<UDRE0))) ;
	// Put data into buffer, sends the data
	UDR0 = data;
}

char USART_receive(void)
{
	// Wait for data to be received
	while (!(UCSR0A & (1<<RXC0)));
	
	// Get and return received data from buffer
	return UDR0;
}

void USART_send_string(char string[])
{
	for (int i=0; i < strlen(string); i++)
	USART_transmit(string[i]);
}

void USART_flush( void )
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

ISR(USART_RX_vect)
{
	//received = USART_Receive();
}
