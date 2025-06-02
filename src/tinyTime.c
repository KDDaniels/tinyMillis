// SPDX-FileCopyrightText: 2025 Kendall Daniels <kendall.daniels.dev@gmail.com>
// SPDX-License-Identifier: MIT

#include "tinyTime.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
VECT - overflow vector
TREG - timer register
CLKS - clock select
IREG - interrupt register
OVFI - overflow interrupt
IFR  - Interrupt flag register
TOF  - Timer overflow flag
*/

#if defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny24__)
    #define VECT TIM0_OVF_vect
    #define TREG TCCR0B
    #define CLKS CS01
    #define IREG TIMSK0
    #define OVFI TOIE0
    #define IFR  TIFR0
    #define TOF  TOV0
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny45) || defined(__AVR_ATtiny25__)
    #define VECT TIM0_OVF_vect
    #define TREG TCCR0B
    #define CLKS CS01
    #define IREG TIMSK
    #define OVFI TOIE0
    #define IFR  TIFR
    #define TOF  TOV0
#endif


volatile uint32_t _millis = 0;
volatile uint32_t _1000us = 0;
volatile uint32_t _tOflow = 0;

ISR(VECT)
{
    _tOflow++;
    _1000us += 256;
    while (_1000us > 1000)
    {
        _millis++;
        _1000us -= 1000;
    }
}

void initTimer0(void) __attribute__((constructor));
void initTimer0(void)
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

uint32_t micros(void)
{
    uint32_t overflows;
    uint8_t tcount;

    cli();
    overflows = _tOflow;
    tcount = TCNT0;

    // Check if timer overflow flag is set and counter is less than max
    if ((IFR & (1 << TOF)) && (tcount < 256))
    {
        overflows++;
        tcount = TCNT0;
    }
    sei();

    return (overflows << 8) + tcount;
}
