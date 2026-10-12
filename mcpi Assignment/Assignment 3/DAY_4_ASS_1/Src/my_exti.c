/*
 * my_exti.c
 *
 *  Created on: 14-Sept-2026
 *      Author: pranav
 */

#include"my_switch.h"
#include "my_led.h"
#include "my_exti.h"

extern volatile uint16_t flag;

void init_exti0_switch()
{
	switch_init();

	RCC->APB2ENR |= BV(14);

	EXTI->FTSR |= BV(0);

	EXTI->RTSR &= ~BV(0);

	SYSCFG->EXTICR[0] &= ~ ( BV(0) | BV(1) | BV(2) | BV(3) );

	EXTI->IMR |= BV(0);

	NVIC_EnableIRQ(6);
}

void EXTI0_IRQHandler()
{
	EXTI->PR |= BV(0);

	flag = 1; 
}

