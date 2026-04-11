// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

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

#include <cstdint>
#include <immintrin.h>

#if defined(__SSE4_1__)
static inline int
popcount(const __m128i x)
{
    const auto x0 = static_cast<uint64_t>(_mm_extract_epi64(x, 0));
    const auto x1 = static_cast<uint64_t>(_mm_extract_epi64(x, 1));
    return __builtin_popcountg(x0) + __builtin_popcountg(x1);
}
#endif

#if defined(__AVX__)
static inline int
popcount(const __m256i x)
{
    const auto x0 = static_cast<uint64_t>(_mm256_extract_epi64(x, 0));
    const auto x1 = static_cast<uint64_t>(_mm256_extract_epi64(x, 1));
    const auto x2 = static_cast<uint64_t>(_mm256_extract_epi64(x, 2));
    const auto x3 = static_cast<uint64_t>(_mm256_extract_epi64(x, 3));
    return __builtin_popcountg(x0) + __builtin_popcountg(x1) +
           __builtin_popcountg(x2) + __builtin_popcountg(x3);
}
#endif

#if defined(__AVX512F__)
static inline int
popcount(const __m512i x)
{
    return popcount(_mm512_extracti64x4_epi64(x, 0)) +
           popcount(_mm512_extracti64x4_epi64(x, 1));
}
#endif

#elif defined(__aarch64__) && defined(__ARM_NEON)

#include <arm_neon.h>

static inline int
popcount(const uint8x16_t x)
{
    return vaddvq_u8(vcntq_u8(x));
}

static inline int
popcount(const uint8x16x2_t x)
{
    return popcount(x.val[0]) + popcount(x.val[1]);
}

#else

#error "Architecture not supported"

#endif
