#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\usart.h"

/**************************************************************************************\
* Interrupt function pointers
\**************************************************************************************/
void (*usartRxInterruptFunction)() = 0;
void (*usartTxInterruptFunction)() = 0;
void (*usartDataRegisterEmptyInterruptFunction)() = 0;

void usart_init(unsigned int ubrr)
{	
    usart_set_baudrate(ubrr);
	usart_set_receiver_enable(1);
    usart_set_transmitter_enable(1);

    usart_set_parity(DISABLED);
    usart_set_stop_bit(ONE_BIT);
    usart_set_character_size(EIGHT_BIT);
}

void usart_init_interrupts(unsigned int ubrr, uint8_t rxIntEnable, void (*rxFunction)(), 
                            uint8_t txIntEnable,  void (*txFunction)())
{	
    usart_set_baudrate(ubrr);
	usart_set_receiver_enable(1);
    usart_set_transmitter_enable(1);

    usart_set_parity(DISABLED);
    usart_set_stop_bit(ONE_BIT);
    usart_set_character_size(EIGHT_BIT);

    if (rxIntEnable > 0)
    {
        usart_set_rx_interrupt(1);
        usartRxInterruptFunction = rxFunction;
    }

    if (txIntEnable > 0)
    {
        usart_set_tx_interrupt(1);
        usartTxInterruptFunction = txFunction;
    }
}

void usart_param_init(unsigned int ubrr, uint8_t receiverEnable, uint8_t transmitterEnable, 
                        UsartMode mode, UsartParity parity, UsartStopBit stopBit, 
                        UsartCharacterSize characterSize, UsartClockPolarity clockPolarity, 
                        uint8_t rxIntEnable, void (*rxFunction)(), 
                        uint8_t txIntEnable,  void (*txFunction)())
{
    usart_set_baudrate(ubrr);
	usart_set_receiver_enable(receiverEnable);
    usart_set_transmitter_enable(transmitterEnable);
    usart_set_mode(mode);
    usart_set_parity(parity);
    usart_set_stop_bit(stopBit);
    usart_set_character_size(characterSize);
    usart_set_clock_polarity(clockPolarity);

    if (rxIntEnable > 0)
    {
        usart_set_rx_interrupt(1);
        usartRxInterruptFunction = rxFunction;
    }

    if (txIntEnable > 0)
    {
        usart_set_tx_interrupt(1);
        usartTxInterruptFunction = txFunction;
    }
}

void usart_set_mode(UsartMode mode)
{
    UCSR0C |= (int)mode << UMSEL00;
}

void usart_set_parity(UsartParity parity)
{
    UCSR0C |= (int)parity << UPM00;
}

void usart_set_stop_bit(UsartStopBit stopBit)
{
    UCSR0C |= (int)stopBit << USBS0;
}

void usart_set_character_size(UsartCharacterSize characterSize)
{
    if (characterSize == NINE_BIT)
    {
        UCSR0C |= 3 << UCSZ00;
        UCSR0B |= 1 << UCSZ02;
    }
    else
    {
        UCSR0C |= (int)characterSize << UCSZ00;
    }
}

void usart_set_clock_polarity(UsartClockPolarity clockPolarity)
{
    UCSR0C |= (int)clockPolarity << UCPOL0;
}

void usart_set_baudrate(unsigned int ubrr)
{
	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;
}

void usart_set_receiver_enable(uint8_t rxEnable)
{
    if(rxEnable > 0)
    {
        UCSR0B |= (1<<RXEN0);
    }
    else
    {
        UCSR0B &= ~(1<<RXEN0);
    }
}

void usart_set_transmitter_enable(uint8_t txEnable)
{
    if(txEnable > 0)
    {
        UCSR0B |= (1<<TXEN0);
    }
    else
    {
        UCSR0B &= ~(1<<TXEN0);
    }
}

void usart_set_tx_interrupt(uint8_t txInterrupt)
{
    if (txInterrupt > 0)
    {
        SREG |= 1 << SREG_I;
        UCSR0B |= 1 << TXCIE0;
    }
    else
    {
        UCSR0B &= ~(1 << TXCIE0);
    }
}

