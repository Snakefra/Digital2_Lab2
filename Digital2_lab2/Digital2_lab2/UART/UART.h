
/*
 * UART.h
 *
 * Created: 25/07/2024 12:41:05
 *  Author: Snake
 */ 
#ifndef UART_H
#define UART_H

#include <avr/io.h>

void uart_init(unsigned int baud);
void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void uart_print(const char *str);

#endif
