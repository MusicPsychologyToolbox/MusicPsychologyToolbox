# Arduino part of MPT

All projects below are used and tested on an Arduino Uno Rev3. The projects/sketches **mpt-avr**, **mpt-basic** and **mpt-isr** provide the same features, but they use a different set of libraries.

## mpt-avr

An Atmel Studio 7 project, which does not use Arduino libraries.

## mpt-basic

The MPT Arduino sketch using the TimerOne library (https://github.com/PaulStoffregen/TimerOne)

## mpt-isr

The MPT Arduino sketch using `ISR(TIMER1_OVF_vect)` instead of TimerOne.

## testing

A collection of test sketches.
