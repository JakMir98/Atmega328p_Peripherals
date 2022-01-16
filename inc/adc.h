/*
 * adc.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/**************************************************************************************\
* Custom datatypes
\**************************************************************************************/
typedef enum 
{
    EXTERNAL = 0,
    AVCC = 1,
    INTERNAL_1_1V = 3
} ReferenceSelection;

typedef enum 
{
    ADC5 = 0,
    ADC0 = 1,
    ADC1 = 2,
    ADC2 = 3,
    ADC3 = 4,
    ADC4 = 5
} InputChannelSelection;

typedef enum 
{
    DIVISION_BY_2 = 0,
    DIVISION_BY_4 = 2,
    DIVISION_BY_8 = 3,
    DIVISION_BY_16 = 4,
    DIVISION_BY_32 = 5,
    DIVISION_BY_64 = 6,
    DIVISION_BY_128 = 7
} PrescallerSelection;

typedef enum 
{
    FREE_RUNNING_MODE = 0,
    ANALOG_COMPARATOR = 1,
    EXTERNAL_INTERRUPT_REQUEST0 = 2,
    TIMER0_COMPARE_MATCH_A = 3,
    TIMER0_OVERFLOW = 4,
    TIMER1_COMPARE_MATCH_B = 5,
    TIMER1_OVERFLOW = 6,
    TIMER1_CAPTURE_EVENT = 7,
} AutoTriggerSource;

/**************************************************************************************\
* Prototypes
\**************************************************************************************/
void adc_set_reference(ReferenceSelection reference);
void adc_set_left_adjust_result(uint8_t adcLeftAdjustResult);
void adc_set_prescaller(PrescallerSelection inputChannel);
void adc_set_interrupt(uint8_t interrupt);
void adc_set_auto_trigger_enable(uint8_t autoTrigger);
void adc_set_analog_comparator_multiplexer(uint8_t analogCompEna);
void adc_set_auto_trigger_source(AutoTriggerSource autoTrigger);
void adc_enable(void);
void adc_disable(void);

void adc_default_init(void);
void adc_init(ReferenceSelection refSelector, PrescallerSelection prescallerSelect);
void adc_param_init(ReferenceSelection refSelector, uint8_t adcLeftAdjust, PrescallerSelection prescallerSelect,
         uint8_t interrupt, void (*callback)(), uint8_t autoTrigger, uint8_t analogComparator, AutoTriggerSource autoTriggerSource);
uint16_t adc_single_read(InputChannelSelection inputChannel);
uint16_t adc_average_single_read(InputChannelSelection inputChannel, int numberOfSamplesToAverage);
void adc_disable_all_digital_input_registers();
void adc_enable_all_digital_input_registers();
float adc_get_on_chip_temperature(void);

void adc_register_callback(void (*callback)());
void adc_deregister_callback(void);

#endif /* ADC_H_ */
