// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// SIMD matrix transpose functions
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "simd_types.hpp"

#include <array>

#if defined(__x86_64__) && defined(__SSE2__)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"

/// Transpose \a x (treating it as a 2x2 matrix of \c uint64_t) using SSE2 intrinsics
static void
simd_transpose(std::array<__m128i, 2>& x) noexcept
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
simd_transpose(std::array<__m128i, 4>& x) noexcept
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

/// Transpose \a x (treating it as an 8x8 matrix of \c uint16_t) using SSE2 intrinsics
/**
* \sa https://stackoverflow.com/a/4951060/1892784
*/
static void
simd_transpose(std::array<__m128i, 8>& x) noexcept
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
simd_transpose(std::array<__m128i, 16>& x) noexcept
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

#if defined(__AVX2__)

/// Transpose each 128-bit lane of \a x (treating it as two independent 2x2 matrices of \c uint64_t) using AVX2 intrinsics
/**
* The AVX2 integer unpacks stay within each 128-bit lane, so this is the 2x2
* SSE2 network above lifted verbatim to ymm registers.  That is what lets two
* independent Castella states be permuted in lockstep, one per lane (see
* \c Castella::permute_x2).
*/
static void
simd_transpose(std::array<__m256i, 2>& x) noexcept
{
    const __m256i AB_0 = _mm256_unpacklo_epi64(x[0], x[1]);
    const __m256i AB_1 = _mm256_unpackhi_epi64(x[0], x[1]);

    x[0] = AB_0;
    x[1] = AB_1;
}

/// Transpose each 128-bit lane of \a x (treating it as two independent 4x4 matrices of \c uint32_t) using AVX2 intrinsics
/**
* The 4x4 SSE2 network above, lifted to ymm registers.  See the 2x2 overload.
*/
static void
simd_transpose(std::array<__m256i, 4>& x) noexcept
{
    const __m256i AB_01 = _mm256_unpacklo_epi32(x[0], x[1]);
    const __m256i AB_23 = _mm256_unpackhi_epi32(x[0], x[1]);
    const __m256i CD_01 = _mm256_unpacklo_epi32(x[2], x[3]);
    const __m256i CD_23 = _mm256_unpackhi_epi32(x[2], x[3]);

    x[0] = _mm256_unpacklo_epi64(AB_01, CD_01); // ABCD_0
    x[1] = _mm256_unpackhi_epi64(AB_01, CD_01); // ABCD_1
    x[2] = _mm256_unpacklo_epi64(AB_23, CD_23); // ABCD_2
    x[3] = _mm256_unpackhi_epi64(AB_23, CD_23); // ABCD_3
}

/// Transpose each 128-bit lane of \a x (treating it as two independent 8x8 matrices of \c uint16_t) using AVX2 intrinsics
/**
* The 8x8 SSE2 network above, lifted to ymm registers.  See the 2x2 overload.
*/
static void
simd_transpose(std::array<__m256i, 8>& x) noexcept
{
    const __m256i AB_03 = _mm256_unpacklo_epi16(x[0], x[1]);
    const __m256i AB_47 = _mm256_unpackhi_epi16(x[0], x[1]);
    const __m256i CD_03 = _mm256_unpacklo_epi16(x[2], x[3]);
    const __m256i CD_47 = _mm256_unpackhi_epi16(x[2], x[3]);
    const __m256i EF_03 = _mm256_unpacklo_epi16(x[4], x[5]);
    const __m256i EF_47 = _mm256_unpackhi_epi16(x[4], x[5]);
    const __m256i GH_03 = _mm256_unpacklo_epi16(x[6], x[7]);
    const __m256i GH_47 = _mm256_unpackhi_epi16(x[6], x[7]);

    const __m256i ABCD_01 = _mm256_unpacklo_epi32(AB_03, CD_03);
    const __m256i ABCD_23 = _mm256_unpackhi_epi32(AB_03, CD_03);
    const __m256i ABCD_45 = _mm256_unpacklo_epi32(AB_47, CD_47);
    const __m256i ABCD_67 = _mm256_unpackhi_epi32(AB_47, CD_47);
    const __m256i EFGH_01 = _mm256_unpacklo_epi32(EF_03, GH_03);
    const __m256i EFGH_23 = _mm256_unpackhi_epi32(EF_03, GH_03);
    const __m256i EFGH_45 = _mm256_unpacklo_epi32(EF_47, GH_47);
    const __m256i EFGH_67 = _mm256_unpackhi_epi32(EF_47, GH_47);

    x[0] = _mm256_unpacklo_epi64(ABCD_01, EFGH_01); // ABCDEFGH_0
    x[1] = _mm256_unpackhi_epi64(ABCD_01, EFGH_01); // ABCDEFGH_1
    x[2] = _mm256_unpacklo_epi64(ABCD_23, EFGH_23); // ABCDEFGH_2
    x[3] = _mm256_unpackhi_epi64(ABCD_23, EFGH_23); // ABCDEFGH_3
    x[4] = _mm256_unpacklo_epi64(ABCD_45, EFGH_45); // ABCDEFGH_4
    x[5] = _mm256_unpackhi_epi64(ABCD_45, EFGH_45); // ABCDEFGH_5
    x[6] = _mm256_unpacklo_epi64(ABCD_67, EFGH_67); // ABCDEFGH_6
    x[7] = _mm256_unpackhi_epi64(ABCD_67, EFGH_67); // ABCDEFGH_7
}

