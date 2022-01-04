#include "/Projekty/C(C++) projects/AVR projects/Atmega328p_Peripherals/Atmega328p_Peripherals/inc/gpio.h"

void GPIO_init(void)
{
	//SET_PIN_AS_OUTPUT(PORTB, PUMP_PIN);

	// setup INT0 for UART INTERRUPT
	GPIO_set_pin_inputPullup(DDRD, PORTD, 2);
	
	// setup interrupt on pin 3 PORTB (PCINT2)
	//SET_PIN_AS_INPUT_PULLUP(DDRB, PORTB, SOME_TEST_INPUT_PIN);
	//PCICR = (1 << PCIE0);  //enable pin change interrupt on pins PCINT7 through PCINT0
	//PCMSK0 = (1 << PCINT2);
	
	// INT1 interrupt setup
	//PUSH_BUTTON_PIN = 3 on PORTD 
	//SET_PIN_AS_INPUT_PULLUP(DDRD, PORTD, SOME_INPUT_PIN);
	//EIMSK |= (1 << INT1); // INT1 interrupt 
	//EICRA |= (1 << ISC10) | (0 << ISC11); // falling edge of INT1 
}

//INT1 interrupt
/* 
ISR(INT1_vect) 
{
	someVariable ^= 1;
}

//PCINT[0-7] interrupt
ISR(PCINT0_vect)
{
	someVariable ^= 1;
}
*/

void GPIO_set_pin_inputPullup(uint8_t directionRegister, uint8_t portRegister, uint8_t pinNumber)
{
	directionRegister &= ~(1 << pinNumber);
	portRegister |= (1 << pinNumber);
}

void GPIO_set_pin_output(uint8_t portRegister, uint8_t pinNumber)
{
	portRegister |= (1 << pinNumber);
}

void GPIO_set_bit(uint8_t portRegister, uint8_t pinNumber)
{
	portRegister |= (1 << pinNumber);
}

void GPIO_reset_bit(uint8_t portRegister, uint8_t pinNumber)
{
	portRegister &= ~(1 << pinNumber);
}

void GPIO_toogle_bit(uint8_t portRegister, uint8_t pinNumber)
{
	portRegister ^= (1 << pinNumber);
}

uint8_t GPIO_is_bit_set(uint8_t portRegister, uint8_t pinNumber)
{
	return portRegister & (1 << pinNumber);
}
