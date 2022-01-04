#include "/Projekty/C(C++) projects/AVR projects/Atmega328p_Peripherals/Atmega328p_Peripherals/inc/sleepModes.h"
#include <avr/sleep.h>
#include <avr/power.h>

/**
 * @brie Go to sleep
 */
void SLEEPMODES_go_to_sleep()
{
	// Sleep mode is set here
	set_sleep_mode(SLEEP_MODE_IDLE); 

	// Enables the sleep bit in the mcucr register
	sleep_enable(); 
	
	// make sure to leave some wakeup sources, eg in this project usart INT0 is wakeup source

	power_adc_disable();
	power_spi_disable();
	power_timer0_disable();
	power_timer1_disable();
	power_timer2_disable();
	power_twi_disable();

	sleep_mode();

	// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
	sleep_disable();
	power_all_enable();

}
