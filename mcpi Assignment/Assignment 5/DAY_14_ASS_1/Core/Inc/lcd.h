/*
 * lcd.h
 *
 *  Created on: 01-Oct-2026
 *      Author: pranav
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx.h"

#ifndef BV
	#define BV(n) (1 << (n))
#endif

#define PCF8574_ADDR 0x4E

#define LCD_DB4_Pos			4
#define LCD_DB5_Pos			5
#define LCD_DB6_Pos			6
#define LCD_DB7_Pos			7

#define LCD_RS_Pos		0
#define LCD_RW_Pos		1
#define LCD_EN_Pos		2
#define LCD_BL_Pos		3

#define LCD_CLEAR				0x01
#define ENTRY_MODE_SET			0x06
#define DISPLAY_ON_OFF_CONTROL	0x0C
#define FUNCTION_SET			0x28
#define LCD_LINE1				0x80
#define LCD_LINE2				0xC0

#define LCD_CMD		0
#define LCD_DATA	1

void lcd_init(void);
void lcd_write_nibble(uint8_t rs, uint8_t val);
void lcd_busy_wait(void);
void lcd_write_byte(uint8_t rs, uint8_t val);
void lcd_puts(uint8_t line, char str[]);
void lcd_shift_display(void);

void PCF8574_Write(uint8_t val);
uint8_t PCF8574_Read(void);

#endif /* INC_LCD_H_ */
