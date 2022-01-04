#include "/Projekty/C(C++) projects/AVR projects/Atmega328p_Peripherals/Atmega328p_Peripherals/inc/adc.h"

void ADC_init()
{
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	
	// Set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t ADC_read(uint8_t ADCchannel)
{
	// Select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	
	// Single conversion mode
	ADCSRA |= (1<<ADSC);
	
	// Wait until ADC conversion is complete
	while(!(ADCSRA & (1 << ADIF)));
	
	// Reset as required
	ADCSRA |= (1 << ADIF);
	
	return ADC;
}

uint16_t ADC_average_read(uint8_t ADCchannel)
{
	uint16_t adcVal = 0;
	uint16_t adcValTotal = 0;
	ADC_read(ADCchannel); //first throw-away read
	
	// Read n sample values from the ADC and average them out
	for(int i = 0; i < ADC_SAMPLES; ++i)
	{
		adcValTotal += ADC_read(ADCchannel);
	}
	
	adcVal = adcValTotal / ADC_SAMPLES;
	return adcVal;
}
