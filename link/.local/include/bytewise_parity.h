// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Calculate the parity of every byte in the \c uint64_t and gather the bits into a \c uint8_t result
/**
\file
\author Steven Ward
*/

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t
bytewise_parity(uint64_t x)
{
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x &= 0x0101010101010101;

    return
        (uint8_t)(x >> (0x00 - 0)) |
        (uint8_t)(x >> (0x08 - 1)) |
        (uint8_t)(x >> (0x10 - 2)) |
        (uint8_t)(x >> (0x18 - 3)) |
        (uint8_t)(x >> (0x20 - 4)) |
        (uint8_t)(x >> (0x28 - 5)) |
        (uint8_t)(x >> (0x30 - 6)) |
        (uint8_t)(x >> (0x38 - 7));
}

#ifdef __cplusplus
} // extern "C"
#endif
