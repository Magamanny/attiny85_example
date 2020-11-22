/*
 * attiny85_blink.c
 *
 * Created: 3/21/2018 7:38:54 PM
 * Author : Manny
 */ 
#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 0x01;
    while (1) 
    {
		_delay_ms(200);
		PORTB |= 1 << PB0;
		_delay_ms(200);
		PORTB &= ~(1 << PB0);
    }
}

