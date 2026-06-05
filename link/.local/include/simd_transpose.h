// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// SIMD matrix transpose functions
/**
* \file
* \author Steven Ward
* \sa https://arm-software.github.io/acle/neon_intrinsics/advsimd.html#zip-elements
* \sa https://arm-software.github.io/acle/neon_intrinsics/advsimd.html#transpose-elements
* \sa https://developer.arm.com/architectures/instruction-sets/intrinsics/#f:@navigationhierarchiessimdisa=[Neon]&f:@navigationhierarchiesreturnbasetype=[uint]&q=vzip
* \sa https://developer.arm.com/architectures/instruction-sets/intrinsics/#f:@navigationhierarchiessimdisa=[Neon]&f:@navigationhierarchiesreturnbasetype=[uint]&q=vtrn
*
* TRN1, TRN2, ZIP1, and ZIP2 have the same latency, throughput, and pipelines.
* https://developer.arm.com/documentation/109824/0002/?lang=en
* "Arm Cortex-A725 Core Software Optimization Guide"
*/

#pragma once

#if defined(__x86_64__)

#include <immintrin.h>

#if defined(__cplusplus)
extern "C" {
#endif

/// Transpose \a x (treating it as a 2x2 matrix of \c uint64_t) using SSE2 intrinsics
static void
transpose_2(__m128i x[static restrict 2])
{
    const __m128i AB_0 = _mm_unpacklo_epi64(x[0], x[1]);
    const __m128i AB_1 = _mm_unpackhi_epi64(x[0], x[1]);

    x[0] = AB_0;
    x[1] = AB_1;
}

/// Transpose \a x (treating it as a 4x4 matrix of \c uint32_t) using SSE2 intrinsics
/**
* \sa https://randombit.net/bitbashing/posts/integer_matrix_transpose_in_sse2.html
*/
static void
transpose_4(__m128i x[static restrict 4])
{
    const __m128i AB_01 = _mm_unpacklo_epi32(x[0], x[1]);
    const __m128i AB_23 = _mm_unpackhi_epi32(x[0], x[1]);
    const __m128i CD_01 = _mm_unpacklo_epi32(x[2], x[3]);
    const __m128i CD_23 = _mm_unpackhi_epi32(x[2], x[3]);

    x[0] = _mm_unpacklo_epi64(AB_01, CD_01); // ABCD_0
    x[1] = _mm_unpackhi_epi64(AB_01, CD_01); // ABCD_1
    x[2] = _mm_unpacklo_epi64(AB_23, CD_23); // ABCD_2
    x[3] = _mm_unpackhi_epi64(AB_23, CD_23); // ABCD_3
}

/// Transpose \a x (treating it as a 4x4 matrix of \c uint32_t) using the \c _MM_TRANSPOSE4_PS macro
/**
* \sa https://community.intel.com/t5/Intel-ISA-Extensions/4x4-matrix-transpose-using-sse2-intrinsics/m-p/785883#M353
* > Cast your __m128i variables into __m128 variables (using _mm_castsi128_ps),
* > use the macro _MM_TRANSPOSE_PS, then cast back using _mm_castps_si128.
*/
static void
transpose_4_macro(__m128i x[static restrict 4])
{
    __m128 A = _mm_castsi128_ps(x[0]);
    __m128 B = _mm_castsi128_ps(x[1]);
    __m128 C = _mm_castsi128_ps(x[2]);
    __m128 D = _mm_castsi128_ps(x[3]);

    _MM_TRANSPOSE4_PS(A, B, C, D);

    x[0] = _mm_castps_si128(A);
    x[1] = _mm_castps_si128(B);
    x[2] = _mm_castps_si128(C);
    x[3] = _mm_castps_si128(D);
}

/// Transpose \a x (treating it as an 8x8 matrix of \c uint16_t) using SSE2 intrinsics
/**
* \sa https://stackoverflow.com/a/4951060/1892784
*/
static void
transpose_8(__m128i x[static restrict 8])
{
    const __m128i AB_03 = _mm_unpacklo_epi16(x[0], x[1]);
    const __m128i AB_47 = _mm_unpackhi_epi16(x[0], x[1]);
    const __m128i CD_03 = _mm_unpacklo_epi16(x[2], x[3]);
    const __m128i CD_47 = _mm_unpackhi_epi16(x[2], x[3]);
    const __m128i EF_03 = _mm_unpacklo_epi16(x[4], x[5]);
    const __m128i EF_47 = _mm_unpackhi_epi16(x[4], x[5]);
    const __m128i GH_03 = _mm_unpacklo_epi16(x[6], x[7]);
    const __m128i GH_47 = _mm_unpackhi_epi16(x[6], x[7]);

    const __m128i ABCD_01 = _mm_unpacklo_epi32(AB_03, CD_03);
    const __m128i ABCD_23 = _mm_unpackhi_epi32(AB_03, CD_03);
    const __m128i ABCD_45 = _mm_unpacklo_epi32(AB_47, CD_47);
    const __m128i ABCD_67 = _mm_unpackhi_epi32(AB_47, CD_47);
    const __m128i EFGH_01 = _mm_unpacklo_epi32(EF_03, GH_03);
    const __m128i EFGH_23 = _mm_unpackhi_epi32(EF_03, GH_03);
    const __m128i EFGH_45 = _mm_unpacklo_epi32(EF_47, GH_47);
    const __m128i EFGH_67 = _mm_unpackhi_epi32(EF_47, GH_47);

    x[0] = _mm_unpacklo_epi64(ABCD_01, EFGH_01); // ABCDEFGH_0
    x[1] = _mm_unpackhi_epi64(ABCD_01, EFGH_01); // ABCDEFGH_1
    x[2] = _mm_unpacklo_epi64(ABCD_23, EFGH_23); // ABCDEFGH_2
    x[3] = _mm_unpackhi_epi64(ABCD_23, EFGH_23); // ABCDEFGH_3
    x[4] = _mm_unpacklo_epi64(ABCD_45, EFGH_45); // ABCDEFGH_4
    x[5] = _mm_unpackhi_epi64(ABCD_45, EFGH_45); // ABCDEFGH_5
    x[6] = _mm_unpacklo_epi64(ABCD_67, EFGH_67); // ABCDEFGH_6
    x[7] = _mm_unpackhi_epi64(ABCD_67, EFGH_67); // ABCDEFGH_7
}

/// Transpose \a x (treating it as a 16x16 matrix of \c uint8_t) using SSE2 intrinsics
/**
* \sa https://codereview.stackexchange.com/questions/295941/16x16-integer-matrix-transpose-using-sse2-intrinsics-in-c
*/
static void
transpose_16(__m128i x[static restrict 16])
{
    const __m128i AB_07 = _mm_unpacklo_epi8(x[0x0], x[0x1]);
    const __m128i AB_8f = _mm_unpackhi_epi8(x[0x0], x[0x1]);
    const __m128i CD_07 = _mm_unpacklo_epi8(x[0x2], x[0x3]);
    const __m128i CD_8f = _mm_unpackhi_epi8(x[0x2], x[0x3]);
    const __m128i EF_07 = _mm_unpacklo_epi8(x[0x4], x[0x5]);
    const __m128i EF_8f = _mm_unpackhi_epi8(x[0x4], x[0x5]);
    const __m128i GH_07 = _mm_unpacklo_epi8(x[0x6], x[0x7]);
    const __m128i GH_8f = _mm_unpackhi_epi8(x[0x6], x[0x7]);
    const __m128i IJ_07 = _mm_unpacklo_epi8(x[0x8], x[0x9]);
    const __m128i IJ_8f = _mm_unpackhi_epi8(x[0x8], x[0x9]);
    const __m128i KL_07 = _mm_unpacklo_epi8(x[0xa], x[0xb]);
    const __m128i KL_8f = _mm_unpackhi_epi8(x[0xa], x[0xb]);
    const __m128i MN_07 = _mm_unpacklo_epi8(x[0xc], x[0xd]);
    const __m128i MN_8f = _mm_unpackhi_epi8(x[0xc], x[0xd]);
    const __m128i OP_07 = _mm_unpacklo_epi8(x[0xe], x[0xf]);
    const __m128i OP_8f = _mm_unpackhi_epi8(x[0xe], x[0xf]);

    const __m128i ABCD_03 = _mm_unpacklo_epi16(AB_07, CD_07);
    const __m128i ABCD_47 = _mm_unpackhi_epi16(AB_07, CD_07);
    const __m128i ABCD_8b = _mm_unpacklo_epi16(AB_8f, CD_8f);
    const __m128i ABCD_cf = _mm_unpackhi_epi16(AB_8f, CD_8f);
    const __m128i EFGH_03 = _mm_unpacklo_epi16(EF_07, GH_07);
    const __m128i EFGH_47 = _mm_unpackhi_epi16(EF_07, GH_07);
    const __m128i EFGH_8b = _mm_unpacklo_epi16(EF_8f, GH_8f);
    const __m128i EFGH_cf = _mm_unpackhi_epi16(EF_8f, GH_8f);
    const __m128i IJKL_03 = _mm_unpacklo_epi16(IJ_07, KL_07);
    const __m128i IJKL_47 = _mm_unpackhi_epi16(IJ_07, KL_07);
    const __m128i IJKL_8b = _mm_unpacklo_epi16(IJ_8f, KL_8f);
    const __m128i IJKL_cf = _mm_unpackhi_epi16(IJ_8f, KL_8f);
    const __m128i MNOP_03 = _mm_unpacklo_epi16(MN_07, OP_07);
    const __m128i MNOP_47 = _mm_unpackhi_epi16(MN_07, OP_07);
    const __m128i MNOP_8b = _mm_unpacklo_epi16(MN_8f, OP_8f);
    const __m128i MNOP_cf = _mm_unpackhi_epi16(MN_8f, OP_8f);

    const __m128i ABCDEFGH_01 = _mm_unpacklo_epi32(ABCD_03, EFGH_03);
    const __m128i ABCDEFGH_23 = _mm_unpackhi_epi32(ABCD_03, EFGH_03);
    const __m128i ABCDEFGH_45 = _mm_unpacklo_epi32(ABCD_47, EFGH_47);
    const __m128i ABCDEFGH_67 = _mm_unpackhi_epi32(ABCD_47, EFGH_47);
    const __m128i ABCDEFGH_89 = _mm_unpacklo_epi32(ABCD_8b, EFGH_8b);
    const __m128i ABCDEFGH_ab = _mm_unpackhi_epi32(ABCD_8b, EFGH_8b);
    const __m128i ABCDEFGH_cd = _mm_unpacklo_epi32(ABCD_cf, EFGH_cf);
    const __m128i ABCDEFGH_ef = _mm_unpackhi_epi32(ABCD_cf, EFGH_cf);
    const __m128i IJKLMNOP_01 = _mm_unpacklo_epi32(IJKL_03, MNOP_03);
    const __m128i IJKLMNOP_23 = _mm_unpackhi_epi32(IJKL_03, MNOP_03);
    const __m128i IJKLMNOP_45 = _mm_unpacklo_epi32(IJKL_47, MNOP_47);
    const __m128i IJKLMNOP_67 = _mm_unpackhi_epi32(IJKL_47, MNOP_47);
    const __m128i IJKLMNOP_89 = _mm_unpacklo_epi32(IJKL_8b, MNOP_8b);
    const __m128i IJKLMNOP_ab = _mm_unpackhi_epi32(IJKL_8b, MNOP_8b);
    const __m128i IJKLMNOP_cd = _mm_unpacklo_epi32(IJKL_cf, MNOP_cf);
    const __m128i IJKLMNOP_ef = _mm_unpackhi_epi32(IJKL_cf, MNOP_cf);

    x[0x0] = _mm_unpacklo_epi64(ABCDEFGH_01, IJKLMNOP_01); // ABCDEFGHIJKLMNOP_0
    x[0x1] = _mm_unpackhi_epi64(ABCDEFGH_01, IJKLMNOP_01); // ABCDEFGHIJKLMNOP_1
    x[0x2] = _mm_unpacklo_epi64(ABCDEFGH_23, IJKLMNOP_23); // ABCDEFGHIJKLMNOP_2
    x[0x3] = _mm_unpackhi_epi64(ABCDEFGH_23, IJKLMNOP_23); // ABCDEFGHIJKLMNOP_3
    x[0x4] = _mm_unpacklo_epi64(ABCDEFGH_45, IJKLMNOP_45); // ABCDEFGHIJKLMNOP_4
    x[0x5] = _mm_unpackhi_epi64(ABCDEFGH_45, IJKLMNOP_45); // ABCDEFGHIJKLMNOP_5
    x[0x6] = _mm_unpacklo_epi64(ABCDEFGH_67, IJKLMNOP_67); // ABCDEFGHIJKLMNOP_6
    x[0x7] = _mm_unpackhi_epi64(ABCDEFGH_67, IJKLMNOP_67); // ABCDEFGHIJKLMNOP_7
    x[0x8] = _mm_unpacklo_epi64(ABCDEFGH_89, IJKLMNOP_89); // ABCDEFGHIJKLMNOP_8
    x[0x9] = _mm_unpackhi_epi64(ABCDEFGH_89, IJKLMNOP_89); // ABCDEFGHIJKLMNOP_9
    x[0xa] = _mm_unpacklo_epi64(ABCDEFGH_ab, IJKLMNOP_ab); // ABCDEFGHIJKLMNOP_a
    x[0xb] = _mm_unpackhi_epi64(ABCDEFGH_ab, IJKLMNOP_ab); // ABCDEFGHIJKLMNOP_b
    x[0xc] = _mm_unpacklo_epi64(ABCDEFGH_cd, IJKLMNOP_cd); // ABCDEFGHIJKLMNOP_c
    x[0xd] = _mm_unpackhi_epi64(ABCDEFGH_cd, IJKLMNOP_cd); // ABCDEFGHIJKLMNOP_d
    x[0xe] = _mm_unpacklo_epi64(ABCDEFGH_ef, IJKLMNOP_ef); // ABCDEFGHIJKLMNOP_e
    x[0xf] = _mm_unpackhi_epi64(ABCDEFGH_ef, IJKLMNOP_ef); // ABCDEFGHIJKLMNOP_f
}

#if defined(__cplusplus)
} // extern "C"
#endif

