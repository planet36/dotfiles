// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// SIMD types used with intrinsic/built-in functions
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html
\sa https://clang.llvm.org/docs/LanguageExtensions.html#vectors-and-extended-vectors
\sa https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html
\sa https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html
\sa https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/details-about-sse-intrinsics.html
\sa https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/xmmintrin.h
\sa https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/emmintrin.h
\sa https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/avxintrin.h
\sa https://gcc.gnu.org/onlinedocs/gcc/x86-Built-in-Functions.html
\sa https://developer.arm.com/documentation/den0018/a/NEON-Intrinsics/Vector-data-types-for-NEON-intrinsics?lang=en
*/

#pragma once

#include <cstring>

#define DECLARE_SIMD_TYPE(T, TNAME, N) \
using TNAME ## x ## N = [[gnu::vector_size(sizeof(T)*N), gnu::warn_if_not_aligned(sizeof(T)*N)]] T; \
static_assert(sizeof(TNAME ## x ## N) == sizeof(T)*N); \
static_assert(alignof(TNAME ## x ## N) == sizeof(T)*N);

// 128-bit types

DECLARE_SIMD_TYPE(signed char  , i8, 16)
DECLARE_SIMD_TYPE(unsigned char, u8, 16)

DECLARE_SIMD_TYPE(short         , i16, 8)
DECLARE_SIMD_TYPE(unsigned short, u16, 8)

DECLARE_SIMD_TYPE(int         , i32, 4)
DECLARE_SIMD_TYPE(unsigned int, u32, 4)
DECLARE_SIMD_TYPE(float       , f32, 4) // == __m128

DECLARE_SIMD_TYPE(long long         , i64, 2) // == __m128i
DECLARE_SIMD_TYPE(unsigned long long, u64, 2)
DECLARE_SIMD_TYPE(double            , f64, 2) // == __m128d

// 256-bit types

DECLARE_SIMD_TYPE(signed char  , i8, 32)
DECLARE_SIMD_TYPE(unsigned char, u8, 32)

DECLARE_SIMD_TYPE(short         , i16, 16)
DECLARE_SIMD_TYPE(unsigned short, u16, 16)

DECLARE_SIMD_TYPE(int         , i32, 8)
DECLARE_SIMD_TYPE(unsigned int, u32, 8)
DECLARE_SIMD_TYPE(float       , f32, 8) // == __m256

DECLARE_SIMD_TYPE(long long         , i64, 4) // == __m256i
DECLARE_SIMD_TYPE(unsigned long long, u64, 4)
DECLARE_SIMD_TYPE(double            , f64, 4) // == __m256d

union simd128
{
	i8x16 i8;
	u8x16 u8;

	i16x8 i16;
	u16x8 u16;

	i32x4 i32;
	u32x4 u32;
	f32x4 f32;

	i64x2 i64;
	u64x2 u64;
	f64x2 f64;

	bool operator==(const simd128& that) const
	{
		return std::memcmp(this, &that, sizeof(simd128)) == 0;
	}

	bool operator!=(const simd128& that) const {return !(*this == that);}
};
static_assert(sizeof(simd128) == 16);
static_assert(alignof(simd128) == 16);

union simd256
{
	i8x32 i8;
	u8x32 u8;

	i16x16 i16;
	u16x16 u16;

	i32x8 i32;
	u32x8 u32;
	f32x8 f32;

	i64x4 i64;
	u64x4 u64;
	f64x4 f64;

	bool operator==(const simd256& that) const
	{
		return std::memcmp(this, &that, sizeof(simd256)) == 0;
	}

	bool operator!=(const simd256& that) const {return !(*this == that);}
};
static_assert(sizeof(simd256) == 32);
static_assert(alignof(simd256) == 32);
