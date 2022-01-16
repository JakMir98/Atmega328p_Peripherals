#include "D:\Projekty\C(C++) projects\AVR projects\Atmega328p_Peripherals\Atmega328p_Peripherals\inc\adc.h"

void (*adcInterruptFunction)() = 0;

void adc_enable(void)
{
    ADCSRA |= (1<<ADEN);
}

void adc_disable(void)
{
    ADCSRA &= ~(1<<ADEN);
}


void adc_set_reference(ReferenceSelection reference)
{
	ADMUX |= ((int)reference<<REFS0);
}

void adc_set_left_adjust_result(uint8_t adcLeftAdjustResult)
{
	if (adcLeftAdjustResult > 0)
	{
		ADMUX |= (1<<ADLAR);
	}
	else
	{
		ADMUX &= ~(1<<ADLAR);
	}
}

void adc_set_prescaller(PrescallerSelection prescaller)
{
	ADCSRA |= ((int)prescaller<<ADPS0);
}

void adc_set_interrupt(uint8_t interrupt)
{
	if (interrupt > 0)
	{
		SREG |= 1 << SREG_I;
		ADCSRA |= (1 << ADIE);
	}
	else
	{
		ADCSRA &= ~(1 << ADIE); // DO NOT TURN OFF GLOBAL INTERRUPT BECAUSE OTHER MODULES CAN USE IT
	}
}

void adc_set_auto_trigger_enable(uint8_t autoTrigger)
{
	if (autoTrigger > 0)
	{
		ADCSRA |= (1 << ADATE);
	}
	else
	{
		ADCSRA &= ~(1 << ADATE);
	}
}

void adc_set_analog_comparator_multiplexer(uint8_t analogCompEna)
{
	if (analogCompEna > 0)
	{
		ADCSRB |= (1 << ACME);
	}
	else
	{
		ADCSRB &= ~(1 << ACME);
	}
}

void adc_set_auto_trigger_source(AutoTriggerSource autoTrigger)
{
	ADCSRB |= ((int)autoTrigger << ADTS0);
}


void adc_default_init(void)
{
	adc_enable();

    adc_set_reference(AVCC);

    adc_set_prescaller(DIVISION_BY_128);
}

void adc_init(ReferenceSelection refSelector, PrescallerSelection prescallerSelect)
{
	adc_enable();

    adc_set_reference(refSelector);

    adc_set_prescaller(prescallerSelect);
}

void adc_param_init(ReferenceSelection refSelector, uint8_t adcLeftAdjust, PrescallerSelection prescallerSelect,
         uint8_t interrupt, void (*callback)(), uint8_t autoTrigger, uint8_t analogComparator, AutoTriggerSource autoTriggerSource)
{
	adc_enable();

    adc_set_reference(refSelector);

    adc_set_left_adjust_result(adcLeftAdjust);

    adc_set_prescaller(prescallerSelect);

    adc_set_interrupt(interrupt);

    adc_register_callback(callback);

    adc_set_auto_trigger_enable(autoTrigger);

    adc_set_analog_comparator_multiplexer(analogComparator);

    adc_set_auto_trigger_source(autoTriggerSource);
}

uint16_t adc_single_read(InputChannelSelection inputChannel)
{	
    // Clear older channel
    ADMUX &= 0xF0;
	
	//Select ADC channel
	ADMUX |= ((int)inputChannel << MUX0);

	// Single conversion mode
	ADCSRA |= (1<<ADSC);
	
	// Wait until ADC conversion is complete
	while(!(ADCSRA & (1 << ADSC)));
	
	// Reset as required
	ADCSRA |= (1 << ADIF);
	
	return ADCW;
}

uint16_t adc_average_single_read(InputChannelSelection inputChannel, int numberOfSamplesToAverage)
{
    uint16_t adcVal = 0;
	uint16_t adcValTotal = 0;
	adc_single_read(inputChannel); //first throw-away read
	
	// Read n sample values from the ADC and average them out
	for(int i = 0; i < numberOfSamplesToAverage; ++i)
	{
		adcValTotal += adc_single_read(inputChannel);
	}
	
	adcVal = adcValTotal / numberOfSamplesToAverage;
	return adcVal;
}
void adc_disable_all_digital_input_registers(void)
{
    DIDR0 |= (31 << ADC0D);
}

void adc_enable_all_digital_input_registers(void)
{
    DIDR0 = 0x00000;
}

float adc_get_on_chip_temperature(void)
{
	// TODO
    return 0;
}

void adc_register_callback(void (*callback)())
{
    adcInterruptFunction = callback;
}

void adc_deregister_callback(void)
{
    adcInterruptFunction = 0;
}

ISR(ADC_vect)
{
    if(adcInterruptFunction != 0)
        adcInterruptFunction();
}
