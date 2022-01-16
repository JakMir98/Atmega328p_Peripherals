#include "gpio.h"

/**************************************************************************************\
* Interrupt function pointers
\**************************************************************************************/
void (*int0Function)() = 0;
void (*int1Function)() = 0;
void (*pcint0Function)() = 0;
void (*pcint1Function)() = 0;
void (*pcint2Function)() = 0;

void gpio_set_pin_mode(PCINT_MAP pin, PinMode mode)
{
	if (mode == INPUT)
	{
		switch (pin)
		{
			case PCINT0_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB0);
				break;
			case PCINT1_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB1);
				break;
			case PCINT2_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB2);
				break;
			case PCINT3_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB3);
				break;
			case PCINT4_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB4);
				break;
			case PCINT5_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB5);
				break;
			case PCINT6_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB6);
				break;
			case PCINT7_VAL:
				gpio_set_pin_input(DDRB, PORTB, PINB7);
				break;
			case PCINT8_VAL:
				gpio_set_pin_input(DDRC, PORTC, PINC0);
				break;
			case PCINT9_VAL:
				gpio_set_pin_input(DDRC, PORTC, PINC1);
				break;
			case PCINT10_VAL:
				gpio_set_pin_input(DDRC, PORTC, PINC2);
				break;
			case PCINT11_VAL:
				gpio_set_pin_input(DDRC, PORTC, PINC3);
				break;
			case PCINT12_VAL:
				gpio_set_pin_input(DDRC, PORTC, PINC4);
				break;
			case PCINT13_VAL:
				gpio_set_pin_input(DDRC, PORTC, PINC5);
				break;
			case PCINT14_VAL:
				gpio_set_pin_input(DDRC, PORTC, PINC6);
				break;
			case PCINT16_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND0);
				break;
			case PCINT17_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND1);
				break;
			case PCINT18_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND2);
				break;
			case PCINT19_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND3);
				break;
			case PCINT20_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND4);
				break;
			case PCINT21_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND5);
				break;
			case PCINT22_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND6);
				break;
			case PCINT23_VAL:
				gpio_set_pin_input(DDRD, PORTD, PIND7);
				break;
		}
	}
	else if (mode == INPUT_PULLUP)
	{
		switch (pin)
		{
			case PCINT0_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB0);
				break;
			case PCINT1_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB1);
				break;
			case PCINT2_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB2);
				break;
			case PCINT3_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB3);
				break;
			case PCINT4_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB4);
				break;
			case PCINT5_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB5);
				break;
			case PCINT6_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB6);
				break;
			case PCINT7_VAL:
				gpio_set_pin_inputPullup(DDRB, PORTB, PINB7);
				break;
			case PCINT8_VAL:
				gpio_set_pin_inputPullup(DDRC, PORTC, PINC0);
				break;
			case PCINT9_VAL:
				gpio_set_pin_inputPullup(DDRC, PORTC, PINC1);
				break;
			case PCINT10_VAL:
				gpio_set_pin_inputPullup(DDRC, PORTC, PINC2);
				break;
			case PCINT11_VAL:
				gpio_set_pin_inputPullup(DDRC, PORTC, PINC3);
				break;
			case PCINT12_VAL:
				gpio_set_pin_inputPullup(DDRC, PORTC, PINC4);
				break;
			case PCINT13_VAL:
				gpio_set_pin_inputPullup(DDRC, PORTC, PINC5);
				break;
			case PCINT14_VAL:
				gpio_set_pin_inputPullup(DDRC, PORTC, PINC6);
				break;
			case PCINT16_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND0);
				break;
			case PCINT17_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND1);
				break;
			case PCINT18_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND2);
				break;
			case PCINT19_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND3);
				break;
			case PCINT20_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND4);
				break;
			case PCINT21_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND5);
				break;
			case PCINT22_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND6);
				break;
			case PCINT23_VAL:
				gpio_set_pin_inputPullup(DDRD, PORTD, PIND7);
				break;
		}
	}
	else // output
	{
		switch (pin)
		{
			case PCINT0_VAL:
				gpio_set_pin_output(PORTB, PINB0);
				break;
			case PCINT1_VAL:
				gpio_set_pin_output(PORTB, PINB1);
				break;
			case PCINT2_VAL:
				gpio_set_pin_output(PORTB, PINB2);
				break;
			case PCINT3_VAL:
				gpio_set_pin_output(PORTB, PINB3);
				break;
			case PCINT4_VAL:
				gpio_set_pin_output(PORTB, PINB4);
				break;
			case PCINT5_VAL:
				gpio_set_pin_output(PORTB, PINB5);
				break;
			case PCINT6_VAL:
				gpio_set_pin_output(PORTB, PINB6);
				break;
			case PCINT7_VAL:
				gpio_set_pin_output(PORTB, PINB7);
				break;
			case PCINT8_VAL:
				gpio_set_pin_output(PORTC, PINC0);
				break;
			case PCINT9_VAL:
				gpio_set_pin_output(PORTC, PINC1);
				break;
			case PCINT10_VAL:
				gpio_set_pin_output(PORTC, PINC2);
				break;
			case PCINT11_VAL:
				gpio_set_pin_output(PORTC, PINC3);
				break;
			case PCINT12_VAL:
				gpio_set_pin_output(PORTC, PINC4);
				break;
			case PCINT13_VAL:
				gpio_set_pin_output(PORTC, PINC5);
				break;
			case PCINT14_VAL:
				gpio_set_pin_output(PORTC, PINC6);
				break;
			case PCINT16_VAL:
				gpio_set_pin_output(PORTD, PIND0);
				break;
			case PCINT17_VAL:
				gpio_set_pin_output(PORTD, PIND1);
				break;
			case PCINT18_VAL:
				gpio_set_pin_output(PORTD, PIND2);
				break;
			case PCINT19_VAL:
				gpio_set_pin_output(PORTD, PIND3);
				break;
			case PCINT20_VAL:
				gpio_set_pin_output(PORTD, PIND4);
				break;
			case PCINT21_VAL:
				gpio_set_pin_output(PORTD, PIND5);
				break;
			case PCINT22_VAL:
				gpio_set_pin_output(PORTD, PIND6);
				break;
			case PCINT23_VAL:
				gpio_set_pin_output(PORTD, PIND7);
				break;
		}
	}
}

