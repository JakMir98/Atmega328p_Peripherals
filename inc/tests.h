/*
 * tests.h
 *
 * Created: 14.01.2022 17:00:35
 *  Author: Admin
 */ 

#ifndef TESTS_H_
#define TESTS_H_

typedef enum
{
	FIRST_TEST,
	SECOND_TEST,
	THIRD_TEST
} TestType;

void gpio_test();
void adc_test(TestType testType);
void i2c_test();
void sleepModes_test();
void spi_test();
void usart_test(TestType testType);
void timers_test();

#endif /* TESTS_H_ */