#elif defined(__aarch64__) && defined(__ARM_NEON)

#include <arm_neon.h>

#if defined(__cplusplus)
extern "C" {
#endif

/// Transpose \a x (treating it as a 2x2 matrix of \c uint64_t) using ARM Neon intrinsics
static void
transpose_2(uint64x2_t x[static restrict 2])
{
    const uint64x2_t AB_0 = vzip1q_u64(x[0], x[1]);
    const uint64x2_t AB_1 = vzip2q_u64(x[0], x[1]);

    x[0] = AB_0;
    x[1] = AB_1;
}

/// Transpose \a x (treating it as a 4x4 matrix of \c uint32_t) using ARM Neon intrinsics
static void
transpose_4(uint32x4_t x[static restrict 4])
{
    const uint32x4_t AB_01 = vzip1q_u32(x[0], x[1]);
    const uint32x4_t AB_23 = vzip2q_u32(x[0], x[1]);
    const uint32x4_t CD_01 = vzip1q_u32(x[2], x[3]);
    const uint32x4_t CD_23 = vzip2q_u32(x[2], x[3]);

    const uint64x2_t ABCD_0 = vzip1q_u64(vreinterpretq_u64_u32(AB_01), vreinterpretq_u64_u32(CD_01));
    const uint64x2_t ABCD_1 = vzip2q_u64(vreinterpretq_u64_u32(AB_01), vreinterpretq_u64_u32(CD_01));
    const uint64x2_t ABCD_2 = vzip1q_u64(vreinterpretq_u64_u32(AB_23), vreinterpretq_u64_u32(CD_23));
    const uint64x2_t ABCD_3 = vzip2q_u64(vreinterpretq_u64_u32(AB_23), vreinterpretq_u64_u32(CD_23));

    x[0] = vreinterpretq_u32_u64(ABCD_0);
    x[1] = vreinterpretq_u32_u64(ABCD_1);
    x[2] = vreinterpretq_u32_u64(ABCD_2);
    x[3] = vreinterpretq_u32_u64(ABCD_3);
}

/// Transpose \a x (treating it as a 8x8 matrix of \c uint16_t) using ARM Neon intrinsics
static void
transpose_8(uint16x8_t x[static restrict 8])
{
    const uint16x8_t AB_03 = vzip1q_u16(x[0], x[1]);
    const uint16x8_t AB_47 = vzip2q_u16(x[0], x[1]);
    const uint16x8_t CD_03 = vzip1q_u16(x[2], x[3]);
    const uint16x8_t CD_47 = vzip2q_u16(x[2], x[3]);
    const uint16x8_t EF_03 = vzip1q_u16(x[4], x[5]);
    const uint16x8_t EF_47 = vzip2q_u16(x[4], x[5]);
    const uint16x8_t GH_03 = vzip1q_u16(x[6], x[7]);
    const uint16x8_t GH_47 = vzip2q_u16(x[6], x[7]);

    const uint32x4_t ABCD_01 = vzip1q_u32(vreinterpretq_u32_u16(AB_03), vreinterpretq_u32_u16(CD_03));
    const uint32x4_t ABCD_23 = vzip2q_u32(vreinterpretq_u32_u16(AB_03), vreinterpretq_u32_u16(CD_03));
    const uint32x4_t ABCD_45 = vzip1q_u32(vreinterpretq_u32_u16(AB_47), vreinterpretq_u32_u16(CD_47));
    const uint32x4_t ABCD_67 = vzip2q_u32(vreinterpretq_u32_u16(AB_47), vreinterpretq_u32_u16(CD_47));
    const uint32x4_t EFGH_01 = vzip1q_u32(vreinterpretq_u32_u16(EF_03), vreinterpretq_u32_u16(GH_03));
    const uint32x4_t EFGH_23 = vzip2q_u32(vreinterpretq_u32_u16(EF_03), vreinterpretq_u32_u16(GH_03));
    const uint32x4_t EFGH_45 = vzip1q_u32(vreinterpretq_u32_u16(EF_47), vreinterpretq_u32_u16(GH_47));
    const uint32x4_t EFGH_67 = vzip2q_u32(vreinterpretq_u32_u16(EF_47), vreinterpretq_u32_u16(GH_47));

    const uint64x2_t ABCDEFGH_0 = vzip1q_u64(vreinterpretq_u64_u32(ABCD_01), vreinterpretq_u64_u32(EFGH_01));
    const uint64x2_t ABCDEFGH_1 = vzip2q_u64(vreinterpretq_u64_u32(ABCD_01), vreinterpretq_u64_u32(EFGH_01));
    const uint64x2_t ABCDEFGH_2 = vzip1q_u64(vreinterpretq_u64_u32(ABCD_23), vreinterpretq_u64_u32(EFGH_23));
    const uint64x2_t ABCDEFGH_3 = vzip2q_u64(vreinterpretq_u64_u32(ABCD_23), vreinterpretq_u64_u32(EFGH_23));
    const uint64x2_t ABCDEFGH_4 = vzip1q_u64(vreinterpretq_u64_u32(ABCD_45), vreinterpretq_u64_u32(EFGH_45));
    const uint64x2_t ABCDEFGH_5 = vzip2q_u64(vreinterpretq_u64_u32(ABCD_45), vreinterpretq_u64_u32(EFGH_45));
    const uint64x2_t ABCDEFGH_6 = vzip1q_u64(vreinterpretq_u64_u32(ABCD_67), vreinterpretq_u64_u32(EFGH_67));
    const uint64x2_t ABCDEFGH_7 = vzip2q_u64(vreinterpretq_u64_u32(ABCD_67), vreinterpretq_u64_u32(EFGH_67));

    x[0] = vreinterpretq_u16_u64(ABCDEFGH_0);
    x[1] = vreinterpretq_u16_u64(ABCDEFGH_1);
    x[2] = vreinterpretq_u16_u64(ABCDEFGH_2);
    x[3] = vreinterpretq_u16_u64(ABCDEFGH_3);
    x[4] = vreinterpretq_u16_u64(ABCDEFGH_4);
    x[5] = vreinterpretq_u16_u64(ABCDEFGH_5);
    x[6] = vreinterpretq_u16_u64(ABCDEFGH_6);
    x[7] = vreinterpretq_u16_u64(ABCDEFGH_7);
}

/// Transpose \a x (treating it as a 16x16 matrix of \c uint8_t) using ARM Neon intrinsics
static void
transpose_16(uint8x16_t x[static restrict 16])
{
    const uint8x16_t AB_07 = vzip1q_u8(x[0x0], x[0x1]);
    const uint8x16_t AB_8f = vzip2q_u8(x[0x0], x[0x1]);
    const uint8x16_t CD_07 = vzip1q_u8(x[0x2], x[0x3]);
    const uint8x16_t CD_8f = vzip2q_u8(x[0x2], x[0x3]);
    const uint8x16_t EF_07 = vzip1q_u8(x[0x4], x[0x5]);
    const uint8x16_t EF_8f = vzip2q_u8(x[0x4], x[0x5]);
    const uint8x16_t GH_07 = vzip1q_u8(x[0x6], x[0x7]);
    const uint8x16_t GH_8f = vzip2q_u8(x[0x6], x[0x7]);
    const uint8x16_t IJ_07 = vzip1q_u8(x[0x8], x[0x9]);
    const uint8x16_t IJ_8f = vzip2q_u8(x[0x8], x[0x9]);
    const uint8x16_t KL_07 = vzip1q_u8(x[0xa], x[0xb]);
    const uint8x16_t KL_8f = vzip2q_u8(x[0xa], x[0xb]);
    const uint8x16_t MN_07 = vzip1q_u8(x[0xc], x[0xd]);
    const uint8x16_t MN_8f = vzip2q_u8(x[0xc], x[0xd]);
    const uint8x16_t OP_07 = vzip1q_u8(x[0xe], x[0xf]);
    const uint8x16_t OP_8f = vzip2q_u8(x[0xe], x[0xf]);

    const uint16x8_t ABCD_03 = vzip1q_u16(vreinterpretq_u16_u8(AB_07), vreinterpretq_u16_u8(CD_07));
    const uint16x8_t ABCD_47 = vzip2q_u16(vreinterpretq_u16_u8(AB_07), vreinterpretq_u16_u8(CD_07));
    const uint16x8_t ABCD_8b = vzip1q_u16(vreinterpretq_u16_u8(AB_8f), vreinterpretq_u16_u8(CD_8f));
    const uint16x8_t ABCD_cf = vzip2q_u16(vreinterpretq_u16_u8(AB_8f), vreinterpretq_u16_u8(CD_8f));
    const uint16x8_t EFGH_03 = vzip1q_u16(vreinterpretq_u16_u8(EF_07), vreinterpretq_u16_u8(GH_07));
    const uint16x8_t EFGH_47 = vzip2q_u16(vreinterpretq_u16_u8(EF_07), vreinterpretq_u16_u8(GH_07));
    const uint16x8_t EFGH_8b = vzip1q_u16(vreinterpretq_u16_u8(EF_8f), vreinterpretq_u16_u8(GH_8f));
    const uint16x8_t EFGH_cf = vzip2q_u16(vreinterpretq_u16_u8(EF_8f), vreinterpretq_u16_u8(GH_8f));
    const uint16x8_t IJKL_03 = vzip1q_u16(vreinterpretq_u16_u8(IJ_07), vreinterpretq_u16_u8(KL_07));
    const uint16x8_t IJKL_47 = vzip2q_u16(vreinterpretq_u16_u8(IJ_07), vreinterpretq_u16_u8(KL_07));
    const uint16x8_t IJKL_8b = vzip1q_u16(vreinterpretq_u16_u8(IJ_8f), vreinterpretq_u16_u8(KL_8f));
    const uint16x8_t IJKL_cf = vzip2q_u16(vreinterpretq_u16_u8(IJ_8f), vreinterpretq_u16_u8(KL_8f));
    const uint16x8_t MNOP_03 = vzip1q_u16(vreinterpretq_u16_u8(MN_07), vreinterpretq_u16_u8(OP_07));
    const uint16x8_t MNOP_47 = vzip2q_u16(vreinterpretq_u16_u8(MN_07), vreinterpretq_u16_u8(OP_07));
    const uint16x8_t MNOP_8b = vzip1q_u16(vreinterpretq_u16_u8(MN_8f), vreinterpretq_u16_u8(OP_8f));
    const uint16x8_t MNOP_cf = vzip2q_u16(vreinterpretq_u16_u8(MN_8f), vreinterpretq_u16_u8(OP_8f));

    const uint32x4_t ABCDEFGH_01 = vzip1q_u32(vreinterpretq_u32_u16(ABCD_03), vreinterpretq_u32_u16(EFGH_03));
    const uint32x4_t ABCDEFGH_23 = vzip2q_u32(vreinterpretq_u32_u16(ABCD_03), vreinterpretq_u32_u16(EFGH_03));
    const uint32x4_t ABCDEFGH_45 = vzip1q_u32(vreinterpretq_u32_u16(ABCD_47), vreinterpretq_u32_u16(EFGH_47));
    const uint32x4_t ABCDEFGH_67 = vzip2q_u32(vreinterpretq_u32_u16(ABCD_47), vreinterpretq_u32_u16(EFGH_47));
    const uint32x4_t ABCDEFGH_89 = vzip1q_u32(vreinterpretq_u32_u16(ABCD_8b), vreinterpretq_u32_u16(EFGH_8b));
    const uint32x4_t ABCDEFGH_ab = vzip2q_u32(vreinterpretq_u32_u16(ABCD_8b), vreinterpretq_u32_u16(EFGH_8b));
    const uint32x4_t ABCDEFGH_cd = vzip1q_u32(vreinterpretq_u32_u16(ABCD_cf), vreinterpretq_u32_u16(EFGH_cf));
    const uint32x4_t ABCDEFGH_ef = vzip2q_u32(vreinterpretq_u32_u16(ABCD_cf), vreinterpretq_u32_u16(EFGH_cf));
    const uint32x4_t IJKLMNOP_01 = vzip1q_u32(vreinterpretq_u32_u16(IJKL_03), vreinterpretq_u32_u16(MNOP_03));
    const uint32x4_t IJKLMNOP_23 = vzip2q_u32(vreinterpretq_u32_u16(IJKL_03), vreinterpretq_u32_u16(MNOP_03));
    const uint32x4_t IJKLMNOP_45 = vzip1q_u32(vreinterpretq_u32_u16(IJKL_47), vreinterpretq_u32_u16(MNOP_47));
    const uint32x4_t IJKLMNOP_67 = vzip2q_u32(vreinterpretq_u32_u16(IJKL_47), vreinterpretq_u32_u16(MNOP_47));
    const uint32x4_t IJKLMNOP_89 = vzip1q_u32(vreinterpretq_u32_u16(IJKL_8b), vreinterpretq_u32_u16(MNOP_8b));
    const uint32x4_t IJKLMNOP_ab = vzip2q_u32(vreinterpretq_u32_u16(IJKL_8b), vreinterpretq_u32_u16(MNOP_8b));
    const uint32x4_t IJKLMNOP_cd = vzip1q_u32(vreinterpretq_u32_u16(IJKL_cf), vreinterpretq_u32_u16(MNOP_cf));
    const uint32x4_t IJKLMNOP_ef = vzip2q_u32(vreinterpretq_u32_u16(IJKL_cf), vreinterpretq_u32_u16(MNOP_cf));

    const uint64x2_t ABCDEFGHIJKLMNOP_0 = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_01), vreinterpretq_u64_u32(IJKLMNOP_01));
    const uint64x2_t ABCDEFGHIJKLMNOP_1 = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_01), vreinterpretq_u64_u32(IJKLMNOP_01));
    const uint64x2_t ABCDEFGHIJKLMNOP_2 = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_23), vreinterpretq_u64_u32(IJKLMNOP_23));
    const uint64x2_t ABCDEFGHIJKLMNOP_3 = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_23), vreinterpretq_u64_u32(IJKLMNOP_23));
    const uint64x2_t ABCDEFGHIJKLMNOP_4 = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_45), vreinterpretq_u64_u32(IJKLMNOP_45));
    const uint64x2_t ABCDEFGHIJKLMNOP_5 = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_45), vreinterpretq_u64_u32(IJKLMNOP_45));
    const uint64x2_t ABCDEFGHIJKLMNOP_6 = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_67), vreinterpretq_u64_u32(IJKLMNOP_67));
    const uint64x2_t ABCDEFGHIJKLMNOP_7 = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_67), vreinterpretq_u64_u32(IJKLMNOP_67));
    const uint64x2_t ABCDEFGHIJKLMNOP_8 = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_89), vreinterpretq_u64_u32(IJKLMNOP_89));
    const uint64x2_t ABCDEFGHIJKLMNOP_9 = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_89), vreinterpretq_u64_u32(IJKLMNOP_89));
    const uint64x2_t ABCDEFGHIJKLMNOP_a = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_ab), vreinterpretq_u64_u32(IJKLMNOP_ab));
    const uint64x2_t ABCDEFGHIJKLMNOP_b = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_ab), vreinterpretq_u64_u32(IJKLMNOP_ab));
    const uint64x2_t ABCDEFGHIJKLMNOP_c = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_cd), vreinterpretq_u64_u32(IJKLMNOP_cd));
    const uint64x2_t ABCDEFGHIJKLMNOP_d = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_cd), vreinterpretq_u64_u32(IJKLMNOP_cd));
    const uint64x2_t ABCDEFGHIJKLMNOP_e = vzip1q_u64(vreinterpretq_u64_u32(ABCDEFGH_ef), vreinterpretq_u64_u32(IJKLMNOP_ef));
    const uint64x2_t ABCDEFGHIJKLMNOP_f = vzip2q_u64(vreinterpretq_u64_u32(ABCDEFGH_ef), vreinterpretq_u64_u32(IJKLMNOP_ef));

    x[0x0] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_0);
    x[0x1] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_1);
    x[0x2] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_2);
    x[0x3] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_3);
    x[0x4] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_4);
    x[0x5] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_5);
    x[0x6] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_6);
    x[0x7] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_7);
    x[0x8] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_8);
    x[0x9] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_9);
    x[0xa] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_a);
    x[0xb] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_b);
    x[0xc] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_c);
    x[0xd] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_d);
    x[0xe] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_e);
    x[0xf] = vreinterpretq_u8_u64(ABCDEFGHIJKLMNOP_f);
}

#if defined(__cplusplus)
} // extern "C"
#endif

#else

#error "Architecture not supported"

#endif
