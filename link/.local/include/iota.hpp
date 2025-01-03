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

template <std::ranges::forward_range R>
inline void
iota(R& container, std::ranges::range_value_t<R> value = {})
{
	static_assert(std::ranges::output_range<R,
	                                        std::ranges::range_value_t<R>>,
	              "The range must be writable");
	std::iota(std::ranges::begin(container), std::ranges::end(container), value);
}
