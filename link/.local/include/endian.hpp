// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// functions to reverse bytes and determine machine endianness (i.e. big endian, little endian)
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/Endianness
*/

#pragma once

#include <bit>
#include <cstdint>

// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
// https://clang.llvm.org/docs/LanguageExtensions.html
constexpr uint16_t rev_2_bytes(uint16_t x) {return __builtin_bswap16(x);}
constexpr uint32_t rev_4_bytes(uint32_t x) {return __builtin_bswap32(x);}
constexpr uint64_t rev_8_bytes(uint64_t x) {return __builtin_bswap64(x);}
#if defined(__SIZEOF_INT128__)
constexpr __uint128_t rev_16_bytes(__uint128_t x) {return __builtin_bswap128(x);}
#endif

template <typename T>
requires (sizeof(T) == 1)
constexpr T
rev_bytes(T x)
{
	return x;
}

template <typename T>
requires (sizeof(T) == 2)
constexpr T
rev_bytes(T x)
{
	return std::bit_cast<T>(rev_2_bytes(std::bit_cast<uint16_t>(x)));
}

template <typename T>
requires (sizeof(T) == 4)
constexpr T
rev_bytes(T x)
{
	return std::bit_cast<T>(rev_4_bytes(std::bit_cast<uint32_t>(x)));
}

template <typename T>
requires (sizeof(T) == 8)
constexpr T
rev_bytes(T x)
{
	return std::bit_cast<T>(rev_8_bytes(std::bit_cast<uint64_t>(x)));
}

#if defined(__SIZEOF_INT128__)
template <typename T>
requires (sizeof(T) == 16)
constexpr T
rev_bytes(T x)
{
	return std::bit_cast<T>(rev_16_bytes(std::bit_cast<__uint128_t>(x)));
}
#endif

static_assert(std::endian::native == std::endian::little ||
              std::endian::native == std::endian::big);

constexpr bool
h_is_be()
{
	return std::endian::native == std::endian::big;
}

constexpr bool
h_is_le()
{
	return std::endian::native == std::endian::little;
}

template <typename T>
constexpr T
h_to_be(const T x)
{
	if constexpr (h_is_be())
		return x;
	else
		return rev_bytes(x);
}

template <typename T>
constexpr T
h_to_le(const T x)
{
	if constexpr (h_is_le())
		return x;
	else
		return rev_bytes(x);
}

template <typename T>
constexpr T
be_to_h(const T x)
{
	if constexpr (h_is_be())
		return x;
	else
		return rev_bytes(x);
}

template <typename T>
constexpr T
le_to_h(const T x)
{
	if constexpr (h_is_le())
		return x;
	else
		return rev_bytes(x);
}
