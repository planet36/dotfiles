// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Return evenly spaced numbers over a specified interval
/**
\file
\author Steven Ward
*/

#pragma once

#include "abs.hpp"
#include "div_mod.hpp"
#include "int_bytes.hpp"

#include <array>
#include <concepts>

/**
Return \a NUM evenly spaced samples, calculated over the interval <code>[\a start, \a stop]</code>.
The endpoint of the interval can optionally be excluded.
\sa https://numpy.org/doc/stable/reference/generated/numpy.linspace.html
*/
template <unsigned int NUM, std::integral T>
requires (NUM > 0)
constexpr
std::array<T, NUM>
linspace(const T start, const T stop, const bool endpoint = true)
{
	std::array<T, NUM> result;

	result.front() = start;

	if constexpr (NUM > 1)
	{
		const auto delta = to_signed(widen(stop)) - to_signed(widen(start));
		const auto div = to_signed(widen(NUM - endpoint));
		const auto offset = to_signed(widen(start)) * div;

		for (std::remove_cv_t<decltype(div)> i = 1; i < div; ++i)
		{
			/*
			* The rounding must happen last.
			*
			*   round(i * delta / div) + start
			* should be
			*   round(i * delta / div + start) ==
			*   round((i * delta + start * div) / div)
			*
			* This is noticeable when start is negative.
			*/
			//result[i] = round_div(i * delta, div) + start;
			result[i] = round_div(i * delta + offset, div);
		}

		if (endpoint)
			result.back() = stop;
	}

	return result;
}

/**
Return \a NUM evenly spaced samples, calculated over the interval <code>[\a start, \a stop]</code>.
The endpoint of the interval can optionally be excluded.
\sa https://numpy.org/doc/stable/reference/generated/numpy.linspace.html
*/
template <unsigned int NUM>
requires (NUM > 0)
constexpr
std::array<double, NUM>
linspace(const double start, const double stop, const bool endpoint = true)
{
	std::array<double, NUM> result;

	result.front() = start;

	if constexpr (NUM > 1)
	{
		const auto delta = stop - start;
		const size_t div = NUM - endpoint;

		for (size_t i = 1; i < div; ++i)
		{
			result[i] = i * delta / div + start;
		}

		if (endpoint)
			result.back() = stop;
	}

	return result;
}
