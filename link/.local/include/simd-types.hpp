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
*/

#pragma once

#include <cstring>

#define DECLARE_SIMD_TYPE(N, T, TNAME) \
using v ## N ## TNAME = [[gnu::vector_size(sizeof(T)*N), gnu::warn_if_not_aligned(sizeof(T)*N)]] T; \
static_assert(sizeof(v ## N ## TNAME) == sizeof(T)*N); \
static_assert(alignof(v ## N ## TNAME) == sizeof(T)*N);

// 128-bit types

DECLARE_SIMD_TYPE(16, signed char, i8) // v16i8
DECLARE_SIMD_TYPE(16, unsigned char, u8) // v16u8

DECLARE_SIMD_TYPE(8, short, i16) // v8i16
DECLARE_SIMD_TYPE(8, unsigned short, u16) // v8u16

DECLARE_SIMD_TYPE(4, int, i32) // v4i32
DECLARE_SIMD_TYPE(4, unsigned int, u32) // v4u32
DECLARE_SIMD_TYPE(4, float, f32) // v4f32 == __m128

DECLARE_SIMD_TYPE(2, long long, i64) // v2i64 == __m128i
DECLARE_SIMD_TYPE(2, unsigned long long, u64) // v2u64
DECLARE_SIMD_TYPE(2, double, f64) // v2f64 == __m128d

// 256-bit types

DECLARE_SIMD_TYPE(32, signed char, i8) // v32i8
DECLARE_SIMD_TYPE(32, unsigned char, u8) // v32u8

DECLARE_SIMD_TYPE(16, short, i16) // v16i16
DECLARE_SIMD_TYPE(16, unsigned short, u16) // v16u16

DECLARE_SIMD_TYPE(8, int, i32) // v8i32
DECLARE_SIMD_TYPE(8, unsigned int, u32) // v8u32
DECLARE_SIMD_TYPE(8, float, f32) // v8f32 == __m256

DECLARE_SIMD_TYPE(4, long long, i64) // v4i64 == __m256i
DECLARE_SIMD_TYPE(4, unsigned long long, u64) // v4u64
DECLARE_SIMD_TYPE(4, double, f64) // v4f64 == __m256d

union simd128
{
	v16i8 i8;
	v16u8 u8;

	v8i16 i16;
	v8u16 u16;

	v4i32 i32;
	v4u32 u32;
	v4f32 f32;

	v2i64 i64;
	v2u64 u64;
	v2f64 f64;

	bool operator==(const simd128& that) const
	{
		return std::memcmp(this, &that, sizeof(simd128)) == 0;
	}
};
static_assert(sizeof(simd128) == 16);
static_assert(alignof(simd128) == 16);

union simd256
{
	v32i8 i8;
	v32u8 u8;

	v16i16 i16;
	v16u16 u16;

	v8i32 i32;
	v8u32 u32;
	v8f32 f32;

	v4i64 i64;
	v4u64 u64;
	v4f64 f64;

	bool operator==(const simd256& that) const
	{
		return std::memcmp(this, &that, sizeof(simd256)) == 0;
	}
};
static_assert(sizeof(simd256) == 32);
static_assert(alignof(simd256) == 32);
