// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Carry-less MUltiply and Mix ("MUM") functions
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/CLMUL_instruction_set
\sa https://www.felixcloutier.com/x86/pclmulqdq
*/

#pragma once

#include <immintrin.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__PCLMUL__)
// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-nonnull-function-attribute
static void
clmul_u64(uint64_t* hi, uint64_t* lo) [[gnu::nonnull]]
{
    // order of hi, lo doesn't matter
    __m128i result = _mm_set_epi64x((long long int)(*hi),
                                    (long long int)(*lo));

    // https://clang.llvm.org/doxygen/____wmmintrin__pclmul_8h.html
    // https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/wmmintrin.h#L103
    // __m128i _mm_clmulepi64_si128(__m128i a, __m128i b, int imm8)
    // imm8: 0x00 => b[0] * a[0]
    // imm8: 0x01 => b[0] * a[1]
    // imm8: 0x10 => b[1] * a[0]
    // imm8: 0x11 => b[1] * a[1]

    // MSB in result is always 0
    result = _mm_clmulepi64_si128(result, result, 0x10);

    *hi = (uint64_t)(_mm_extract_epi64(result, 1));
    *lo = (uint64_t)(_mm_extract_epi64(result, 0));
}

static inline uint64_t
clmumx_u64(uint64_t a, uint64_t b)
{
    clmul_u64(&a, &b);
    return a ^ b;
}

static inline uint64_t
clmuma_u64(uint64_t a, uint64_t b)
{
    clmul_u64(&a, &b);
    return a + b;
}

static inline uint64_t
clmums_u64(uint64_t a, uint64_t b)
{
    clmul_u64(&a, &b);
    return a - b;
}
#else
#warning "__PCLMUL__ not defined"
#endif

#ifdef __cplusplus
} // extern "C"
#endif
