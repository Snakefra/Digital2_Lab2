//****************************************************************************
// Universidad del Valle de Guatemala
// IE3054: Electronica Digital 2
// Autor: Oscar Melchor
// Proyecto: Pantalla LCD
// Archivo: Digital2_lab2.c
// Hardware : ATMEGA328P
// Created: 19/07/2024 10:56:01
//****************************************************************************
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "LCD/LCD.h"
#include "ADC/ADC.h"
#include "UART/UART.h"

void float_to_string(float value, char *buffer);

void setup() {
	UCSR0B = 0; // Apagar el registro UCSR0B

	lcd_init();
	lcd_backlight_on();
	adc_init();
	uart_init(9600); // Configurar UART a 9600 baudios
}

int main(void) {
	setup();

	int contador = 0; // Inicializar el contador

	while (1) {
		uint16_t pot1_value = adc_read(6); // Leer valor del potenciometro 1 (A6)
		float pot1_voltios = convertir_a_voltios(pot1_value);

		uint16_t pot2_value = adc_read(7); // Leer valor del potenciometro 2 (A7)
		float pot2_voltios = convertir_a_voltios(pot2_value);

		char buffer[8];
		
		lcd_set_cursor(0, 0);
		lcd_print("S1:   S2:   S3:");

		lcd_set_cursor(1, 0);
		float_to_string(pot1_voltios, buffer);
		lcd_print(buffer);

		lcd_set_cursor(1, 6);
		float_to_string(pot2_voltios, buffer);
		lcd_print(buffer);

		lcd_set_cursor(1, 12);
		char contador_str[4];
		itoa(contador, contador_str, 10); // Convertir el contador a cadena
		lcd_print(contador_str); // Mostrar el valor del contador en el LCD

		// Enviar valores por UART
		uart_print("S1:");
		float_to_string(pot1_voltios, buffer);
		uart_print(buffer);
		uart_transmit(' ');

		uart_print("S2:");
		float_to_string(pot2_voltios, buffer);
		uart_print(buffer);
		uart_transmit('\n');

		// Leer datos recibidos por UART
		if (UCSR0A & (1 << RXC0)) {
			unsigned char received = uart_receive();
			if (received == '+') {
				contador++;
				} else if (received == '-') {
				contador--;
			}
		}

		_delay_ms(500); // Esperar medio segundo
	}

	return 0;
}

void float_to_string(float value, char *buffer) {
	int int_part = (int)value;
	int frac_part = (int)((value - int_part) * 100); // Obtener dos dígitos decimales

	if (int_part >= 100) {
		buffer[0] = (int_part / 100) + '0';
		buffer[1] = ((int_part / 10) % 10) + '0';
		buffer[2] = (int_part % 10) + '0';
		buffer[3] = '.';
		buffer[4] = (frac_part / 10) + '0';
		buffer[5] = (frac_part % 10) + '0';
		buffer[6] = 'V';
		buffer[7] = '\0'; // Terminar la cadena
		} else if (int_part >= 10) {
		buffer[0] = (int_part / 10) + '0';
		buffer[1] = (int_part % 10) + '0';
		buffer[2] = '.';
		buffer[3] = (frac_part / 10) + '0';
		buffer[4] = (frac_part % 10) + '0';
		buffer[5] = 'V';
		buffer[6] = '\0'; // Terminar la cadena
		} else {
		buffer[0] = int_part + '0';
		buffer[1] = '.';
		buffer[2] = (frac_part / 10) + '0';
		buffer[3] = (frac_part % 10) + '0';
		buffer[4] = 'V';
		buffer[5] = '\0'; // Terminar la cadena
	}
}
