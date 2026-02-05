// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// One-way compression functions for 2 SIMD registers
/**
* \file
* \author Steven Ward
*
* \sa https://blog.michaelbrase.com/2018/05/08/emulating-x86-aes-intrinsics-on-armv8-a/
* \sa https://blog.michaelbrase.com/2018/06/04/optimizing-x86-aes-intrinsics-on-armv8-a/
*
* ## AES instruction comparison
* \verbatim
|--------|---------------|-------------|--------|
| Round  | AES Step      | Intel       | ARM    |
|--------|---------------|-------------|--------|
| 0      | AddRoundKey   | XOR         | AESE   |
|--------|---------------|-------------|        |
| 1      | SubBytes      | AESENC      |        |
|        |               |             |        |
|        | ShiftRows     |             |        |
|        |               |             |--------|
|        | MixColumns    |             | AESMC  |
|        |               |             |--------|
|        | AddRoundKey   |             | AESE   |
|--------|---------------|-------------|        |
| 2      | SubBytes      | AESENC      |        |
|        |               |             |        |
|        | ShiftRows     |             |        |
|        |               |             |--------|
|        | MixColumns    |             | AESMC  |
|        |               |             |--------|
|        | AddRoundKey   |             | AESE   |
|--------|---------------|-------------|        |
| 3      | SubBytes      | AESENC      |        |
|        |               |             |        |
|        | ShiftRows     |             |        |
|        |               |             |--------|
|        | MixColumns    |             | AESMC  |
|        |               |             |--------|
|        | AddRoundKey   |             | AESE   |
|--------|---------------|-------------|        |
| last   | SubBytes      | AESENCLAST  |        |
|        |               |             |        |
|        | ShiftRows     |             |        |
|        |               |             |--------|
|        | AddRoundKey   |             | XOR    |
| -------|---------------|-------------|--------|
\endverbatim
*/

#pragma once

#if defined(__x86_64__) && defined(__AES__)
#include <immintrin.h>
typedef __m128i simd128_t;
#elif defined(__aarch64__) && defined(__ARM_FEATURE_AES)
#include <arm_neon.h>
typedef uint8x16_t simd128_t;
#else
#error "Architecture not supported"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// Compress (via AES operations) 2 128-bit SIMD registers into 1,
/// non-symmetrically and non-linearly
static inline simd128_t
compress_aesenc4_128(const simd128_t a, const simd128_t b)
{
#if defined(__x86_64__) && defined(__AES__)
    return
        _mm_aesenc_si128(
                _mm_aesenc_si128(
                    _mm_aesenc_si128(
                        _mm_aesenc_si128(a, b),
                        a),
                    b),
                a);
#elif defined(__aarch64__) && defined(__ARM_FEATURE_AES)
    const simd128_t zero = vdupq_n_u8(0);
    return
        vaesmcq_u8(vaeseq_u8(
                    vaesmcq_u8(vaeseq_u8(
                            vaesmcq_u8(vaeseq_u8(
                                    vaesmcq_u8(vaeseq_u8(a, zero)),
                                    b)),
                            a)),
                    b)) ^ a;
#endif
}

#ifdef __cplusplus
} // extern "C"
#endif
