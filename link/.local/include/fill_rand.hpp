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

template <std::unsigned_integral T, size_t N>
void fill_rand(std::array<T, N>& arr)
{
	std::random_device rd;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		// std::random_device::result_type is unsigned int
		// https://en.cppreference.com/w/cpp/numeric/random/random_device
		if constexpr (sizeof (T) <= sizeof (typename std::random_device::result_type))
			arr[i] = rd();
		else
			arr[i] = int_join(rd(), rd());
	}
}

template <std::unsigned_integral T>
void fill_rand(T& x)
{
	std::random_device rd;
	// std::random_device::result_type is unsigned int
	// https://en.cppreference.com/w/cpp/numeric/random/random_device
	if constexpr (sizeof (T) <= sizeof (typename std::random_device::result_type))
		x = rd();
	else
		x = int_join(rd(), rd());
}
