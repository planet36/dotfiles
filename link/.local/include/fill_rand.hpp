// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Fill a buffer with random values
/**
\file
\author Steven Ward
*/

#pragma once

#include <array>
#include <vector>

#if defined(_GLIBCXX_HAVE_ARC4RANDOM)

#include <cstdlib>

// arc4random_buf
// https://www.gnu.org/software/libc/manual/html_node/High-Quality-Random.html

template <typename T>
void
fill_rand(T& x) noexcept
{
	arc4random_buf(&x, sizeof(T));
}

template <typename T, size_t N>
void
fill_rand(std::array<T, N>& container) noexcept
{
	arc4random_buf(std::data(container), sizeof(T) * std::size(container));
}

template <typename T>
void
fill_rand(std::vector<T>& container) noexcept
{
	arc4random_buf(std::data(container), sizeof(T) * std::size(container));
}

#elif defined(_GLIBCXX_HAVE_GETENTROPY)

#include <system_error>
#include <unistd.h>

// getentropy
// https://www.gnu.org/software/libc/manual/html_node/Unpredictable-Bytes.html
// Max num bytes allowed is 256

template <typename T>
requires (sizeof(T) <= 256)
void
fill_rand(T& x)
{
	if (getentropy(&x, sizeof(T)) < 0)
	{
		throw std::system_error(std::make_error_code(std::errc{errno}),
		                        "getentropy");
	}
}

template <typename T, size_t N>
requires (sizeof(T) * N <= 256)
void
fill_rand(std::array<T, N>& container)
{
	if (getentropy(std::data(container), sizeof(T) * std::size(container)) < 0)
	{
		throw std::system_error(std::make_error_code(std::errc{errno}),
		                        "getentropy");
	}
}

template <typename T>
void
fill_rand(std::vector<T>& container)
{
	if (getentropy(std::data(container), sizeof(T) * std::size(container)) < 0)
	{
		throw std::system_error(std::make_error_code(std::errc{errno}),
		                        "getentropy");
	}
}

#else

#include "int_join.hpp"

#include <concepts>
#include <random>
#include <utility>

template <std::unsigned_integral T>
void
fill_rand(T& x)
{
	static std::random_device rd;

	// std::random_device::result_type is unsigned int
	// https://en.cppreference.com/w/cpp/numeric/random/random_device
	if constexpr (sizeof(T) <= sizeof(typename std::random_device::result_type))
		x = rd();
	else if constexpr (sizeof(T) <=
	                   2 * sizeof(typename std::random_device::result_type))
		x = int_join(rd(), rd());
	else
		std::unreachable();
}

template <std::unsigned_integral T, size_t N>
void
fill_rand(std::array<T, N>& container)
{
	static std::random_device rd;

	for (T& x : container)
	{
		// std::random_device::result_type is unsigned int
		// https://en.cppreference.com/w/cpp/numeric/random/random_device
		if constexpr (sizeof(T) <=
		              sizeof(typename std::random_device::result_type))
			x = rd();
		else if constexpr (sizeof(T) <=
		                   2 * sizeof(typename std::random_device::result_type))
			x = int_join(rd(), rd());
		else
			std::unreachable();
	}
}

template <std::unsigned_integral T>
void
fill_rand(std::vector<T>& container)
{
	static std::random_device rd;

	for (T& x : container)
	{
		// std::random_device::result_type is unsigned int
		// https://en.cppreference.com/w/cpp/numeric/random/random_device
		if constexpr (sizeof(T) <=
		              sizeof(typename std::random_device::result_type))
			x = rd();
		else if constexpr (sizeof(T) <=
		                   2 * sizeof(typename std::random_device::result_type))
			x = int_join(rd(), rd());
		else
			std::unreachable();
	}
}

#endif
