// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// similar to \c std::copysign but for signed integers
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/numeric/math/copysign
*/

#pragma once

#include "make_negative.hpp"

#include <concepts>
#include <cstdlib>

constexpr auto
icopysign(const std::signed_integral auto mag, const std::signed_integral auto sgn)
{
	if (sgn < 0)
		return make_negative(mag);
	else
		return std::abs(mag);
}
