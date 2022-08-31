// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get a uniformly distributed random number within an interval
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/experimental/randint
*/

#pragma once

#include "int_bytes.hpp"
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
"Fast Random Integer Generation in an Interval" by Daniel Lemire
\sa https://arxiv.org/abs/1805.10941
\return a uniformly distributed random unsigned integer within the interval [0, \a s)
*/
template <std::unsigned_integral T>
T
rand_uint_half_open(const T s)
{
	if (s == 1)
		return 0;

	if (s == 0)
		return rand_int<T>();

	using T2 = next_larger<T>;
	T2 m;

	m = rand_int<T>(); // x in [0, 2^L)
	m *= s; // x in [0, s * 2^L)
	if (static_cast<T>(m) < s)
	{
		const T min = std::numeric_limits<T>::max() % s; // 2^L mod s
		while (static_cast<T>(m) < min)
		{
			m = rand_int<T>(); // x in [0, 2^L)
			m *= s; // x in [0, s * 2^L)
		}
	}

	return m >> std::numeric_limits<T>::digits; // in [0, s)
}

/**
\return a uniformly distributed random floating-point number within the interval [0, 1)
*/
float
rand_float_unit()
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
rand_double_unit()
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
rand_long_double_unit()
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
	return rand_float_unit() * (b - a) + a;
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
double
rand_double(const double a, const double b)
{
	return rand_double_unit() * (b - a) + a;
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
long double
rand_long_double(const long double a, const long double b)
{
	return rand_long_double_unit() * (b - a) + a;
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
