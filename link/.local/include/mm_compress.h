// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Compress 2 \c __m128i into 1 \c __m128i non-symmetrically and non-linearly
/**
* \file
* \author Steven Ward
*
* \sa https://blog.michaelbrase.com/2018/05/08/emulating-x86-aes-intrinsics-on-armv8-a/
* \sa https://blog.michaelbrase.com/2018/06/04/optimizing-x86-aes-intrinsics-on-armv8-a/
*
* \verbatim
* AES instruction comparison
* |--------|---------------|-------------|--------|
* | Round  | AES Step      | Intel       | ARM    |
* |--------|---------------|-------------|--------|
* | 0      | AddRoundKey   | XOR         | AESE   |
* |--------|---------------|-------------|        |
* | 1      | SubBytes      | AESENC      |        |
* |        |               |             |        |
* |        | ShiftRows     |             |        |
* |        |               |             |--------|
* |        | MixColumns    |             | AESMC  |
* |        |               |             |--------|
* |        | AddRoundKey   |             | AESE   |
* |--------|---------------|-------------|        |
* | 2      | SubBytes      | AESENC      |        |
* |        |               |             |        |
* |        | ShiftRows     |             |        |
* |        |               |             |--------|
* |        | MixColumns    |             | AESMC  |
* |        |               |             |--------|
* |        | AddRoundKey   |             | AESE   |
* |--------|---------------|-------------|        |
* | 3      | SubBytes      | AESENC      |        |
* |        |               |             |        |
* |        | ShiftRows     |             |        |
* |        |               |             |--------|
* |        | MixColumns    |             | AESMC  |
* |        |               |             |--------|
* |        | AddRoundKey   |             | AESE   |
* |--------|---------------|-------------|        |
* | last   | SubBytes      | AESENCLAST  |        |
* |        |               |             |        |
* |        | ShiftRows     |             |        |
* |        |               |             |--------|
* |        | AddRoundKey   |             | XOR    |
* | -------|---------------|-------------|--------|
* \endverbatim
*/

#pragma once

#if defined(__x86_64__)
#include <immintrin.h>
typedef __m128i simd128_t;
#elif defined(__aarch64__)
#include <arm_neon.h>
typedef uint8x16_t simd128_t;
#else
#error "Architecture not supported"
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline simd128_t
mm_compress(const simd128_t a, const simd128_t b)
{
#if defined(__AES__)
    const simd128_t zero = _mm_setzero_si128();
    return
        _mm_aesenc_si128(
                _mm_aesenc_si128(
                    _mm_aesenc_si128(
                        _mm_aesenc_si128(b, a),
                        b),
                    a),
                zero);
#elif defined(__ARM_FEATURE_AES)
    const simd128_t zero = vdupq_n_u8(0);
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
