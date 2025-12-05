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

#if defined(__x86_64__) && defined(__SSE4_1__)

#include <immintrin.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline int
mm_popcount(const __m128i x)
{
    const uint64_t x0 = (uint64_t)_mm_extract_epi64(x, 0);
    const uint64_t x1 = (uint64_t)_mm_extract_epi64(x, 1);
    return __builtin_popcountg(x0) + __builtin_popcountg(x1);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
