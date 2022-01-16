#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\spi.h"

/**************************************************************************************\
* Interrupt function pointers
\**************************************************************************************/
void (*spiInterruptFunction)() = 0;

void spi_enable(void)
{
    SPCR |= 1 << SPE;
}

void spi_disable(void)
{
    SPCR &= ~(1 << SPE);
}

void spi_setup_as_master(void)
{
    SPCR |= (1<<MSTR);
}

void spi_interrupt_enable(uint8_t enable)
{
    if (enable > 0)
    {
        SREG |= 1 << SREG_I;
        SPSR |= 1 << SPIF;
    }
}

void spi_register_callback(void (*callback)())
{
    spiInterruptFunction = callback;
}

void spi_deregister_callback(void)
{
    spiInterruptFunction = 0;
}

void spi_set_data_order(SpiDataOrder order)
{
    SPCR |= (int)order << DORD;
}

void spi_set_clock_polarity(SpiClockPolarity clockPolarity)
{
    SPCR |= (int)clockPolarity << CPOL;
}

void spi_set_clock_phase(SpiClockPhase clockPhase)
{
    SPCR |= (int)clockPhase << CPHA;
}

void spi_set_clk_oscilattor_relation(SpiClkOcilatorRelation clkRelation, uint8_t doubleSpiSpeed)
{
    if (doubleSpiSpeed > 0)
    {
        SPSR |= 1 << SPI2X;
    }

    SPCR |= (int)clkRelation << SPR0;
}

void spi_master_default_init(void)
{
	// Set MOSI and SCK output, all others input
	DATA_REGISTER_SPI = (1<<MOSI_PIN)|(1<<SCK_PIN);
	
	// Enable SPI, Master, set clock rate fck/16
    spi_enable();
    spi_setup_as_master();
    spi_set_clk_oscilattor_relation(FOSC_DIVIDED_BY_16, 0);
}

void spi_master_init(uint8_t interruptEnable, void (*callback)(), SpiDataOrder order, 
                        SpiClockPolarity clockPolarity, SpiClockPhase clockPhase,
                        SpiClkOcilatorRelation clkRelation, uint8_t doubleSpiSpeed)
{
    DATA_REGISTER_SPI = (1<<MOSI_PIN)|(1<<SCK_PIN);
	
	// Enable SPI, Master, set clock rate fck/16
    spi_enable();
    spi_setup_as_master();
    spi_interrupt_enable(interruptEnable);
    spi_register_callback(callback);
    spi_set_data_order(order);
    spi_set_clock_polarity(clockPolarity);
    spi_set_clock_phase(clockPhase);
    spi_set_clk_oscilattor_relation(clkRelation, doubleSpiSpeed);
}

void spi_master_transmit(char cData)
{
	// Start transmission
	SPDR = cData;
	
	// Wait for transmission complete
	while(!(SPSR & (1<<SPIF)));
}

void spi_slave_default_init(void)
{
	// Set MISO output, all others input
	DATA_REGISTER_SPI = (1<<MISO_PIN);
	
	// Enable SPI
    spi_enable();
}

char spi_slave_receive(void)
{
	// Wait for reception complete
	while(!(SPSR & (1<<SPIF)));
	
	// Return Data Register
	return SPDR;
}

ISR(SPI_STC_vect)
{
    if(spiInterruptFunction != 0)
        spiInterruptFunction();
}