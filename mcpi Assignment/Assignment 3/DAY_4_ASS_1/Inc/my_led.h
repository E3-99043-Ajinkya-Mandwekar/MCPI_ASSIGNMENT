/*
 * my_led.h
 *
 *  Created on: 13-Sept-2026
 *      Author: kiran_z6dopa8
 */

#ifndef MY_LED_H_
#define MY_LED_H_

#include<stm32f407xx.h>
#include<stm32f4xx.h>

#define GREEN_LED 12
#define ORANGE_LED 13
#define RED_LED 14
#define BLUE_LED 15



void led_init();
void led_on_pin( uint16_t pin  );
void led_off_pin( uint16_t pin  );

#endif /* MY_LED_H_ */
