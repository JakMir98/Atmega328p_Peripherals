#include "sleepModes.h"

void sleepmodes_go_to_sleep(SleepModes mode, uint8_t adcDisable, uint8_t spiDisable, 
                            uint8_t timer0Disable, uint8_t timer1Disable, uint8_t timer2Disable, 
                            uint8_t i2cDisable, uint8_t usartDisable)
{
    // Sleep mode is set here
	SMCR |= (int)mode << SM0;

	// Enables the sleep bit in the mcucr register
	sleep_enable(); 
	
	// make sure to set sleep mode according to needs so choose sleep mode which contains chossen wakeup source
    if (adcDisable > 0)
    {
        power_adc_disable();
    }
    if (spiDisable > 0)
    {
        power_spi_disable();
    }
    if (timer0Disable > 0)
    {
        power_timer0_disable();
    }
    if (timer1Disable > 0)
    {
        power_timer1_disable();
    }
	if (timer2Disable > 0)
    {
        power_timer2_disable();
    }
	if (i2cDisable > 0)
    {
        power_twi_disable();
    }
	if (usartDisable > 0)
    {
        power_usart0_disable();
    }
	sleep_mode();

	// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
	sleep_disable();
	power_all_enable();
}