/// Transpose each 128-bit lane of \a x (treating it as two independent 16x16 matrices of \c uint8_t) using AVX2 intrinsics
/**
* The 16x16 SSE2 network above, lifted to ymm registers.  See the 2x2
* overload.
*/
static void
simd_transpose(std::array<__m256i, 16>& x) noexcept
{
    const __m256i AB_07 = _mm256_unpacklo_epi8(x[0x0], x[0x1]);
    const __m256i AB_8f = _mm256_unpackhi_epi8(x[0x0], x[0x1]);
    const __m256i CD_07 = _mm256_unpacklo_epi8(x[0x2], x[0x3]);
    const __m256i CD_8f = _mm256_unpackhi_epi8(x[0x2], x[0x3]);
    const __m256i EF_07 = _mm256_unpacklo_epi8(x[0x4], x[0x5]);
    const __m256i EF_8f = _mm256_unpackhi_epi8(x[0x4], x[0x5]);
    const __m256i GH_07 = _mm256_unpacklo_epi8(x[0x6], x[0x7]);
    const __m256i GH_8f = _mm256_unpackhi_epi8(x[0x6], x[0x7]);
    const __m256i IJ_07 = _mm256_unpacklo_epi8(x[0x8], x[0x9]);
    const __m256i IJ_8f = _mm256_unpackhi_epi8(x[0x8], x[0x9]);
    const __m256i KL_07 = _mm256_unpacklo_epi8(x[0xa], x[0xb]);
    const __m256i KL_8f = _mm256_unpackhi_epi8(x[0xa], x[0xb]);
    const __m256i MN_07 = _mm256_unpacklo_epi8(x[0xc], x[0xd]);
    const __m256i MN_8f = _mm256_unpackhi_epi8(x[0xc], x[0xd]);
    const __m256i OP_07 = _mm256_unpacklo_epi8(x[0xe], x[0xf]);
    const __m256i OP_8f = _mm256_unpackhi_epi8(x[0xe], x[0xf]);

    const __m256i ABCD_03 = _mm256_unpacklo_epi16(AB_07, CD_07);
    const __m256i ABCD_47 = _mm256_unpackhi_epi16(AB_07, CD_07);
    const __m256i ABCD_8b = _mm256_unpacklo_epi16(AB_8f, CD_8f);
    const __m256i ABCD_cf = _mm256_unpackhi_epi16(AB_8f, CD_8f);
    const __m256i EFGH_03 = _mm256_unpacklo_epi16(EF_07, GH_07);
    const __m256i EFGH_47 = _mm256_unpackhi_epi16(EF_07, GH_07);
    const __m256i EFGH_8b = _mm256_unpacklo_epi16(EF_8f, GH_8f);
    const __m256i EFGH_cf = _mm256_unpackhi_epi16(EF_8f, GH_8f);
    const __m256i IJKL_03 = _mm256_unpacklo_epi16(IJ_07, KL_07);
    const __m256i IJKL_47 = _mm256_unpackhi_epi16(IJ_07, KL_07);
    const __m256i IJKL_8b = _mm256_unpacklo_epi16(IJ_8f, KL_8f);
    const __m256i IJKL_cf = _mm256_unpackhi_epi16(IJ_8f, KL_8f);
    const __m256i MNOP_03 = _mm256_unpacklo_epi16(MN_07, OP_07);
    const __m256i MNOP_47 = _mm256_unpackhi_epi16(MN_07, OP_07);
    const __m256i MNOP_8b = _mm256_unpacklo_epi16(MN_8f, OP_8f);
    const __m256i MNOP_cf = _mm256_unpackhi_epi16(MN_8f, OP_8f);

    const __m256i ABCDEFGH_01 = _mm256_unpacklo_epi32(ABCD_03, EFGH_03);
    const __m256i ABCDEFGH_23 = _mm256_unpackhi_epi32(ABCD_03, EFGH_03);
    const __m256i ABCDEFGH_45 = _mm256_unpacklo_epi32(ABCD_47, EFGH_47);
    const __m256i ABCDEFGH_67 = _mm256_unpackhi_epi32(ABCD_47, EFGH_47);
    const __m256i ABCDEFGH_89 = _mm256_unpacklo_epi32(ABCD_8b, EFGH_8b);
    const __m256i ABCDEFGH_ab = _mm256_unpackhi_epi32(ABCD_8b, EFGH_8b);
    const __m256i ABCDEFGH_cd = _mm256_unpacklo_epi32(ABCD_cf, EFGH_cf);
    const __m256i ABCDEFGH_ef = _mm256_unpackhi_epi32(ABCD_cf, EFGH_cf);
    const __m256i IJKLMNOP_01 = _mm256_unpacklo_epi32(IJKL_03, MNOP_03);
    const __m256i IJKLMNOP_23 = _mm256_unpackhi_epi32(IJKL_03, MNOP_03);
    const __m256i IJKLMNOP_45 = _mm256_unpacklo_epi32(IJKL_47, MNOP_47);
    const __m256i IJKLMNOP_67 = _mm256_unpackhi_epi32(IJKL_47, MNOP_47);
    const __m256i IJKLMNOP_89 = _mm256_unpacklo_epi32(IJKL_8b, MNOP_8b);
    const __m256i IJKLMNOP_ab = _mm256_unpackhi_epi32(IJKL_8b, MNOP_8b);
    const __m256i IJKLMNOP_cd = _mm256_unpacklo_epi32(IJKL_cf, MNOP_cf);
    const __m256i IJKLMNOP_ef = _mm256_unpackhi_epi32(IJKL_cf, MNOP_cf);

    x[0x0] = _mm256_unpacklo_epi64(ABCDEFGH_01, IJKLMNOP_01); // ABCDEFGHIJKLMNOP_0
    x[0x1] = _mm256_unpackhi_epi64(ABCDEFGH_01, IJKLMNOP_01); // ABCDEFGHIJKLMNOP_1
    x[0x2] = _mm256_unpacklo_epi64(ABCDEFGH_23, IJKLMNOP_23); // ABCDEFGHIJKLMNOP_2
    x[0x3] = _mm256_unpackhi_epi64(ABCDEFGH_23, IJKLMNOP_23); // ABCDEFGHIJKLMNOP_3
    x[0x4] = _mm256_unpacklo_epi64(ABCDEFGH_45, IJKLMNOP_45); // ABCDEFGHIJKLMNOP_4
    x[0x5] = _mm256_unpackhi_epi64(ABCDEFGH_45, IJKLMNOP_45); // ABCDEFGHIJKLMNOP_5
    x[0x6] = _mm256_unpacklo_epi64(ABCDEFGH_67, IJKLMNOP_67); // ABCDEFGHIJKLMNOP_6
    x[0x7] = _mm256_unpackhi_epi64(ABCDEFGH_67, IJKLMNOP_67); // ABCDEFGHIJKLMNOP_7
    x[0x8] = _mm256_unpacklo_epi64(ABCDEFGH_89, IJKLMNOP_89); // ABCDEFGHIJKLMNOP_8
    x[0x9] = _mm256_unpackhi_epi64(ABCDEFGH_89, IJKLMNOP_89); // ABCDEFGHIJKLMNOP_9
    x[0xa] = _mm256_unpacklo_epi64(ABCDEFGH_ab, IJKLMNOP_ab); // ABCDEFGHIJKLMNOP_a
    x[0xb] = _mm256_unpackhi_epi64(ABCDEFGH_ab, IJKLMNOP_ab); // ABCDEFGHIJKLMNOP_b
    x[0xc] = _mm256_unpacklo_epi64(ABCDEFGH_cd, IJKLMNOP_cd); // ABCDEFGHIJKLMNOP_c
    x[0xd] = _mm256_unpackhi_epi64(ABCDEFGH_cd, IJKLMNOP_cd); // ABCDEFGHIJKLMNOP_d
    x[0xe] = _mm256_unpacklo_epi64(ABCDEFGH_ef, IJKLMNOP_ef); // ABCDEFGHIJKLMNOP_e
    x[0xf] = _mm256_unpackhi_epi64(ABCDEFGH_ef, IJKLMNOP_ef); // ABCDEFGHIJKLMNOP_f
}

