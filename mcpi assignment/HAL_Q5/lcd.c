#include "lcd.h"
#include <string.h>

/* hi2c1 is defined in main.c */
extern I2C_HandleTypeDef hi2c1;


/*-----------------------------------------------------------
 * Send one byte to PCF8574
 *----------------------------------------------------------*/
void PCF8574_Write(uint8_t val)
{
    HAL_I2C_Master_Transmit(
        &hi2c1,
        PCF8574_ADDR,
        &val,
        1,
        HAL_MAX_DELAY
    );
}


/*-----------------------------------------------------------
 * Write 4-bit data to LCD
 *----------------------------------------------------------*/
void lcd_write_nibble(uint8_t rs, uint8_t data)
{
    uint8_t val = 0;

    /*
     * Put 4-bit data on PCF8574 P4-P7
     */
    val |= (data & 0x0F) << 4;

    /*
     * RS = 0 -> Command
     * RS = 1 -> Data
     */
    if (rs)
    {
        val |= (1 << LCD_RS);
    }

    /*
     * Backlight ON
     */
    val |= (1 << LCD_BL);

    /*
     * Enable = 1
     */
    val |= (1 << LCD_EN);

    PCF8574_Write(val);

    /*
     * Enable pulse
     */
    HAL_Delay(1);

    /*
     * Enable = 0
     */
    val &= ~(1 << LCD_EN);

    PCF8574_Write(val);

    HAL_Delay(1);
}


/*-----------------------------------------------------------
 * Send command to LCD
 *----------------------------------------------------------*/
void lcd_send_cmd(uint8_t cmd)
{
    /*
     * Send upper 4 bits
     */
    lcd_write_nibble(LCD_CMD, (cmd >> 4) & 0x0F);

    /*
     * Send lower 4 bits
     */
    lcd_write_nibble(LCD_CMD, cmd & 0x0F);

    HAL_Delay(2);
}


/*-----------------------------------------------------------
 * Send data/character to LCD
 *----------------------------------------------------------*/
void lcd_send_data(uint8_t data)
{
    /*
     * Send upper 4 bits
     */
    lcd_write_nibble(LCD_DATA, (data >> 4) & 0x0F);

    /*
     * Send lower 4 bits
     */
    lcd_write_nibble(LCD_DATA, data & 0x0F);
}


/*-----------------------------------------------------------
 * Initialize LCD
 *----------------------------------------------------------*/
void lcd_init(void)
{
    /*
     * Wait for LCD power-up
     */
    HAL_Delay(20);

    /*
     * LCD initialization sequence
     *
     * LCD starts in 8-bit mode.
     * These commands make it enter 4-bit mode.
     */

    lcd_write_nibble(LCD_CMD, 0x03);

    HAL_Delay(5);

    lcd_write_nibble(LCD_CMD, 0x03);

    HAL_Delay(1);

    lcd_write_nibble(LCD_CMD, 0x03);

    HAL_Delay(1);

    /*
     * Change LCD to 4-bit mode
     */
    lcd_write_nibble(LCD_CMD, 0x02);

    HAL_Delay(1);


    /*
     * Function Set
     *
     * 0x28:
     * 4-bit mode
     * 2 lines
     * 5x8 character font
     */
    lcd_send_cmd(0x28);


    /*
     * Display ON
     * Cursor OFF
     * Blink OFF
     */
    lcd_send_cmd(0x0C);


    /*
     * Clear display
     */
    lcd_send_cmd(0x01);

    HAL_Delay(2);


    /*
     * Entry mode
     *
     * Cursor moves right
     */
    lcd_send_cmd(0x06);
}


/*-----------------------------------------------------------
 * Clear LCD
 *----------------------------------------------------------*/
void lcd_clear(void)
{
    lcd_send_cmd(0x01);

    HAL_Delay(2);
}


/*-----------------------------------------------------------
 * Set cursor position
 *
 * row = 0 -> first line
 * row = 1 -> second line
 *
 * col = 0 to 15
 *----------------------------------------------------------*/
void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    if (row == 0)
    {
        address = 0x80 + col;
    }
    else
    {
        address = 0xC0 + col;
    }

    lcd_send_cmd(address);
}


/*-----------------------------------------------------------
 * Print string on LCD
 *----------------------------------------------------------*/
void lcd_print(char *str)
{
    while (*str)
    {
        lcd_send_data(*str);

        str++;
    }
}
