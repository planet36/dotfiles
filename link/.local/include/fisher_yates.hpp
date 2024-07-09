// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Fisher-Yates shuffle
/**
\file
\author Steven Ward
\sa https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
*/

#pragma once

#include "rand.hpp"

#include <algorithm>
#include <ranges>

/**
\sa https://en.cppreference.com/w/cpp/ranges/random_access_range
*/
void
fisher_yates(std::ranges::random_access_range auto& container)
{
	for (size_t i = std::size(container); i > 1;)
	{
		const size_t j = rand_uint_range(i); // [0, i)
		i--; // must decrement after choosing random number, not before

		if (i != j)
		{
			std::swap(container[i], container[j]);
		}
	}
}