/// Transpose one 2x2 matrix of \c uint64_t stored in the folded (row 0, row 1) layout using AVX2 intrinsics
/**
* Held in 1 ymm register as x[0] = [row 0 | row 1], and produced the same way.
* Transposing a 2x2 matrix swaps the off-diagonal elements, which here is just
* the qword permute ([q0 q1 | q2 q3] -> [q0 q2 | q1 q3]) that finishes the
* larger folded overloads below.  No unpack levels are needed.
*/
static void
simd_transpose_folded(std::array<__m256i, 1>& x) noexcept
{
    constexpr int q0_q2_q1_q3 = 0b11'01'10'00;
    x[0] = _mm256_permute4x64_epi64(x[0], q0_q2_q1_q3);
}

/// Transpose one 4x4 matrix of \c uint32_t stored in the folded (row j, row j+2) layout using AVX2 intrinsics
/**
* Held in 2 ymm registers as x[j] = [row j | row j+2], and produced the same
* way.  Rows 0-1 (A-B) are in the low 128-bit lanes, rows 2-3 (C-D) in the
* high lanes.
*
* This is the same network as the 16x16 folded overload below, shrunk to one
* unpack level.  Per lane, the dword unpacks transpose the 2x4 submatrix, the
* qword unpacks pair column c with column c+2, and the final qword permute
* rejoins each column's halves.  See the 16x16 overload for the rationale.
*/
static void
simd_transpose_folded(std::array<__m256i, 2>& x) noexcept
{
    // Low lanes: rows A-B; high lanes: rows C-D (same network per lane).
    const __m256i AB_01 = _mm256_unpacklo_epi32(x[0], x[1]);
    const __m256i AB_23 = _mm256_unpackhi_epi32(x[0], x[1]);

    // Pair column c with column c+2 within each lane.
    const __m256i COL_02 = _mm256_unpacklo_epi64(AB_01, AB_23);
    const __m256i COL_13 = _mm256_unpackhi_epi64(AB_01, AB_23);

    constexpr int q0_q2_q1_q3 = 0b11'01'10'00;
    x[0] = _mm256_permute4x64_epi64(COL_02, q0_q2_q1_q3);
    x[1] = _mm256_permute4x64_epi64(COL_13, q0_q2_q1_q3);
}

