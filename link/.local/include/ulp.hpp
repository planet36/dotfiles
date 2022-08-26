// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Unit in Last Place (ULP) function
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/Unit_in_the_last_place
*/

#pragma once

#include "float_bits_union.hpp"

#include <cmath>
#include <concepts>
#include <limits>

/// get the Unit in Last Place (ULP) of \a x
/**
\sa https://github.com/sonyomega/physbam_public/blob/master/PhysBAM_Tools/Math_Tools/ulp.h
\sa https://searchcode.com/file/98565256/PhysBAM_Tools/Math_Tools/ulp.h
*/
template <std::floating_point T>
requires std::numeric_limits<T>::is_iec559
T
ulp(T x)
{
	x = std::abs(x);

	if (std::isinf(x))
		return x;

	float_bits_union<sizeof(T)> u{.f = x};
	u.i ^= 1;

	return u.i & 1 ? u.f - x : x - u.f;
}
