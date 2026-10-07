#ifndef LCD_H
#define LCD_H

#include "main.h"

/* PCF8574 I2C LCD Address */
#define PCF8574_ADDR    (0x27 << 1)

/* LCD Commands */
#define LCD_CMD         0
#define LCD_DATA        1

/* LCD pins connected to PCF8574 */
#define LCD_RS          0
#define LCD_EN          2
#define LCD_BL          3

/* LCD Functions */

void lcd_init(void);

void lcd_clear(void);

void lcd_set_cursor(uint8_t row, uint8_t col);

void lcd_print(char *str);

void lcd_write_nibble(uint8_t rs, uint8_t data);

void lcd_send_cmd(uint8_t cmd);

void lcd_send_data(uint8_t data);

#endif
