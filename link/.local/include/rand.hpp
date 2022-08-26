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
#include "make_unit_float.hpp"
#include "wyrand.hpp"

#include <concepts>
#include <limits>
#include <random>

/**
\pre \a a <= \a b
\sa https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
\return a uniformly distributed random integer within the interval [\a a, \a b]
*/
template <integral_number T>
T
rand_int(const T a, const T b)
{
	static thread_local wyrand gen;
	static_assert(std::numeric_limits<decltype(gen)::result_type>::digits >=
	              std::numeric_limits<T>::digits);
	return std::uniform_int_distribution<T>{a, b}(gen);
}

/**
\sa https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
\return a uniformly distributed random integer within the interval [min, \a b]
*/
template <integral_number T>
T
rand_int(const T b)
{
	return rand_int(std::numeric_limits<T>::min(), b);
}

/**
\return a uniformly distributed random integer within the interval [min, max]
*/
template <integral_number T>
T
rand_int()
{
	static thread_local wyrand gen;
	static_assert(std::numeric_limits<decltype(gen)::result_type>::digits >=
	              std::numeric_limits<T>::digits);
	return gen.next();
}

/**
\return a uniformly distributed random floating-point number within the interval [0, 1)
*/
float
rand_unit_float()
{
	static thread_local wyrand gen;
	static_assert(std::numeric_limits<decltype(gen)::result_type>::digits >=
	              std::numeric_limits<float>::digits);
	return make_unit_float(gen.next());
}

/**
\return a uniformly distributed random floating-point number within the interval [0, 1)
*/
double
rand_unit_double()
{
	static thread_local wyrand gen;
	static_assert(std::numeric_limits<decltype(gen)::result_type>::digits >=
	              std::numeric_limits<double>::digits);
	return make_unit_double(gen.next());
}

/**
\return a uniformly distributed random floating-point number within the interval [0, 1)
*/
long double
rand_unit_long_double()
{
	static thread_local wyrand gen;
	static_assert(std::numeric_limits<decltype(gen)::result_type>::digits >=
	              std::numeric_limits<long double>::digits);
	return make_unit_long_double(gen.next());
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
float
rand_float(const float a, const float b)
{
	return rand_unit_float() * (b - a) + a;
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
double
rand_double(const double a, const double b)
{
	return rand_unit_double() * (b - a) + a;
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
long double
rand_long_double(const long double a, const long double b)
{
	return rand_unit_long_double() * (b - a) + a;
}

/**
* \sa https://martin.ankerl.com/2018/12/08/fast-random-bool/
* \sa https://gist.github.com/martinus/c43d99ad0008e11fcdbf06982e25f464
*/
bool
rand_bool()
{
	static constexpr uint64_t mask64_one_msb = UINT64_C(1) << 63;
	static thread_local wyrand gen;
	static thread_local uint64_t x = 1;

	if (x == 1) [[unlikely]]
	{
		x = gen.next() | mask64_one_msb;
	}

	const bool ret = x & 1;
	x >>= 1;
	return ret;
}
