// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Wrapper for \c std::iota that takes a \c std::ranges::forward_range
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/algorithm/iota
*/

#include <numeric>
#include <ranges>

inline void
iota(std::ranges::forward_range auto& container, std::ranges::range_value_t<decltype(container)> value = {})
{
	std::iota(std::ranges::begin(container), std::ranges::end(container), value);
}
