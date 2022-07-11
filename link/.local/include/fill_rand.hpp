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
#include <random>
#include <system_error>
#include <unistd.h>
#include <utility>

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

// https://man7.org/linux/man-pages/man3/getentropy.3.html
// Max num bytes allowed is 256

template <std::unsigned_integral T, size_t N>
requires (sizeof(T) * N <= 256)
void
getentropy(std::array<T, N>& arr)
{
	if (getentropy(arr.data(), sizeof(T) * N) < 0)
	{
		throw std::system_error(std::make_error_code(std::errc(errno)),
		                        "getentropy");
	}
}

template <std::unsigned_integral T>
requires (sizeof(T) <= 256)
void
getentropy(T& x)
{
	if (getentropy(&x, sizeof(T)) < 0)
	{
		throw std::system_error(std::make_error_code(std::errc(errno)),
		                        "getentropy");
	}
}