/// Transpose one 8x8 matrix of \c uint16_t stored in the folded (row j, row j+4) layout using AVX2 intrinsics
/**
* Held in 4 ymm registers as x[j] = [row j | row j+4], and produced the same
* way.  Rows 0-3 (A-D) are in the low 128-bit lanes, rows 4-7 (E-H) in the
* high lanes.
*
* This is the same network as the 16x16 folded overload below, shrunk to two
* unpack levels.  Per lane, the word and dword unpacks transpose the 4x8
* submatrix, the qword unpacks pair column c with column c+4, and the final
* qword permute rejoins each column's halves.  See the 16x16 overload for the
* rationale.
*/
static void
simd_transpose_folded(std::array<__m256i, 4>& x) noexcept
{
    // Rows A-D are in the low lanes and rows E-H in the high lanes.  The
    // network is the same in each.
    const __m256i AB_03 = _mm256_unpacklo_epi16(x[0], x[1]);
    const __m256i AB_47 = _mm256_unpackhi_epi16(x[0], x[1]);
    const __m256i CD_03 = _mm256_unpacklo_epi16(x[2], x[3]);
    const __m256i CD_47 = _mm256_unpackhi_epi16(x[2], x[3]);

    // Per lane, two full 4-element columns of the lane's 4x8 submatrix.
    const __m256i ABCD_01 = _mm256_unpacklo_epi32(AB_03, CD_03);
    const __m256i ABCD_23 = _mm256_unpackhi_epi32(AB_03, CD_03);
    const __m256i ABCD_45 = _mm256_unpacklo_epi32(AB_47, CD_47);
    const __m256i ABCD_67 = _mm256_unpackhi_epi32(AB_47, CD_47);

    // Pair column c with column c+4 within each lane.
    const __m256i COL_04 = _mm256_unpacklo_epi64(ABCD_01, ABCD_45);
    const __m256i COL_15 = _mm256_unpackhi_epi64(ABCD_01, ABCD_45);
    const __m256i COL_26 = _mm256_unpacklo_epi64(ABCD_23, ABCD_67);
    const __m256i COL_37 = _mm256_unpackhi_epi64(ABCD_23, ABCD_67);

    constexpr int q0_q2_q1_q3 = 0b11'01'10'00;
    x[0] = _mm256_permute4x64_epi64(COL_04, q0_q2_q1_q3);
    x[1] = _mm256_permute4x64_epi64(COL_15, q0_q2_q1_q3);
    x[2] = _mm256_permute4x64_epi64(COL_26, q0_q2_q1_q3);
    x[3] = _mm256_permute4x64_epi64(COL_37, q0_q2_q1_q3);
}

