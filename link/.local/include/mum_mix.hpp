// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// MUM mix
/**
\file
\author Steven Ward
\sa https://github.com/vnmakarov/mum-hash
\sa https://github.com/vnmakarov/mum-hash/blob/master/mum.h#L104
\sa https://github.com/vnmakarov/mum-hash/blob/master/mum-prng.h#L74
*/

#pragma once

#if !defined(__SIZEOF_INT128__)
#error "__SIZEOF_INT128__ not defined"
#endif

#include "int_parts_union.hpp"

/// Multiply 64-bit \a V and \a P and return sum of high and low parts of the result.
constexpr uint64_t
mum_mix_add(const uint64_t v, const uint64_t p)
{
	const int_parts<uint64_t> r{.whole = __uint128_t{v} * p};
	/* We could use XOR here too but, for some reasons, on Haswell and
	Power7 using an addition improves hashing performance by 10% for
	small strings.  */
	return r.parts[1] + r.parts[0];
}

/// Multiply 64-bit \a V and \a P and return xor of high and low parts of the result.
constexpr uint64_t
mum_mix_xor(const uint64_t v, const uint64_t p)
{
	const int_parts<uint64_t> r{.whole = __uint128_t{v} * p};
	return r.parts[1] ^ r.parts[0];
}
