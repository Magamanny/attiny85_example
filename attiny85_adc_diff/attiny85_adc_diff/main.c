/*
 * attiny85_adc_diff.c
 *
 * Created: 4/5/2018 10:57:18 PM
 * Author : Manny
 *  Attiny85 pin	||	ARDUINO UNO pin
 *	DO	(pin 6)		||	MISO	(pin 12)
 *	DI	(pin 5)		||	MOSI	(pin 11)
 *	USCK(pin 7)		||	SCK		(pin 13)
 *	Demostrate the use of differentaial channel
*/
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
void spi_begin();

int main(void)
	{
	spi_begin();	// Set device as SPI slave
	USIDR = 0X32;	// load address
	ADMUX |= (1<<REFS1)|(1<<REFS2);				// set reference to 2.56V internal
	ADMUX |= (1<<ADLAR);						// Left adjust the 10-bit ADC result
	ADMUX |= (1<<MUX1)|(1<<MUX2)|(1<<MUX0);		// set channel, 20 gain ADC2 ve+ and ADC3 ve-
	ADCSRA|= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);	// ADC select clock
	//ADCSRB|= (1<<BIN);
	ADCSRA|= (1<<ADEN);							// enable ADC
	ADCSRA|= (1<<ADSC);							// start convention
	_delay_ms(100);
	while (1)
	{
		if(ADCSRA & (1<<ADIF))
		{
			int8_t adc;
			PORTB ^= (1<<PB3);
			// both the ADCL and ADCH registers must be read, other wise they will not be updated
			// read ADCL first if more then 8-bit resolution is required.
			adc	= ADCH;
			USIDR = adc;			// load data
			ADCSRA|= (1<<ADIF);		// clear flag
			ADCSRA|= (1<<ADSC);		// start next convention
		}
	}
}

// SPI in slave mode //
void spi_begin()
{
DDRB |= (1<<PB1);
USICR |= (1<<USIWM0)|(1<<USICS1);					// sample at falling edge
//USICR |= (1<<USIWM0)|(1<<USICS1)|(1<<USICS0);		// sample at rising edge
}

