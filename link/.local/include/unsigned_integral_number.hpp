// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for an unsigned integral number type
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
struct is_unsigned_integral_number : is_type_any_of<std::remove_cv_t<T>,
                                                    unsigned short,
                                                    unsigned int,
                                                    unsigned long,
                                                    unsigned long long>
{};

template <typename T>
inline constexpr bool is_unsigned_integral_number_v = is_unsigned_integral_number<T>::value;

template <typename T>
concept unsigned_integral_number = is_unsigned_integral_number_v<T>;
