/*
 * accel_init.h
 *
 *  Created on: 30-Sept-2026
 *      Author: pranav
 */

#ifndef INC_ACCEL_INIT_H_
#define INC_ACCEL_INIT_H_

#include "stm32f4xx.h"

// macros/constants for Accel.
#define ACCEL_CR4		0x20
#define ACCEL_STATUS	0x27
#define ACCEL_XL		0x28
#define ACCEL_YL		0x2A
#define ACCEL_ZL		0x2C

#define ACCEL_CR4_XYZEN		((1 << 1)|(1 << 0))
#define ACCEL_CR4_ODR25		(1 << 6)
#define ACCEL_SR_XYZDA		(1 << 3)

#define ACCEL_CE_GPIO 		GPIOE
#define ACCEL_CE_GPIO_PIN	GPIO_PIN_3

// helper struct to represent data
typedef struct AccelReading {
	int16_t x, y;
}AccelReading_t;

// functions for Accel
void Accel_Init(void);
void Accel_WaitForReading(void);
AccelReading_t Accel_GetReading(void);

void Accel_Write(uint8_t int_addr, uint8_t data[], uint8_t size);
void Accel_Read(uint8_t int_addr, uint8_t data[], uint8_t size);

#endif /* INC_ACCEL_INIT_H_ */
