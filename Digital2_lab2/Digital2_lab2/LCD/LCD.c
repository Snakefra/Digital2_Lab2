
/*
 * LCD.c
 *
 * Created: 19/07/2024 10:57:50
 *  Author: Snake
 */ 

#include "LCD.h"

void lcd_command(unsigned char cmd) {
	PORTB &= ~(1 << LCD_RS); // RS = 0 para comandos
	PORTC = (PORTC & 0xFC) | (cmd & 0x03); // Enviar los bits 0 y 1 a PC0 y PC1
	PORTD = (PORTD & 0x03) | (cmd & 0xFC); // Enviar los bits 2 a 7 a PD2 a PD7
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_ms(2);
}

void lcd_data(unsigned char data) {
	PORTB |= (1 << LCD_RS); // RS = 1 para datos
	PORTC = (PORTC & 0xFC) | (data & 0x03); // Enviar los bits 0 y 1 a PC0 y PC1
	PORTD = (PORTD & 0x03) | (data & 0xFC); // Enviar los bits 2 a 7 a PD2 a PD7
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_ms(2);
}

void lcd_init(void) {
	DDRC |= (1 << LCD_D0) | (1 << LCD_D1); // Configurar los pines PC0 y PC1 como salidas
	DDRD |= (1 << LCD_D2) | (1 << LCD_D3) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7); // Configurar los pines PD2 a PD7 como salidas
	DDRB |= (1 << LCD_RS) | (1 << LCD_E) | (1 << LCD_BACKLIGHT); // Configurar los pines RS, E y retroiluminación como salidas
	_delay_ms(20);

	lcd_command(0x38); // Configurar el LCD en modo 8 bits, 2 líneas, 5x8
	lcd_command(0x0C); // Encender el display, sin cursor
	lcd_command(0x06); // Incrementar el cursor
	lcd_command(0x01); // Limpiar la pantalla
	_delay_ms(2);
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
	unsigned char address;
	if (row == 0) address = 0x80 + col;
	else address = 0xC0 + col;
	lcd_command(address);
}

void lcd_print(const char *str) {
	while (*str) {
		lcd_data(*str++);
	}
}

void lcd_backlight_on(void) {
	PORTB |= (1 << LCD_BACKLIGHT); // Encender la retroiluminación
}

void lcd_backlight_off(void) {
	PORTB &= ~(1 << LCD_BACKLIGHT); // Apagar la retroiluminación
}
