/*
 * Music Psychology Toolbox (MPT)
 * 
 * Copyright (c) 2018 Alexander Fust
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * This program is free software: you can redistribute it and/or modify
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// Oscillator frequency of micro controller on Arduino board is 16MHz
#define F_CPU   16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "usart.h"

bool newData = false;

#define TCNT1_START 49536

int value;
uint8_t low, high;
ISR(TIMER1_OVF_vect)
{
	/*PINB |= 1 << PORTB5;*/
	if (newData) return;
	
	low = ADCL;
 	high = ADCH;
	
	newData = true;
	TCNT1 = TCNT1_START;
}

// ISR(ADC_vect)
// {
// 	if (newData) return;
// 	low = ADCL;
// 	high = ADCH;
// 	newData = true;
// }

void init(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = TCNT1_START;
	TCCR1B |= /*(1 << CS11) |*/ (1 << CS10);
	TIMSK1 |= (1 << TOIE1);
	
	ADMUX |= (1 << REFS0);// | (1 << MUX2);
	ADCSRA |= (1 << ADEN) | (1 << ADSC) /*| (1 << ADIE)*/ | (1 << ADATE) | (1 << ADPS2);
	
	USART_init(MYUBRR);
	/*DDRB |= (1 << DDB5);*/
	
	sei();
}

int main(void)
{
	init();
	
    while (1) 
    {
		_delay_us(10);
		if (newData)
		{
			println((high << 8) | low);
			newData = false;
		}
    }
}

