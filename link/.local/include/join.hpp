// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// join strings
/**
\file
\author Steven Ward

Note: Only std::string is supported.
*/

#pragma once

#include "type_any_of.hpp"

#include <concepts>
#include <iterator>
#include <string>
#include <string_view>

template <std::input_iterator Iter>
requires type_any_of<std::remove_cv_t<typename std::iterator_traits<Iter>::value_type>,
	std::string,
	std::string_view>
auto
join(const Iter& first, const Iter& last, const std::string& joiner = ", ")
{
	std::string result;

	for (Iter i = first; i != last; i = std::next(i))
	{
		if (i->empty())
			continue;

		if (!result.empty())
			result += joiner;

		result += *i;
	}

	return result;
}

template <std::input_iterator Iter>
requires std::same_as<
	typename std::iterator_traits<Iter>::value_type,
	const char*>
auto
join(const Iter& first, const Iter& last, const std::string& joiner = ", ")
{
	std::string result;

	for (Iter i = first; i != last; i = std::next(i))
	{
		if (*i == nullptr || (*i)[0] == '\0')
			continue;

		if (!result.empty())
			result += joiner;

		result += *i;
	}

	return result;
}

// template template parameter
template <template <typename> typename Container, typename StringT>
requires type_any_of<StringT,
	std::string,
	std::string_view,
	const char*>
auto
join(const Container<StringT>& c, const std::string& joiner = ", ")
{
	return join(c.cbegin(), c.cend(), joiner);
}
