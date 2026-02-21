// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// MUltiply and Mix ("MUM") functions
/**
* \file
* \author Steven Ward
* \sa https://github.com/vnmakarov/mum-hash/blob/ad5658e26fa03029c436848eca25fae1a17639be/mum.h#L104
*/

#pragma once

#include <immintrin.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_mulx_u32)
// Note: _mulx_u32 is not defined if __x86_64__
// https://github.com/gcc-mirror/gcc/blob/dfe0d4389a3ce43179563a63046ad3e74d615a08/gcc/config/i386/bmi2intrin.h#L95
// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-nonnull-function-attribute
static inline unsigned int
_mulx_u32(unsigned int a, unsigned int b, unsigned int* hi) [[gnu::nonnull]]
{
    unsigned long long r = (unsigned long long)a * (unsigned long long)b;
    *hi = (unsigned int)(r >> 32);
    return (unsigned int)r;
}
#endif

/// Multiply \a a and \a b and return the XOR of the high and low parts of the product
static inline uint32_t
mumx32(uint32_t a, uint32_t b)
{
    unsigned int hi = 0;
    unsigned int lo = _mulx_u32(a, b, &hi);
    return hi ^ lo;
}

/// Multiply \a a and \a b and return the sum of the high and low parts of the product
static inline uint32_t
muma32(uint32_t a, uint32_t b)
{
    unsigned int hi = 0;
    unsigned int lo = _mulx_u32(a, b, &hi);
    return hi + lo;
}

/// Multiply \a a and \a b and return the difference of the high and low parts of the product
static inline uint32_t
mums32(uint32_t a, uint32_t b)
{
    unsigned int hi = 0;
    unsigned int lo = _mulx_u32(a, b, &hi);
    return hi - lo;
}

/// Multiply \a a and \a b and return the XOR of the high and low parts of the product
static inline uint64_t
mumx64(uint64_t a, uint64_t b)
{
    unsigned long long hi = 0; // unsigned __int64
    unsigned long long lo = _mulx_u64(a, b, &hi);
    return hi ^ lo;
}

/// Multiply \a a and \a b and return the sum of the high and low parts of the product
static inline uint64_t
muma64(uint64_t a, uint64_t b)
{
    unsigned long long hi = 0; // unsigned __int64
    unsigned long long lo = _mulx_u64(a, b, &hi);
    return hi + lo;
}

/// Multiply \a a and \a b and return the difference of the high and low parts of the product
static inline uint64_t
mums64(uint64_t a, uint64_t b)
{
    unsigned long long hi = 0; // unsigned __int64
    unsigned long long lo = _mulx_u64(a, b, &hi);
    return hi - lo;
}

#ifdef __cplusplus
} // extern "C"
#endif
