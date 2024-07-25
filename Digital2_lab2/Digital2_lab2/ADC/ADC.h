
/*
 * ADC.h
 *
 * Created: 25/07/2024 13:08:24
 *  Author: Snake
 */ 
#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void adc_init(void);
uint16_t adc_read(uint8_t ch);
float convertir_a_voltios(uint16_t valor_adc);

#endif
