// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get a uniformly distributed random number within an interval
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/experimental/randint
*/

#pragma once

#include "integral_number.hpp"
#include "xoshiro.hpp"

#include <concepts>
#include <limits>
#include <random>

/**
\pre \a a <= \a b
\sa https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
\return a uniformly distributed random integer within the interval [\a a, \a b]
*/
template <integral_number T>
T rand_int(const T a = std::numeric_limits<T>::min(), const T b = std::numeric_limits<T>::max())
{
	static thread_local xoshiro256starstar gen;
	return std::uniform_int_distribution<T>{a, b}(gen);
}

/**
\pre \a a < \a b
\sa https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
\return a uniformly distributed random floating point number within the interval [\a a, \a b)
*/
template <std::floating_point T>
T rand_float(const T a, const T b)
{
	static thread_local xoshiro256plus gen;
	return std::uniform_real_distribution<T>{a, b}(gen);
}