/// Transpose one 16x16 matrix of \c uint8_t stored in the folded (row j, row j+8) layout using AVX2 intrinsics
/**
* Held in 8 ymm registers as x[j] = [row j | row j+8], and produced the same
* way, which is what lets consecutive transposes chain in registers without
* spilling the state to memory.  Rows 0-7 (A-H) are in the low 128-bit lanes,
* rows 8-15 (I-P) in the high lanes.
*
* The first three unpack levels are the standard byte-matrix network run per
* lane.  The low lanes transpose the top 8x16 submatrix (rows A-H) and the
* high lanes the bottom (rows I-P), leaving each lane of the level-4 outputs
* holding two 8-byte column vectors [col c | col c+8] of its submatrix.  A
* final qword permute ([q0 q1 | q2 q3] -> [q0 q2 | q1 q3]) rejoins the top and
* bottom halves of each column, restoring the folded layout.
*
* That is 32 in-lane unpacks and 8 cross-lane permutes.  The plain 16-register
* network needs 64 unpacks.
*/
static void
simd_transpose_folded(std::array<__m256i, 8>& x) noexcept
{
    // Rows A-H are in the low lanes and rows I-P in the high lanes.  The
    // network is the same in each.
    const __m256i AB_07 = _mm256_unpacklo_epi8(x[0], x[1]);
    const __m256i AB_8f = _mm256_unpackhi_epi8(x[0], x[1]);
    const __m256i CD_07 = _mm256_unpacklo_epi8(x[2], x[3]);
    const __m256i CD_8f = _mm256_unpackhi_epi8(x[2], x[3]);
    const __m256i EF_07 = _mm256_unpacklo_epi8(x[4], x[5]);
    const __m256i EF_8f = _mm256_unpackhi_epi8(x[4], x[5]);
    const __m256i GH_07 = _mm256_unpacklo_epi8(x[6], x[7]);
    const __m256i GH_8f = _mm256_unpackhi_epi8(x[6], x[7]);

    const __m256i ABCD_03 = _mm256_unpacklo_epi16(AB_07, CD_07);
    const __m256i ABCD_47 = _mm256_unpackhi_epi16(AB_07, CD_07);
    const __m256i ABCD_8b = _mm256_unpacklo_epi16(AB_8f, CD_8f);
    const __m256i ABCD_cf = _mm256_unpackhi_epi16(AB_8f, CD_8f);
    const __m256i EFGH_03 = _mm256_unpacklo_epi16(EF_07, GH_07);
    const __m256i EFGH_47 = _mm256_unpackhi_epi16(EF_07, GH_07);
    const __m256i EFGH_8b = _mm256_unpacklo_epi16(EF_8f, GH_8f);
    const __m256i EFGH_cf = _mm256_unpackhi_epi16(EF_8f, GH_8f);

    // Per lane, two full 8-byte columns of the lane's 8x16 submatrix.
    const __m256i ABCDEFGH_01 = _mm256_unpacklo_epi32(ABCD_03, EFGH_03);
    const __m256i ABCDEFGH_23 = _mm256_unpackhi_epi32(ABCD_03, EFGH_03);
    const __m256i ABCDEFGH_45 = _mm256_unpacklo_epi32(ABCD_47, EFGH_47);
    const __m256i ABCDEFGH_67 = _mm256_unpackhi_epi32(ABCD_47, EFGH_47);
    const __m256i ABCDEFGH_89 = _mm256_unpacklo_epi32(ABCD_8b, EFGH_8b);
    const __m256i ABCDEFGH_ab = _mm256_unpackhi_epi32(ABCD_8b, EFGH_8b);
    const __m256i ABCDEFGH_cd = _mm256_unpacklo_epi32(ABCD_cf, EFGH_cf);
    const __m256i ABCDEFGH_ef = _mm256_unpackhi_epi32(ABCD_cf, EFGH_cf);

    // Pair column c with column c+8 within each lane: per lane, COL_c8 =
    // [col c (8 bytes) | col c+8 (8 bytes)] of that lane's submatrix.
    const __m256i COL_08 = _mm256_unpacklo_epi64(ABCDEFGH_01, ABCDEFGH_89);
    const __m256i COL_19 = _mm256_unpackhi_epi64(ABCDEFGH_01, ABCDEFGH_89);
    const __m256i COL_2a = _mm256_unpacklo_epi64(ABCDEFGH_23, ABCDEFGH_ab);
    const __m256i COL_3b = _mm256_unpackhi_epi64(ABCDEFGH_23, ABCDEFGH_ab);
    const __m256i COL_4c = _mm256_unpacklo_epi64(ABCDEFGH_45, ABCDEFGH_cd);
    const __m256i COL_5d = _mm256_unpackhi_epi64(ABCDEFGH_45, ABCDEFGH_cd);
    const __m256i COL_6e = _mm256_unpacklo_epi64(ABCDEFGH_67, ABCDEFGH_ef);
    const __m256i COL_7f = _mm256_unpackhi_epi64(ABCDEFGH_67, ABCDEFGH_ef);

    // COL_c8 qwords are [c(top) c+8(top) | c(bottom) c+8(bottom)].  Swapping
    // the middle qwords joins each column's halves, giving [col c | col c+8],
    // which is [output row c | output row c+8].  That is the folded layout
    // again.
    constexpr int q0_q2_q1_q3 = 0b11'01'10'00;
    x[0] = _mm256_permute4x64_epi64(COL_08, q0_q2_q1_q3);
    x[1] = _mm256_permute4x64_epi64(COL_19, q0_q2_q1_q3);
    x[2] = _mm256_permute4x64_epi64(COL_2a, q0_q2_q1_q3);
    x[3] = _mm256_permute4x64_epi64(COL_3b, q0_q2_q1_q3);
    x[4] = _mm256_permute4x64_epi64(COL_4c, q0_q2_q1_q3);
    x[5] = _mm256_permute4x64_epi64(COL_5d, q0_q2_q1_q3);
    x[6] = _mm256_permute4x64_epi64(COL_6e, q0_q2_q1_q3);
    x[7] = _mm256_permute4x64_epi64(COL_7f, q0_q2_q1_q3);
}

