/**
 * Music Psychology Toolbox (MPT)
 * 
 * Copyright (c) 2018 Christopher Fust
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

#include "TimerOne.h"

bool newData = false;
int air1, air2, air3, pulse;
int sync = 0;
int buttonState = 0;
int timestamp;

// Comment this out to deactivate the airflow collection.
#define AIRFLOW_SENSOR

// Comment this out to deactivate the pulse collection.
#define PULSE_SENSOR

/**
 * 1s  = 1000ms
 * 1s  = 1000,000us 
 * 1ms = 1000us
 * 
 * for a 10ms  measurement interval set interrupt to 10 000us => 100 reads/s
 * for a 50ms  measurement interval set interrupt to 50 000us => 20 reads/s
 * for a 100ms measurement interval set interrupt to 100 000us => 10 reads/s
 */
unsigned long sample_rate_us = 10000;

/**
 * Change TIME_MS_INTERVAL according to sample_rate_us.
 */
#define TIME_MS_INTERVAL  10

/**
 * Time ms counter.
 */
unsigned long time_ms = 0;

void setup() {
  Timer1.initialize(sample_rate_us);
  Timer1.attachInterrupt(getData);
  Serial.begin(115200);
  pinMode(3, INPUT);
  pinMode(9, OUTPUT);

  // interrupt test pin/oscilloscope
  pinMode(13, OUTPUT);

  // prevent disruptive default interrupt
  cli(); // disable interrupts
  TIMSK0 &= ~(1 << TOIE0);
  sei(); // enable interrupts
}

void getData() {
  // toggle pin to meassure interval issues
  PINB |= 1 << PORTB5; 
  
  time_ms += TIME_MS_INTERVAL;
  
  /**
   * Accoding to the Arduino documentation a analog read takes about 100us which is
   * 1s = 1000 000us / 100us = 10 000 reads/s
   * 
   * https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
   */
#ifdef AIRFLOW_SENSOR
  air1 = analogRead(A0); // 100us
  air2 = analogRead(A1); // 100us
  air3 = analogRead(A2); // 100us
#endif
#ifdef PULSE_SENSOR
  pulse = analogRead(A3); // 100us => 500us => 0.0001s
#endif
  newData = true;
}

// TODO CH reset time_ms on sync?
void loop() {
  buttonState = digitalRead(3);
  if (buttonState){
    digitalWrite(9, HIGH); 
    sync = -1;
  }
  else{
    digitalWrite(9, LOW);
    sync = 0;
  }
  if (newData) {
    newData = false;
    Serial.print(time_ms);
    Serial.print(",");
    Serial.print(sync);
#ifdef AIRFLOW_SENSOR
    Serial.print(",");
    Serial.print(air1);
    Serial.print(",");
    Serial.print(air2);
    Serial.print(",");
    Serial.print(air3);
#endif
#ifdef PULSE_SENSOR
    Serial.print(",");
    Serial.print(pulse);
#endif
    Serial.println();
  }
}
