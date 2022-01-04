#include "/Projekty/C(C++) projects/AVR projects/Atmega328p_Peripherals/Atmega328p_Peripherals/inc/spi.h"

ISR(SPI_STC_vect)
{

}

void SPI_master_init(void)
{
	// Set MOSI and SCK output, all others input
	DATA_REGISTER_SPI = (1<<MOSI_PIN)|(1<<DD_SCK);
	
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_master_transmit(char cData)
{
	// Start transmission
	SPDR = cData;
	
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)))
	;
}

void SPI_slave_init(void)
{
	// Set MISO output, all others input
	DATA_REGISTER_SPI = (1<<MISO_PIN);
	
	// Enable SPI
	SPCR = (1<<SPE);
}

char SPI_slave_receive(void)
{
	// Wait for reception complete
	while(!(SPSR & (1<<SPIF)));
	
	// Return Data Register
	return SPDR;
}
