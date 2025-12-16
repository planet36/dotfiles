// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Create a bitmask with one bit set
/**
* \file
* \author Steven Ward
*/

#pragma once

#if defined(DEBUG)
#include <assert.h>
#endif
#if defined(__x86_64__)
#include <immintrin.h>
#endif
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SSE2__)
/// Create a bitmask of a \c __m128i with bit \a bit set
/**
* \pre \a bit < 128
*/
static inline __m128i
mm_bitmask(const unsigned int bit)
{
#if defined(DEBUG)
    assert(bit < 128);
#endif

    uint64_t vals[sizeof(__m128i)/sizeof(uint64_t)] = {0};

    const unsigned int lane = bit / 64;
    const unsigned int shift = bit % 64;

    vals[lane] = UINT64_C(1) << shift;

    return _mm_set_epi64x(vals[1], vals[0]);
}
#endif

#if defined(__AVX__)
/// Create a bitmask of a \c __m256i with bit \a bit set
/**
* \pre \a bit < 256
*/
static inline __m256i
mm_bitmask256(const unsigned int bit)
{
#if defined(DEBUG)
    assert(bit < 256);
#endif

    uint64_t vals[sizeof(__m256i)/sizeof(uint64_t)] = {0};

    const unsigned int lane = bit / 64;
    const unsigned int shift = bit % 64;

    vals[lane] = UINT64_C(1) << shift;

    return _mm256_set_epi64x(vals[3], vals[2], vals[1], vals[0]);
}
#endif

#if defined(__AVX512F__)
/// Create a bitmask of a \c __m512i with bit \a bit set
/**
* \pre \a bit < 512
*/
static inline __m512i
mm_bitmask512(const unsigned int bit)
{
#if defined(DEBUG)
    assert(bit < 512);
#endif

    uint64_t vals[sizeof(__m512i)/sizeof(uint64_t)] = {0};

    const unsigned int lane = bit / 64;
    const unsigned int shift = bit % 64;

    vals[lane] = UINT64_C(1) << shift;

    return _mm512_set_epi64(
            vals[7], vals[6], vals[5], vals[4],
            vals[3], vals[2], vals[1], vals[0]);
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif
