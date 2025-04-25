// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for a signed integral number type
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/language/type
*/

#pragma once

#include "type_any_of.hpp"

#include <type_traits>

// Character types and bool are excluded
template <typename T>
struct is_signed_integral_number : is_type_any_of<std::remove_cv_t<T>,
    short, int, long, long long>
{};

template <typename T>
inline constexpr bool is_signed_integral_number_v =
    is_signed_integral_number<T>::value;

template <typename T>
concept signed_integral_number = is_signed_integral_number_v<T>;
