
/*
 * ADC.c
 *
 * Created: 25/07/2024 13:08:43
 *  Author: Snake
 */ 
#include "ADC.h"

void adc_init(void) {
	ADMUX = (1 << REFS0); // Referencia de voltaje AVcc
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Habilitar ADC, prescaler de 64
}

uint16_t adc_read(uint8_t ch) {
	ch &= 0x0F; // Seleccionar canal ADC entre 0 a 15
	ADMUX = (ADMUX & 0xF0) | ch; // Seleccionar el canal
	ADCSRA |= (1 << ADSC); // Iniciar la conversión
	while (ADCSRA & (1 << ADSC)); // Esperar a que termine la conversión
	return ADC;
}

float convertir_a_voltios(uint16_t valor_adc) {
	return (valor_adc / 1023.0) * 5.0;
}
