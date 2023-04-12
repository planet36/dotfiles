// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Cast integer to floating-point of sufficient precision
/**
\file
\author Steven Ward
*/

#pragma once

#include "float_bytes.hpp"

#include <concepts>
#include <limits>


constexpr auto
i_to_f(const std::integral auto x)
{
	using result_type = float_bits<std::numeric_limits<decltype(x)>::digits>;
	return static_cast<result_type>(x);
}