void gpio_set_pin_state(PCINT_MAP pin, PinState mode)
{
	switch (pin)
	{
		case PCINT0_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB0);
			else
				gpio_set_bit(PORTB, PINB0);
			break;
		case PCINT1_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB1);
			else
				gpio_set_bit(PORTB, PINB1);
			break;
		case PCINT2_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB2);
			else
				gpio_set_bit(PORTB, PINB2);
			break;
		case PCINT3_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB3);
			else
				gpio_set_bit(PORTB, PINB3);
			break;
		case PCINT4_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB4);
			else
				gpio_set_bit(PORTB, PINB4);
			break;
		case PCINT5_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB5);
						else
				gpio_set_bit(PORTB, PINB5);
			break;
		case PCINT6_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB6);
			else
				gpio_set_bit(PORTB, PINB6);
			break;
		case PCINT7_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTB, PINB7);
			else
				gpio_set_bit(PORTB, PINB7);
			break;
		case PCINT8_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTC, PINC0);
			else
				gpio_set_bit(PORTC, PINC0);
			break;
		case PCINT9_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTC, PINC1);
			else
				gpio_set_bit(PORTC, PINC1);
			break;
		case PCINT10_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTC, PINC2);
			else
				gpio_set_bit(PORTC, PINC2);
			break;
		case PCINT11_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTC, PINC3);
			else
				gpio_set_bit(PORTC, PINC3);
			break;
		case PCINT12_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTC, PINC4);
			else
				gpio_set_bit(PORTC, PINC4);
			break;
		case PCINT13_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTC, PINC5);
			else
				gpio_set_bit(PORTC, PINC5);
			break;
		case PCINT14_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTC, PINC6);
			else
				gpio_set_bit(PORTC, PINC6);
			break;
		case PCINT16_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND0);
			else
				gpio_set_bit(PORTD, PIND0);
			break;
		case PCINT17_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND1);
			else
				gpio_set_bit(PORTD, PIND1);
			break;
		case PCINT18_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND2);
			else
				gpio_set_bit(PORTD, PIND2);
			break;
		case PCINT19_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND3);
			else
				gpio_set_bit(PORTD, PIND3);
			break;
		case PCINT20_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND4);
			else
				gpio_set_bit(PORTD, PIND4);
			break;
		case PCINT21_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND5);
			else
				gpio_set_bit(PORTD, PIND5);
			break;
		case PCINT22_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND6);
			else
				gpio_set_bit(PORTD, PIND6);
			break;
		case PCINT23_VAL:
			if (mode == LOW)
				gpio_reset_bit(PORTD, PIND7);
			else
				gpio_set_bit(PORTD, PIND7);
			break;
	}
}

