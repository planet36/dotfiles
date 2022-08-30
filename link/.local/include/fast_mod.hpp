// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Fast modulus
/**
\file
\author Steven Ward
\sa https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>
#include <limits>

template <std::unsigned_integral T>
constexpr T
fast_mod(const T x, const T N)
{
	//return x % N;
	return (static_cast<next_larger<T>>(x) * N) >> std::numeric_limits<T>::digits;
}
