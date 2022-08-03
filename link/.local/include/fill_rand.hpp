// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Fill an array of unsigned ints with random values
/**
\file
\author Steven Ward
*/

#pragma once

#include "int_join.hpp"

#include <array>
#include <concepts>
#include <cstdlib>
#include <random>
#include <system_error>
#include <unistd.h>
#include <utility>

#if defined(_GLIBCXX_HAVE_GETENTROPY) && defined(_GLIBCXX_HAVE_ARC4RANDOM)

// getentropy
// https://www.gnu.org/software/libc/manual/html_node/Unpredictable-Bytes.html
// Max num bytes allowed is 256

// arc4random_buf
// https://www.gnu.org/software/libc/manual/html_node/High-Quality-Random.html

template <std::unsigned_integral T, size_t N>
void
fill_rand(std::array<T, N>& arr)
{
	if constexpr (sizeof(T) * N <= 256)
	{
		if (getentropy(arr.data(), sizeof(T) * N) < 0)
		{
			throw std::system_error(std::make_error_code(std::errc(errno)),
			                        "getentropy");
		}
	}
	else
	{
		arc4random_buf(arr.data(), sizeof(T) * N);
	}
}

template <std::unsigned_integral T>
void
fill_rand(T& x)
{
	if constexpr (sizeof(T) <= 256)
	{
		if (getentropy(&x, sizeof(T)) < 0)
		{
			throw std::system_error(std::make_error_code(std::errc(errno)),
			                        "getentropy");
		}
	}
	else
	{
		arc4random_buf(&x, sizeof(T));
	}
}

#else

template <std::unsigned_integral T, size_t N>
void
fill_rand(std::array<T, N>& arr)
{
	static std::random_device rd;

	for (size_t i = 0; i < arr.size(); ++i)
	{
		// std::random_device::result_type is unsigned int
		// https://en.cppreference.com/w/cpp/numeric/random/random_device
		if constexpr (sizeof(T) <= sizeof(typename std::random_device::result_type))
			arr[i] = rd();
		else if constexpr (sizeof(T) <= 2*sizeof(typename std::random_device::result_type))
			arr[i] = int_join(rd(), rd());
		else
			std::unreachable();
	}
}

template <std::unsigned_integral T>
void
fill_rand(T& x)
{
	static std::random_device rd;

	// std::random_device::result_type is unsigned int
	// https://en.cppreference.com/w/cpp/numeric/random/random_device
	if constexpr (sizeof(T) <= sizeof(typename std::random_device::result_type))
		x = rd();
	else if constexpr (sizeof(T) <= 2*sizeof(typename std::random_device::result_type))
		x = int_join(rd(), rd());
	else
		std::unreachable();
}

#endif
