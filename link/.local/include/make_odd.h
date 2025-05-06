// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Make packed unsigned integers odd
/**
\file
\author Steven Ward
*/

#pragma once

#include <immintrin.h>

/// Make the packed unsigned 8-bit integers odd
inline __m128i
make_odd_epu8(const __m128i a)
{
    return _mm_or_si128(a, _mm_set1_epi8(1));
}

/// Make the packed unsigned 16-bit integers odd
inline __m128i
make_odd_epu16(const __m128i a)
{
    return _mm_or_si128(a, _mm_set1_epi16(1));
}

/// Make the packed unsigned 32-bit integers odd
inline __m128i
make_odd_epu32(const __m128i a)
{
    return _mm_or_si128(a, _mm_set1_epi32(1));
}

/// Make the packed unsigned 64-bit integers odd
inline __m128i
make_odd_epu64(const __m128i a)
{
    return _mm_or_si128(a, _mm_set1_epi64x(1));
}
