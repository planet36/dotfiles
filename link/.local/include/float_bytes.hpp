// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// compile-time typing of floats based on a given byte size
/**
\file
\author Steven Ward
\sa https://peter.bloomfield.online/using-cpp-templates-for-size-based-type-selection/
*/

#pragma once

#include <type_traits>

template <unsigned int N>
using float_bytes =
std::conditional_t<N <= sizeof(float), float,
	std::conditional_t<N <= sizeof(double), double,
		std::conditional_t<N <= sizeof(long double), long double,
			void
		>
	>
>;