void usart_set_rx_interrupt(uint8_t rxInterrupt)
{
    if (rxInterrupt > 0)
    {
        SREG |= 1 << SREG_I;
        UCSR0B |= 1 << RXCIE0;
    }
    else
    {
        UCSR0B &= ~(1 << RXCIE0);
    }
}

void usart_set_double_usart_transmission_speed(uint8_t speed)
{
    if (speed > 0)
    {
        UCSR0A |= 1 << U2X0;
    }
    else
    {
        UCSR0A &= ~(1 << U2X0);
    }
}

void usart_set_multiProcessor_communication_mode(uint8_t mode)
{
    if (mode > 0)
    {
        UCSR0A |= 1 << MPCM0;
    }
    else
    {
        UCSR0A &= ~(1 << MPCM0);
    }
}

void usart_register_rx_callback(void (*callback)())
{
    usartRxInterruptFunction = callback;
}

void usart_deregister_rx_callback(void)
{
    usartRxInterruptFunction = 0;
}

void usart_register_tx_callback(void (*callback)())
{
    usartTxInterruptFunction = callback;
}

void usart_deregister_tx_callback(void)
{
    usartTxInterruptFunction = 0;
}

void usart_register_dataRegisterEmpty_callback(void (*callback)())
{
    usartDataRegisterEmptyInterruptFunction = callback;
}

void usart_deregister_dataRegisterEmpty_callback(void)
{
    usartDataRegisterEmptyInterruptFunction = 0;
}

void usart_transmit(char data)
{
	// Wait for empty transmit buffer
	while (!(UCSR0A & (1<<UDRE0))) ;
	// Put data into buffer, sends the data
	UDR0 = data;
}

void usart_send_string(char string[])
{
	for (int i=0; i < strlen(string); i++)
	usart_transmit(string[i]);
}

char usart_receive(void)
{
	// Wait for data to be received
	while (!(UCSR0A & (1<<RXC0)));
	
	// Get and return received data from buffer
	return UDR0;
}

uint8_t usart_receive_string(char *pString)
{
	char ch;
	uint8_t len = 0;
	while(1)
	{
		ch=usart_receive();    //Receive a char
		//usart_transmit(ch);     //Echo back the received char

		if((ch=='\r') || (ch=='\n')) //read till enter key is pressed
		{						     //once enter key is pressed null terminate the string
			pString[len]=0;           //and break the loop
			break;
		}
		else if((ch=='\b') && (len!=0))
		{
			len--;    //If backspace is pressed then decrement the index to remove the old char
		}
		else
		{
			pString[len++]=ch; //copy the char into string and increment the index
		}
	}
	return len;
}

void usart_flush( void )
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

void usart_transmit_9databits( unsigned int data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)));
    /* Copy 9th bit to TXB8 */
    UCSR0B &= ~(1<<TXB80);

    if ( data & 0x0100 )
        UCSR0B |= (1<<TXB80);
    /* Put data into buffer, sends the data */
    UDR0 = data; 
}

unsigned int usart_receive_9databits( void )
{
   unsigned char status, resh, resl;
   /* Wait for data to be received */
   while ( !(UCSR0A & (1<<RXC0)) );
   /* Get status and 9th bit, then data */
   /* from buffer */
   status = UCSR0A;
   resh = UCSR0B;
   resl = UDR0;
   /* If error, return -1 */
   if ( status & ((1<<FE0)|(1<<DOR0)|(1<<UPE0)) )
      return -1;
   /* Filter the 9th bit, then return */
   resh = (resh >> 1) & 0x01;
   return ((resh << 8) | resl);
}

ISR(USART_RX_vect)
{
    if(usartRxInterruptFunction != 0)
        usartRxInterruptFunction();
}

ISR(USART_TX_vect)
{
    if(usartTxInterruptFunction != 0)
        usartTxInterruptFunction();
}

ISR(USART_UDRE_vect)
{
    if(usartDataRegisterEmptyInterruptFunction != 0)
        usartDataRegisterEmptyInterruptFunction();
}
