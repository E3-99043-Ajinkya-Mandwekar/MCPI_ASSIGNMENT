/*
 * accel_init.c
 *
 *  Created on: 30-Sept-2026
 *      Author: pranav
 */

#include "accel_init.h"

extern SPI_HandleTypeDef hspi1;

void Accel_Write(uint8_t int_addr, uint8_t data[], uint8_t size) {
	// enable slave PE.3 = 0
	HAL_GPIO_WritePin(ACCEL_CE_GPIO, ACCEL_CE_GPIO_PIN, GPIO_PIN_RESET);
	// for write: internal addr MSB (7th bit) should be 0
	int_addr &= ~(1 << 7);
	// transmit internal address
	HAL_SPI_Transmit(&hspi1, &int_addr, 1, HAL_MAX_DELAY);
	// transmit the data
	HAL_SPI_Transmit(&hspi1, data, size, HAL_MAX_DELAY);
	// disable slave PE.3 = 1
	HAL_GPIO_WritePin(ACCEL_CE_GPIO, ACCEL_CE_GPIO_PIN, GPIO_PIN_SET);
}

void Accel_Read(uint8_t int_addr, uint8_t data[], uint8_t size) {
	// enable slave PE.3 = 0
	HAL_GPIO_WritePin(ACCEL_CE_GPIO, ACCEL_CE_GPIO_PIN, GPIO_PIN_RESET);
	// for write: internal addr MSB (7th bit) should be 1
	int_addr |= (1 << 7);
	// transmit internal address
	HAL_SPI_Transmit(&hspi1, &int_addr, 1, HAL_MAX_DELAY);
	// transmit the data
	HAL_SPI_Receive(&hspi1, data, size, HAL_MAX_DELAY);
	// disable slave PE.3 = 1
	HAL_GPIO_WritePin(ACCEL_CE_GPIO, ACCEL_CE_GPIO_PIN, GPIO_PIN_SET);
}

void Accel_Init(void) {
	// config cr4 -- enable XYZ axes and set odr
	uint8_t cr4_val = ACCEL_CR4_XYZEN | ACCEL_CR4_ODR25;
	Accel_Write(ACCEL_CR4, &cr4_val, 1);
}

void Accel_WaitForReading(void) {
	// wait until status regr XYZDA become 1.
	uint8_t sr_val;
	do {
		Accel_Read(ACCEL_STATUS, &sr_val, 1);
	}while( (sr_val & ACCEL_SR_XYZDA) == 0 );
}

AccelReading_t Accel_GetReading(void) {
	uint8_t data[2];
	AccelReading_t val;
	// wait for reading
	Accel_WaitForReading();
	// read xl & xh and make x reading
	Accel_Read(ACCEL_XL, data, 2);
	val.x = ((uint16_t)data[1] << 8) | data[0];
	// read yl & yh and make y reading
	Accel_Read(ACCEL_YL, data, 2);
	val.y = ((uint16_t)data[1] << 8) | data[0];
	return val;
}
