/*
 * Music Psychology Toolbox (MPT)
 *
 * Copyright (c) 2018-2019 Christopher Fust
 * Copyright (c) 2018-2019 Alexander Fust
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
#include <avr/io.h>
#include <avr/interrupt.h>

// Comment this out to deactivate PIN13 debug toggeling.
// This pin is used to meassure interval timing issues.
//#define TOGGLE_PIN_ON_INTERRUPT

bool newData = false;

/**
 * 1s  = 1000ms
 * 1s  = 1000,000us
 * 1ms = 1000us
 *
 * for a   1ms measurement interval set interrupt to    1000us => 1000 Hz
 * for a  10ms measurement interval set interrupt to  10'000us =>  100 Hz
 * for a  50ms measurement interval set interrupt to  50'000us =>   20 Hz
 * for a 100ms measurement interval set interrupt to 100'000us =>   10 Hz
 *
 * Change TIME_MS_INTERVAL according to the target sample rate (dT).
 */
#define TIME_MS_INTERVAL  1UL

/**
 * initcnt = maxcnt - dT * cpufreq / prescale
 * initcnt = 65536 - 0.001 * 16,000,000 / 64 = 250
 */
#define TCNT1_START 250

/**
 * Time ms counter.
 */
unsigned long time_ms = 0;

ISR(TIMER1_OVF_vect)
{
  TCNT1 = TCNT1_START;

#ifdef TOGGLE_PIN_ON_INTERRUPT
  PINB |= 1 << PORTB5;
#endif

  time_ms += TIME_MS_INTERVAL;

  newData = true;
}

void setup() {
  Serial.begin(115200);

#ifdef TOGGLE_PIN_ON_INTERRUPT
  pinMode(13, OUTPUT);
#endif

  cli(); // disable interrupts
  // prevent disruptive default interrupt
  TIMSK0 &= ~(1 << TOIE0);

  // Setup interrupt one
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = TCNT1_START;
  TCCR1B = (1 << CS11) | (1<<CS10);
  TIMSK1 |= (1 << TOIE1);
  sei(); // enable interrupts
}

void loop() {
  if (newData) {
    Serial.println(time_ms);
    newData = false;
  }
}
