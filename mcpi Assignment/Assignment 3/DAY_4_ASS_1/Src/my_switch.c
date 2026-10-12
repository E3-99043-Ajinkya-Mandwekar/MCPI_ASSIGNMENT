/*
 * my_switch.c
 *
 *  Created on: 14-Sept-2026
 *      Author: pranav
 */

#include "my_switch.h"

void switch_init()
{
	RCC->AHB1ENR |= BV(0);

	GPIOA->MODER &= ~( BV(0) | BV(1));

	GPIOA->OTYPER &= ~BV(0); 

	GPIOA->OSPEEDR &= ~( BV(0) | BV(1));

	GPIOA->PUPDR &= ~( BV(0) | BV(1));
}
