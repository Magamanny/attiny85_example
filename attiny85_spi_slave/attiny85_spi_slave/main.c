/*
 * attiny85_spi_slave.c
 *
 * Created: 3/27/2018 9:35:18 PM
 * Author : Manny
 * Demonstrate the use of spi as an spi slave device, The master is checked with SPI_MODE0 of arduino.
 * The code echoes the data recived form master in the next transition, the first transition data is 0x32
 * Corresponding arduino sketch name = "spi_master"
 * Check for both setting for slave
 * Wiring of the devices
 *  Attiny85 pin	||	Arduino Uno pin
 *	DO	(pin 6)		||	MISO	(pin 12)
 *	DI	(pin 5)		||	MOSI	(pin 11)
 *	USCK(pin 7)		||	SCK		(pin 13)
 */ 
 
//#define F_CPU 1000000L
#include <avr/io.h>
//#include <util/delay.h>
/*
#ifndef SPI_SPEED
# warning "SPI_SPEED not defined for spi.h"
#define SPI_SPEED 10
#endif
*/
void spi_begin();
void spi_trsf(int8_t);

int main(void)
{
	spi_begin();
	DDRB |= (1<<PB4);
	USIDR = 0Xfe;
	while (1)
    {
		if(USISR & (1<<USIOIF))	// data available in SPI buffer
		{
			USISR |= (1<<USIOIF);	// only be clear if it is written 1
			USIDR = USIDR; 
		}
    }
}
// OK
void spi_begin()
{
	DDRB |= (1<<PB1);	// MISO as output
	USICR |= (1<<USIWM0)|(1<<USICS1);					// shift at falling edge, SPI_MODE_0, tested OK, physical testing require
	//USICR |= (1<<USIWM0)|(1<<USICS1)|(1<<USICS0);		// shift at rising edge, SPI MODE 1
}
/*
void spi_trsf(int8_t data)
{
	USIDR |= data;
	for(int i=0;i<16;i++)
	{
		USICR |= (1<<USITC);
		USICR ^= (1<<USICLK);
		_delay_us(1000000/(2*SPI_SPEED));
	}
}
*/