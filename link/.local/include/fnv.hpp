// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// constexpr FNV hash functions for string_view
/**
\file
\author Steven Ward
\sa http://www.isthe.com/chongo/tech/comp/fnv/index.html
\sa https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
\sa https://www.ietf.org/archive/id/draft-eastlake-fnv-02.txt
*/

#pragma once

#include <string_view>

constexpr uint32_t fnv_prime_32 = UINT32_C(16'777'619); // = 2**24 + 2**8 + 0x93
constexpr uint64_t fnv_prime_64 = UINT64_C(1'099'511'628'211); // = 2**40 + 2**8 + 0xB3

constexpr uint32_t fnv_offset_basis_32 = UINT32_C(2'166'136'261);
constexpr uint64_t fnv_offset_basis_64 = UINT64_C(14'695'981'039'346'656'037);

/// FNV-1 32-bit hash
constexpr uint32_t fnv1_32(const std::string_view& s)
{
	uint32_t result = fnv_offset_basis_32;

	for (const unsigned char octet : s)
	{
		result *= fnv_prime_32;
		result ^= octet;
	}

	return result;
}

/// FNV-1a 32-bit hash
constexpr uint32_t fnv1a_32(const std::string_view& s)
{
	uint32_t result = fnv_offset_basis_32;

	for (const unsigned char octet : s)
	{
		result ^= octet;
		result *= fnv_prime_32;
	}

	return result;
}

/// FNV-1 64-bit hash
constexpr uint64_t fnv1_64(const std::string_view& s)
{
	uint64_t result = fnv_offset_basis_64;

	for (const unsigned char octet : s)
	{
		result *= fnv_prime_64;
		result ^= octet;
	}

	return result;
}

/// FNV-1a 64-bit hash
constexpr uint64_t fnv1a_64(const std::string_view& s)
{
	uint64_t result = fnv_offset_basis_64;

	for (const unsigned char octet : s)
	{
		result ^= octet;
		result *= fnv_prime_64;
	}

	return result;
}
