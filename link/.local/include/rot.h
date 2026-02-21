// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Functions to rotate left and rotate right
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline uint8_t
rotl8(uint8_t x, unsigned int r)
{
    r %= 8U;
    return (r == 0) ? x : (uint8_t)((x << r) | (x >> (8U - r)));
}

static inline uint16_t
rotl16(uint16_t x, unsigned int r)
{
    r %= 16U;
    return (r == 0) ? x : (uint16_t)((x << r) | (x >> (16U - r)));
}

static inline uint32_t
rotl32(uint32_t x, unsigned int r)
{
    r %= 32U;
    return (r == 0) ? x : (uint32_t)((x << r) | (x >> (32U - r)));
}

static inline uint64_t
rotl64(uint64_t x, unsigned int r)
{
    r %= 64U;
    return (r == 0) ? x : (uint64_t)((x << r) | (x >> (64U - r)));
}

static inline uint8_t
rotr8(uint8_t x, unsigned int r)
{
    r %= 8U;
    return (r == 0) ? x : (uint8_t)((x >> r) | (x << (8U - r)));
}

static inline uint16_t
rotr16(uint16_t x, unsigned int r)
{
    r %= 16U;
    return (r == 0) ? x : (uint16_t)((x >> r) | (x << (16U - r)));
}

static inline uint32_t
rotr32(uint32_t x, unsigned int r)
{
    r %= 32U;
    return (r == 0) ? x : (uint32_t)((x >> r) | (x << (32U - r)));
}

static inline uint64_t
rotr64(uint64_t x, unsigned int r)
{
    r %= 64U;
    return (r == 0) ? x : (uint64_t)((x >> r) | (x << (64U - r)));
}

#ifdef __cplusplus
} // extern "C"
#endif
