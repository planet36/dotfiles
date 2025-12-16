// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Count the number of 1-bits
/**
* \file
* \author Steven Ward
* \sa https://clang.llvm.org/docs/LanguageExtensions.html#builtin-popcountg
* \sa https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html#index-_005f_005fbuiltin_005fpopcountg
* \sa https://cppreference.com/w/cpp/numeric/popcount.html
*/

#pragma once

#if defined(__x86_64__)

#include <immintrin.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SSE4_1__)
static inline int
mm_popcount(const __m128i x)
{
    const uint64_t x0 = (uint64_t)_mm_extract_epi64(x, 0);
    const uint64_t x1 = (uint64_t)_mm_extract_epi64(x, 1);
    return __builtin_popcountg(x0) + __builtin_popcountg(x1);
}
#endif

#if defined(__AVX__)
static inline int
mm256_popcount(const __m256i x)
{
    const uint64_t x0 = (uint64_t)_mm256_extract_epi64(x, 0);
    const uint64_t x1 = (uint64_t)_mm256_extract_epi64(x, 1);
    const uint64_t x2 = (uint64_t)_mm256_extract_epi64(x, 2);
    const uint64_t x3 = (uint64_t)_mm256_extract_epi64(x, 3);
    return __builtin_popcountg(x0) + __builtin_popcountg(x1) +
           __builtin_popcountg(x2) + __builtin_popcountg(x3);
}
#endif

#if defined(__AVX512F__)
static inline int
mm512_popcount(const __m512i x)
{
    return mm256_popcount(_mm512_extracti64x4_epi64(x, 0)) +
           mm256_popcount(_mm512_extracti64x4_epi64(x, 1));
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif
