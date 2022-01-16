/*
 * timers.h
 *
 * Created: 15.01.2022 13:29:30
 *  Author: Admin
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/io.h>

/**************************************************************************************\
* Private prototypes
\**************************************************************************************/
/**
 * @brief Periodic timer initialization overflow mode
 */
void TIMER_OVERFLOW_init();

/**
 * @brief Periodic timer initialization compare mode
 */
void TIMER_COMPARE_init();

#endif /* TIMERS_H_ */
