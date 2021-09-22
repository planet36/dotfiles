// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for an arithmetic type (excluding boolean and character types)
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/language/types
\sa https://en.cppreference.com/w/cpp/types/is_arithmetic
\sa https://en.cppreference.com/w/cpp/concepts/same_as
*/

#pragma once

#include <concepts>

// adapted from
// https://www.sandordargo.com/blog/2021/03/24/concepts-in-real-life
template <typename T>
concept number = std::is_arithmetic_v<T>
	&& !std::same_as<T, bool>
	&& !std::same_as<T, char>
	&& !std::same_as<T, signed char>
	&& !std::same_as<T, unsigned char>
	&& !std::same_as<T, char8_t>
	&& !std::same_as<T, char16_t>
	&& !std::same_as<T, char32_t>
	&& !std::same_as<T, wchar_t>
;
