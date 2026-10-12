
#ifndef LED_H
#define LED_H

#include<stdint.h>
#include<stm32f4xx.h>
#include<stm32f407xx.h>

void Init();
void Led_On(uint8_t);
void Led_Off(uint8_t);

#endif
