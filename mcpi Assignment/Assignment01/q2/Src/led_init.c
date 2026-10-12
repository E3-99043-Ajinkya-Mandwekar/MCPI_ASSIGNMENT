

#include "led.h"

void Init()
{
	RCC -> AHB1ENR |= BV(3);
	GPIOD -> MODER |= (BV(24) | BV(26) | BV(28) | BV(30) );
	GPIOD -> MODER &= ~(BV(25) | BV(27) | BV(29) | BV(31) );
	GPIOD -> OTYPER &= ~(BV(12) | BV(13) | BV(14) | BV(15) );
	GPIOD -> PUPDR &= ~(BV(24) | BV(25) | BV(26) | BV(27) | BV(28) | BV(29) | BV(30) |BV(31) );
	GPIOD -> OSPEEDR &= ~(BV(24) | BV(25) | BV(26) | BV(27) | BV(28) | BV(29) | BV(30) | BV(31) );
}

void Led_On(uint8_t Pin)
{
	GPIOD -> ODR |= BV(Pin);
}

void Led_Off(uint8_t Pin)
{
	GPIOD -> ODR &= ~(BV(Pin));
}
