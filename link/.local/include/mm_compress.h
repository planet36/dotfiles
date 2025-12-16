// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Compress 2 \c __m128i into 1 \c __m128i non-symmetrically and non-linearly
/**
* \file
* \author Steven Ward
*/

#pragma once

#if defined(__x86_64__)
#include <immintrin.h>
typedef __m128i simd128_t;
#elif defined(__aarch64__)
#include <arm_neon.h>
typedef uint8x16_t simd128_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline simd128_t
mm_compress(const simd128_t a, const simd128_t b)
{
#if defined(__AES__)
    return
        _mm_aesenc_si128(
                _mm_aesenc_si128(
                    _mm_aesenc_si128(
                        _mm_aesenc_si128(b, a),
                        b),
                    a),
                _mm_setzero_si128());
#elif defined(__ARM_FEATURE_AES)
    return
        vaesmcq_u8(vaeseq_u8(
                    vaesmcq_u8(vaeseq_u8(
                            vaesmcq_u8(vaeseq_u8(
                                    vaesmcq_u8(vaeseq_u8(b, zero)),
                                    a)),
                            b)),
                    a));
#endif
}

#ifdef __cplusplus
} // extern "C"
#endif