#endif

#pragma GCC diagnostic pop

#elif defined(__aarch64__) && defined(__ARM_NEON)

/// Transpose \a x (treating it as a 2x2 matrix of \c uint64_t) using ARM Neon intrinsics
static void
simd_transpose(std::array<uint8x16_t, 2>& x) noexcept
{
    const uint64x2_t AB_0 = vzip1q_u64(vreinterpretq_u64_u8(x[0]), vreinterpretq_u64_u8(x[1]));
    const uint64x2_t AB_1 = vzip2q_u64(vreinterpretq_u64_u8(x[0]), vreinterpretq_u64_u8(x[1]));

    x[0] = vreinterpretq_u8_u64(AB_0);
    x[1] = vreinterpretq_u8_u64(AB_1);
}

/// Transpose \a x (treating it as a 4x4 matrix of \c uint32_t) using ARM Neon intrinsics
static void
simd_transpose(std::array<uint8x16_t, 4>& x) noexcept
{
    const uint32x4_t AB_01 = vzip1q_u32(vreinterpretq_u32_u8(x[0]), vreinterpretq_u32_u8(x[1]));
    const uint32x4_t AB_23 = vzip2q_u32(vreinterpretq_u32_u8(x[0]), vreinterpretq_u32_u8(x[1]));
    const uint32x4_t CD_01 = vzip1q_u32(vreinterpretq_u32_u8(x[2]), vreinterpretq_u32_u8(x[3]));
    const uint32x4_t CD_23 = vzip2q_u32(vreinterpretq_u32_u8(x[2]), vreinterpretq_u32_u8(x[3]));

    const uint64x2_t ABCD_0 = vzip1q_u64(vreinterpretq_u64_u32(AB_01), vreinterpretq_u64_u32(CD_01));
    const uint64x2_t ABCD_1 = vzip2q_u64(vreinterpretq_u64_u32(AB_01), vreinterpretq_u64_u32(CD_01));
    const uint64x2_t ABCD_2 = vzip1q_u64(vreinterpretq_u64_u32(AB_23), vreinterpretq_u64_u32(CD_23));
    const uint64x2_t ABCD_3 = vzip2q_u64(vreinterpretq_u64_u32(AB_23), vreinterpretq_u64_u32(CD_23));

    x[0] = vreinterpretq_u8_u64(ABCD_0);
    x[1] = vreinterpretq_u8_u64(ABCD_1);
    x[2] = vreinterpretq_u8_u64(ABCD_2);
    x[3] = vreinterpretq_u8_u64(ABCD_3);
}

