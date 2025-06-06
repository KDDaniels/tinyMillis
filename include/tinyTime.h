// SPDX-FileCopyrightText: 2025 Kendall Daniels <kendall.daniels.dev@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef ARDUINO
    #define USE_CUSTOM
#endif

#ifdef USE_CUSTOM
    #ifndef TINYTIME_H
    #define TINYTIME_H

    #include <stdint.h>

    #ifdef __cplusplus
    extern "C" {
    #endif

    void initTimer0(void);
    uint32_t millis(void);
    uint32_t micros(void);
    void delay(uint32_t d);
    void delayMicros(uint32_t d);

    #ifdef __cplusplus
    }
    #endif
    #endif
#endif