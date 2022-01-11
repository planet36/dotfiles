// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept to check if a type is the same as any other given types
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/concepts/same_as
\sa https://en.cppreference.com/w/cpp/types/is_same
*/

#pragma once

#include <type_traits>

template <typename T, typename ... U>
struct is_type_any_of : std::bool_constant<(std::is_same_v<T, U> || ...)>{};

template <typename T, typename ... U>
inline constexpr bool is_type_any_of_v = is_type_any_of<T>::value;

template <typename T, typename ... U>
concept type_any_of = is_type_any_of_v<T, U...>;