void gpio_set_external_interrupt(uint8_t enable, ExternalInterruptName externalIntterupt,
                                    ExternalInterruptSenseControl senseControl, void (*callback)())
{
    if (enable > 0)
    {
		sei();
        //SREG |= 1 << SREG_I;
        if (externalIntterupt == EXT_INT0)
        {
			EICRA &= ~((1 << ISC00) | (1 << ISC01)); 
            EICRA |= (int)senseControl << ISC00;
            EIMSK |= 1 << INT0;
            int0Function = callback;
        }
        else if (externalIntterupt == EXT_INT1)
        {
			EICRA &= ~((1 << ISC10) | (1 << ISC11)); 
            EICRA |= (int)senseControl << ISC10;
            EIMSK |= 1 << INT1;
            int1Function = callback;
        }
    }
	else
	{
		if (externalIntterupt == EXT_INT0)
		{
			EIMSK &= ~(1 << INT0);
			int0Function = 0;
		}
		else if (externalIntterupt == EXT_INT1)
		{
			EIMSK &= ~(1 << INT1);
			int1Function = 0;
		}
	}
}
void gpio_set_interrupt(uint8_t enable, PCINT_MAP pcintNumber, void (*callback)())
{
    if (enable > 0)
    {
		sei();
		if ((int)pcintNumber < 8)
		{
			PCICR |= 1 << PCIE0;
			PCMSK0 |= (1 << (int)pcintNumber);
			pcint0Function = callback;
		}
		else if((int)pcintNumber < 15)
		{
			PCICR |= 1 << PCIE1; 
			PCMSK1 |= (1 << ((int)pcintNumber - 8));
			pcint1Function = callback;
		}
		else
		{
			PCICR |= 1 << PCIE2;
			PCMSK2 |= (1 << ((int)pcintNumber - 16));
			pcint2Function = callback;
		}
    }
	else
	{
		if ((int)pcintNumber < 8)
		{
			PCMSK0 &= ~(1 << (int)pcintNumber);
			pcint0Function = 0;
		}
		else if((int)pcintNumber < 15)
		{
			PCMSK1 &= ~(1 << ((int)pcintNumber - 8));
			pcint1Function = 0;
		}
		else
		{
			PCMSK2 &= ~(1 << ((int)pcintNumber - 16));
			pcint2Function = 0;
		}
	}
}

void gpio_register_int0_callback(void (*callback)())
{
    int0Function = callback;
}

void gpio_deregister_int0_callback(void)
{
    int0Function = 0;
}

void gpio_register_int1_callback(void (*callback)())
{
    int1Function = callback;
}

void gpio_deregister_int1_callback(void)
{
    int1Function = 0;
}

void gpio_register_pcint0_callback(void (*callback)())
{
    pcint0Function = callback;
}

void gpio_deregister_pcint0_callback(void)
{
    pcint0Function = 0;
}

void gpio_register_pcint1_callback(void (*callback)())
{
    pcint1Function = callback;
}

void gpio_deregister_pcint1_callback(void)
{
    pcint1Function = 0;
}

void gpio_register_pcint2_callback(void (*callback)())
{
    pcint2Function = callback;
}

void gpio_deregister_pcint2_callback(void)
{
    pcint2Function = 0;
}

ISR(INT0_vect) 
{
	if(int0Function != 0)
        int0Function();
}

ISR(INT1_vect) 
{
	if(int1Function != 0)
        int1Function();
}

ISR(PCINT0_vect)
{
	if(pcint0Function != 0)
        pcint0Function();
}

ISR(PCINT1_vect)
{
	if(pcint1Function != 0)
        pcint1Function();
}

ISR(PCINT2_vect)
{
    if(pcint2Function != 0)
        pcint2Function();
}
