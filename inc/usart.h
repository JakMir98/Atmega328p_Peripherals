/*
 * uart.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 
#ifndef UART_H
#define UART_H                  

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

/**************************************************************************************\
* Constants
\**************************************************************************************/
#ifndef FOSC
    #define FOSC 16000000
#endif

#ifndef BAUD
    #define BAUD 9600
#endif

#define UBRR_ASYNC_NORMAL (((FOSC / (BAUD * 16UL))) - 1)
#define UBRR_ASYNC_DOUBLE_SPEED (((FOSC / (BAUD * 8UL))) - 1)
#define UBRR_SYNC_NORMAL (((FOSC / (BAUD * 2UL))) - 1)

/**************************************************************************************\
* Custom datatypes
\**************************************************************************************/
typedef enum 
{
    ASYNCHRONOUS_USART = 0,
    SYNCHRONOUS_USART = 1,
    MASTER_SPI = 3
} UsartMode;

typedef enum 
{
    DISABLED = 0,
    ENABLED_EVEN_PARITY = 2,
    ENABLED_ODD_PARITY = 3
} UsartParity;

typedef enum 
{
    ONE_BIT = 0,
    TWO_BIT = 1
} UsartStopBit;

typedef enum 
{
    FIVE_BIT = 0,
    SIX_BIT = 1,
    SEVEN_BIT = 2,
    EIGHT_BIT = 3,
    NINE_BIT = 7,
} UsartCharacterSize;

typedef enum 
{
    RISING_TX_FALLING_RX_EDGE = 0,
    RISING_RX_FALLING_TX_EDGE = 1
} UsartClockPolarity;

/**************************************************************************************\
* Prototypes
\**************************************************************************************/
/**
 * @brief USART initialization
 */
void usart_init(unsigned int ubrr);
void usart_init_interrupts(unsigned int ubrr, uint8_t rxIntEnable, void (*rxFunction)(), 
                            uint8_t txIntEnable,  void (*txFunction)());
void usart_param_init(unsigned int ubrr, uint8_t receiverEnable, uint8_t transmitterEnable, 
                        UsartMode mode, UsartParity parity, UsartStopBit stopBit, 
                        UsartCharacterSize characterSize, UsartClockPolarity clockPolarity, 
                        uint8_t rxIntEnable, void (*rxFunction)(), 
                        uint8_t txIntEnable,  void (*txFunction)());

void usart_set_mode(UsartMode mode);
void usart_set_parity(UsartParity parity);
void usart_set_stop_bit(UsartStopBit stopBit);
void usart_set_character_size(UsartCharacterSize characterSize);
void usart_set_clock_polarity(UsartClockPolarity clockPolarity);
void usart_set_baudrate(unsigned int ubrr);
void usart_set_receiver_enable(uint8_t rxEnable);
void usart_set_transmitter_enable(uint8_t txEnable);
void usart_set_tx_interrupt(uint8_t txInterrupt);
void usart_set_rx_interrupt(uint8_t rxInterrupt);
void usart_set_double_usart_transmission_speed(uint8_t speed);
void usart_set_multiProcessor_communication_mode(uint8_t mode);

void usart_register_rx_callback(void (*callback)());
void usart_deregister_rx_callback(void);
void usart_register_tx_callback(void (*callback)());
void usart_deregister_tx_callback(void);
void usart_register_dataRegisterEmpty_callback(void (*callback)());
void usart_deregister_dataRegisterEmpty_callback(void);

/**
 * @brief Transmit character through USART
 */
void usart_transmit(char data);

/**
 * @brief Receive character from USART
 */
char usart_receive(void);

/**
 * @brief Send string through USART
 */
void usart_send_string(char string[]);

/**
 * @brief Flush data from usart register
 */
void usart_flush(void);

/**
 * @brief Transmit 9 bit characters
 */
void usart_transmit_9databits( unsigned int data );

/**
 * @brief Receive 9 bit character
 */
unsigned int usart_receive_9databits(void);

#endif
