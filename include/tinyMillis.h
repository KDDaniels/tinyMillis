// SPDX-FileCopyrightText: 2025 Kendall Daniels <kendall.daniels.dev@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef ARDUINO
    #define USE_CUSTOM
#endif

#ifdef USE_CUSTOM
    #ifndef TINYMILLIS_H
    #define TINYMILLIS_H

    #include <stdint.h>

    #ifdef __cplusplus
    extern "C" {
    #endif

    void initMillis(void);
    uint32_t millis(void);

    #ifdef __cplusplus
    }
    #endif
    #endif
#endif