/// Transpose \a x (treating it as a 8x8 matrix of \c uint16_t) using ARM Neon intrinsics
static void
simd_transpose(std::array<uint8x16_t, 8>& x) noexcept
{
    const uint16x8_t AB_03 = vzip1q_u16(vreinterpretq_u16_u8(x[0]), vreinterpretq_u16_u8(x[1]));
    const uint16x8_t AB_47 = vzip2q_u16(vreinterpretq_u16_u8(x[0]), vreinterpretq_u16_u8(x[1]));
    const uint16x8_t CD_03 = vzip1q_u16(vreinterpretq_u16_u8(x[2]), vreinterpretq_u16_u8(x[3]));
    const uint16x8_t CD_47 = vzip2q_u16(vreinterpretq_u16_u8(x[2]), vreinterpretq_u16_u8(x[3]));
    const uint16x8_t EF_03 = vzip1q_u16(vreinterpretq_u16_u8(x[4]), vreinterpretq_u16_u8(x[5]));
    const uint16x8_t EF_47 = vzip2q_u16(vreinterpretq_u16_u8(x[4]), vreinterpretq_u16_u8(x[5]));
    const uint16x8_t GH_03 = vzip1q_u16(vreinterpretq_u16_u8(x[6]), vreinterpretq_u16_u8(x[7]));
    const uint16x8_t GH_47 = vzip2q_u16(vreinterpretq_u16_u8(x[6]), vreinterpretq_u16_u8(x[7]));

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

    x[0] = vreinterpretq_u8_u64(ABCDEFGH_0);
    x[1] = vreinterpretq_u8_u64(ABCDEFGH_1);
    x[2] = vreinterpretq_u8_u64(ABCDEFGH_2);
    x[3] = vreinterpretq_u8_u64(ABCDEFGH_3);
    x[4] = vreinterpretq_u8_u64(ABCDEFGH_4);
    x[5] = vreinterpretq_u8_u64(ABCDEFGH_5);
    x[6] = vreinterpretq_u8_u64(ABCDEFGH_6);
    x[7] = vreinterpretq_u8_u64(ABCDEFGH_7);
}

/// Transpose \a x (treating it as a 16x16 matrix of \c uint8_t) using ARM Neon intrinsics
/**
* \sa https://codereview.stackexchange.com/questions/301656/16x16-byte-matrix-transpose-using-arm-neon-intrinsics-in-c
*/
static void
simd_transpose(std::array<uint8x16_t, 16>& x) noexcept
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

#endif
