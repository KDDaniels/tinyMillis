// SPDX-FileCopyrightText: 2025 Kendall Daniels <kendall.daniels.dev@gmail.com>
// SPDX-License-Identifier: MIT

#include "tinyMillis.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
VECT - overflow vector
TREG - timer register
CLKS - clock select
IREG - interrupt register
OVFI - overflow interrupt
*/

#if defined(__AVR_ATtiny84__)
    #define VECT TIM0_OVF_vect
    #define TREG TCCR0B
    #define CLKS CS01
    #define IREG TIMSK0
    #define OVFI TOIE0
#elif defined(__AVR_ATtiny85__)
    #define VECT TIM0_OVF_vect
    #define TREG TCCR0B
    #define CLKS CS01
    #define IREG TIMSK
    #define OVFI TOIE0
#endif


volatile uint32_t _millis = 0;
volatile uint32_t _1000us = 0;

ISR(VECT)
{
    _1000us += 256;
    while (_1000us > 1000)
    {
        _millis++;
        _1000us -= 1000;
    }
}

void initMillis(void) __attribute__((constructor));
void initMillis(void)
{
    // setting prescaler to CLK / 8 (8MHz/8 = 1MHz)
    TREG |= (1<<CLKS);

    // enable overflow interrupt
    IREG |= (1<<OVFI);

    sei();
}

uint32_t millis(void)
{
    uint32_t m;
    cli();
    m = _millis;
    sei();
    return m;
}
