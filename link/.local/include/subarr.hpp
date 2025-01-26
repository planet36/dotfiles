// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get a sub-array (analogous to \c std::string::substr)
/**
\file
\author Steven Ward
*/

#pragma once

#include <algorithm>
#include <array>

template <size_t POS, size_t COUNT, typename T, size_t N>
constexpr std::array<T, COUNT>
subarr(const std::array<T, N>& arr)
{
	static_assert(N >= COUNT);
	static_assert(COUNT >= 1);
	static_assert(POS < N);
	static_assert(POS <= N - COUNT);

	std::array<T, COUNT> result;

	auto first = std::next(std::cbegin(arr), POS);
	auto last = std::next(first, COUNT);
	(void)std::copy(first, last, std::begin(result));

	return result;
}
