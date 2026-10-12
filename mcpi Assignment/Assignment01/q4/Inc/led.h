
#ifndef LED_H
#define LED_H

#include<stdint.h>
#include<stm32f4xx.h>
#include<stm32f407xx.h>

void Init();
void Switch();
void Led_Pattern(uint8_t);

#endif
