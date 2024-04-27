// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// constexpr FNV hash functions for \c std::string_view
/**
\file
\author Steven Ward
\sa http://www.isthe.com/chongo/tech/comp/fnv/index.html
\sa https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
\sa https://www.ietf.org/archive/id/draft-eastlake-fnv-02.txt
*/

#pragma once

#include <cstdint>
#include <iterator>
#include <string_view>

/*
https://www.wolframalpha.com/input?i=PrimeQ%5B16777619%5D
https://www.wolframalpha.com/input?i=PrimeQ%5B1099511628211%5D
*/
inline constexpr uint32_t fnv_prime_32 = UINT32_C(16'777'619); // = 2**24 + 2**8 + 0x93
inline constexpr uint64_t fnv_prime_64 = UINT64_C(1'099'511'628'211); // = 2**40 + 2**8 + 0xB3

inline constexpr uint32_t fnv_offset_basis_32 = UINT32_C(2'166'136'261);
inline constexpr uint64_t fnv_offset_basis_64 = UINT64_C(14'695'981'039'346'656'037);

/// FNV-1 32-bit hash
constexpr auto
fnv1_32(const std::string_view s)
{
	auto result = fnv_offset_basis_32;

	for (const auto c : s)
	{
		const auto octet = static_cast<uint8_t>(c);
		result *= fnv_prime_32;
		result ^= octet;
	}

	return result;
}

/// FNV-1a 32-bit hash
constexpr auto
fnv1a_32(const std::string_view s)
{
	auto result = fnv_offset_basis_32;

	for (const auto c : s)
	{
		const auto octet = static_cast<uint8_t>(c);
		result ^= octet;
		result *= fnv_prime_32;
	}

	return result;
}

/// FNV-1 64-bit hash
constexpr auto
fnv1_64(const std::string_view s)
{
	auto result = fnv_offset_basis_64;

	for (const auto c : s)
	{
		const auto octet = static_cast<uint8_t>(c);
		result *= fnv_prime_64;
		result ^= octet;
	}

	return result;
}

/// FNV-1a 64-bit hash
constexpr auto
fnv1a_64(const std::string_view s)
{
	auto result = fnv_offset_basis_64;

	for (const auto c : s)
	{
		const auto octet = static_cast<uint8_t>(c);
		result ^= octet;
		result *= fnv_prime_64;
	}

	return result;
}

/// FNV-1 32-bit hash
template <std::input_iterator Iter>
requires (sizeof(std::iter_value_t<Iter>) == 1)
constexpr auto
fnv1_32(Iter first, const Iter last)
{
	auto result = fnv_offset_basis_32;

	while (first != last)
	{
		result *= fnv_prime_32;
		result ^= static_cast<uint8_t>(*first);
		++first;
	}

	return result;
}

/// FNV-1a 32-bit hash
template <std::input_iterator Iter>
requires (sizeof(std::iter_value_t<Iter>) == 1)
constexpr auto
fnv1a_32(Iter first, const Iter last)
{
	auto result = fnv_offset_basis_32;

	while (first != last)
	{
		result ^= static_cast<uint8_t>(*first);
		result *= fnv_prime_32;
		++first;
	}

	return result;
}

/// FNV-1 64-bit hash
template <std::input_iterator Iter>
requires (sizeof(std::iter_value_t<Iter>) == 1)
constexpr auto
fnv1_64(Iter first, const Iter last)
{
	auto result = fnv_offset_basis_64;

	while (first != last)
	{
		result *= fnv_prime_64;
		result ^= static_cast<uint8_t>(*first);
		++first;
	}

	return result;
}

/// FNV-1a 64-bit hash
template <std::input_iterator Iter>
requires (sizeof(std::iter_value_t<Iter>) == 1)
constexpr auto
fnv1a_64(Iter first, const Iter last)
{
	auto result = fnv_offset_basis_64;

	while (first != last)
	{
		result ^= static_cast<uint8_t>(*first);
		result *= fnv_prime_64;
		++first;
	}

	return result;
}
