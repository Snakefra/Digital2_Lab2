
/*
 * LCD.h
 *
 * Created: 19/07/2024 10:57:30
 *  Author: Snake
 */

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>

#define LCD_RS PB0
#define LCD_E  PB1
#define LCD_D0 PC0
#define LCD_D1 PC1
#define LCD_D2 PD2
#define LCD_D3 PD3
#define LCD_D4 PD4
#define LCD_D5 PD5
#define LCD_D6 PD6
#define LCD_D7 PD7
#define LCD_BACKLIGHT PB2

void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_set_cursor(unsigned char row, unsigned char col);
void lcd_print(const char *str);
void lcd_backlight_on(void);
void lcd_backlight_off(void);

#endif
