/*
 * timers.h
 *
 * Created: 15.01.2022 13:29:30
 *  Author: Admin
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
/**************************************************************************************\
* Prototypes
\**************************************************************************************/

void register_timer0overflow_interrupt_function(void (*callback)());
void deregister_timer0overflow_interrupt_function(void);
void register_timer0compA_interrupt_function(void (*callback)());
void deregister_timer0compA_interrupt_function(void);
void register_timer0compB_interrupt_function(void (*callback)());
void deregister_timer0compB_interrupt_function(void);

void register_timer1overflow_interrupt_function(void (*callback)());
void deregister_timer1overflow_interrupt_function(void);
void register_timer1compA_interrupt_function(void (*callback)());
void deregister_timer1compA_interrupt_function(void);
void register_timer1compB_interrupt_function(void (*callback)());
void deregister_timer1compB_interrupt_function(void);
void register_timer1captureEvent_interrupt_function(void (*callback)());
void deregister_timer1captureEvent_interrupt_function(void);

void register_timer2overflow_interrupt_function(void (*callback)());
void deregister_timer2overflow_interrupt_function(void);
void register_timer2compA_interrupt_function(void (*callback)());
void deregister_timer2compA_interrupt_function(void);
void register_timer2compB_interrupt_function(void (*callback)());
void deregister_timer2compB_interrupt_function(void);


/**
 * @brief Periodic timer initialization overflow mode
 */
void TIMER_OVERFLOW_init();

/**
 * @brief Periodic timer initialization compare mode
 */
void TIMER_COMPARE_init();

#endif /* TIMERS_H_ */
