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
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__AES__)
static inline __m128i
mm_compress128(const __m128i a, const __m128i b)
{
    return
        _mm_aesenc_si128(
                _mm_aesenc_si128(
                    _mm_aesenc_si128(
                        _mm_aesenc_si128(b, a),
                        b),
                    a),
                _mm_setzero_si128());
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif
