#include "timers.h"

/**************************************************************************************\
* Interrupt function pointers
\**************************************************************************************/
void (*timer0overflowInterruptFunction)() = 0;
void (*timer0compBInterruptFunction)() = 0;
void (*timer0compAInterruptFunction)() = 0;
void (*timer1overflowInterruptFunction)() = 0;
void (*timer1compBInterruptFunction)() = 0;
void (*timer1compAInterruptFunction)() = 0;
void (*timer1captureEventInterruptFunction)() = 0;
void (*timer2overflowInterruptFunction)() = 0;
void (*timer2compBInterruptFunction)() = 0;
void (*timer2compAInterruptFunction)() = 0;

void TIMER_OVERFLOW_init()
{
	// TIMER0 - 8 bit  
	TCCR0A = 0b00000000; // normal port operation
	TCCR0B = (1 << CS02) | (1 << CS00); // 0b00000101 clock / 1024
	TIMSK0 = (1 << TOIE0); // 0b00000001 enable Timer/Counter 0 Overflow Interrupt

	// TIMER1 - 16 bit
	TCCR1A = 0b00000000; // normal port operation
	TCCR1B = (1 << CS12) | (1 << CS10); //0b00000010 clock / 1024
	TCCR1C = 0b00000000;
	TIMSK1 = (1 << TOIE1); // 0b00000001  enable Timer/Counter 1 Overflow Interrupt
}

void TIMER_COMPARE_init()
{
	//F_CPU=16MHz: Clock time period = 1000ms / 16000000Hz = 0.0000625ms
	//Timer count = (Required Delay / Clock Time Period)-1 = (1000ms / 0.0000625ms) = 15999999
	//The clock has already ticked 15999999 times to give a delay of 1s!
	// tick every 1 sec
	
	TCCR1B |= (1 << WGM12)|(1 << CS12); // set up timer with prescaler = 256 and CTC mode
	TCNT1 = 0; // initialize counter
	OCR1A = 62500; // initialize compare value
	TIMSK1 |= (1 << OCIE1A); // enable compare interrupt
	
}

//TIMER0 overflow interrupt
ISR(TIMER0_OVF_vect) 
{
	if (timer0overflowInterruptFunction != 0)
		timer0overflowInterruptFunction();
}


ISR(TIMER0_COMPA_vect)
{
	if (timer0compAInterruptFunction != 0)
		timer0compAInterruptFunction();
}

ISR(TIMER0_COMPB_vect)
{
	if (timer0compBInterruptFunction != 0)
		timer0compBInterruptFunction();
}


//TIMER1 overflow interrupt
ISR(TIMER1_OVF_vect) 
{
	if (timer1overflowInterruptFunction != 0)
		timer1overflowInterruptFunction();
}

ISR(TIMER1_COMPA_vect)
{
	if (timer1compAInterruptFunction != 0)
		timer1compAInterruptFunction();
}

ISR(TIMER1_COMPB_vect)
{
	if (timer1compBInterruptFunction != 0)
		timer1compBInterruptFunction();
}


ISR(TIMER1_CAPT_vect)
{
	if (timer1captureEventInterruptFunction != 0)
		timer1captureEventInterruptFunction();
}

ISR(TIMER2_OVF_vect)
{
	if (timer2overflowInterruptFunction != 0)
		timer2overflowInterruptFunction();
}

ISR (TIMER2_COMPA_vect)
{
	if (timer2compAInterruptFunction != 0)
		timer2compAInterruptFunction();
}

ISR (TIMER2_COMPB_vect)
{
	if (timer2compBInterruptFunction != 0)
		timer2compBInterruptFunction();
}



