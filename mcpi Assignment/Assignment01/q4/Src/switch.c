

#include "led.h"
void Switch()
{
	RCC -> AHB1ENR |= BV(0);
	GPIOA -> MODER &= ~(BV(1) | BV(0));
	GPIOA -> OTYPER &= ~(BV(0));
	GPIOA -> OSPEEDR &= ~(BV(1) | BV(0));
	GPIOA -> PUPDR &= ~(BV(1) | BV(0));
}

void Init()
{
	RCC -> AHB1ENR |= BV(3);
	GPIOD -> MODER |= (BV(24) | BV(26) | BV(28) | BV(30) );
	GPIOD -> MODER &= ~(BV(25) | BV(27) | BV(29) | BV(31) );
	GPIOD -> OTYPER &= ~(BV(12) | BV(13) | BV(14) | BV(15) );
	GPIOD -> PUPDR &= ~(BV(24) | BV(25) | BV(26) | BV(27) | BV(28) | BV(29) | BV(30) |BV(31) );
	GPIOD -> OSPEEDR &= ~(BV(24) | BV(25) | BV(26) | BV(27) | BV(28) | BV(29) | BV(30) | BV(31) );
}

void Led_Pattern(uint8_t Data)
{
	uint8_t bit;
	uint8_t Led = 12;
	while(Led < 16)
	{
		bit = Data & 1;
		if(bit == 1)
			GPIOD -> ODR |= BV(Led);
		else
			GPIOD -> ODR &= ~(BV(Led));

		Data = Data >> 1;
		Led++;
	}
}
