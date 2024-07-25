
/*
 * UART.c
 *
 * Created: 25/07/2024 12:41:14
 *  Author: Snake
 */ 
#define F_CPU 16000000UL
#include "UART.h"

void uart_init(unsigned int baud) {
	unsigned int ubrr = F_CPU/16/baud-1;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Habilitar recepción y transmisión
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configurar 8 bits de datos
}

void uart_transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0))); // Esperar a que el buffer esté vacío
	UDR0 = data; // Enviar el dato
}

unsigned char uart_receive(void) {
	while (!(UCSR0A & (1 << RXC0))); // Esperar a que se reciba el dato
	return UDR0; // Leer el dato recibido
}

void uart_print(const char *str) {
	while (*str) {
		uart_transmit(*str++);
	}
}
