/*
 * timer.h
 *
 * Created: 02.01.2022 17:14:49
 *  Author: Jakub Mirota
 */ 

#ifndef TIMER_H_
#define TIMER_H_

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

#endif /* TIMER_H_ */
