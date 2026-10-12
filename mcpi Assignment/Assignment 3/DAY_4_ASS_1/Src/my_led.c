/*
 * my_led.c
 *
 *  Created on: 13-Sept-2026
 *      Author: pranav
 */

#include"my_led.h"


void led_init()
{
	RCC->AHB1ENR |= BV(3);

	GPIOD->MODER |=  ( BV(24) | BV(26) | BV(28) | BV(30) );
	GPIOD->MODER &= ~( BV(25) | BV(27) | BV(29) | BV(31) );

	GPIOD->OSPEEDR &= ~( BV(25) | BV(27) | BV(29) | BV(31) );
	GPIOD->OSPEEDR &= ~( BV(24) | BV(26) | BV(28) | BV(30) );

	GPIOD->OTYPER &= ~( BV(12) | BV(13) | BV(14) | BV(15) );

	GPIOD->PUPDR &= ~( BV(25) | BV(27) | BV(29) | BV(31) );
	GPIOD->PUPDR &= ~( BV(24) | BV(26) | BV(28) | BV(30) );
}

void led_on_pin( uint16_t pin  )
{
	GPIOD->ODR |= BV(pin);
}

void led_off_pin( uint16_t pin  )
{
	GPIOD->ODR &= ~BV(pin);
}

