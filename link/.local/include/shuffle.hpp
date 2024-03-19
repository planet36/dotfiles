// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Wrapper for \c std::shuffle with the \c per_thread_random_number_engine given as the URBG
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/algorithm/random_shuffle
*/

#pragma once

#include "rand.hpp"

#include <algorithm>
#include <concepts>

template <std::random_access_iterator RandomIt>
void
shuffle(RandomIt first, RandomIt last)
{
	std::shuffle(first, last, per_thread_random_number_engine);
}
