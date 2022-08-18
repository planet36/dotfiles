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

#include "int_parts_union.hpp"

/// Multiply \a V and \a P and return the sum of high and low parts of the result.
template <std::unsigned_integral T>
constexpr T
mum_mix_add(const T v, const T p)
{
	const int_parts<T> r{.whole = static_cast<next_larger<T>>(v) * p};
	return r.parts[1] + r.parts[0];
}

/// Multiply \a V and \a P and return the XOR of high and low parts of the result.
template <std::unsigned_integral T>
constexpr T
mum_mix_xor(const T v, const T p)
{
	const int_parts<T> r{.whole = static_cast<next_larger<T>>(v) * p};
	return r.parts[1] ^ r.parts[0];
}
