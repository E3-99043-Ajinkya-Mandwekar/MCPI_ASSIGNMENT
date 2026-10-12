
#ifndef LED_H
#define LED_H

#include<stdint.h>
#include<stm32f4xx.h>
#include<stm32f407xx.h>

void Init();
void Led_Toggle(int);

#define GREEN 12
#define ORANGE  13
#define RED 14
#define BLUE 15

#endif
