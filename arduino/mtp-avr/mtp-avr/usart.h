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
#ifndef USART_H_
#define USART_H_

#define BAUD    250000

// USART Baud Rate Register
#define MYUBRR  F_CPU/16/BAUD-1

void USART_init(unsigned int ubrr);

void USART_transmit(unsigned char data);

void println(int value);

#endif /* USART_H_ */
