// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Concept to check if a type is the same as any other given types
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/concepts/same_as
* \sa https://en.cppreference.com/w/cpp/types/is_same
*/

#pragma once

#include <type_traits>

template <typename T, typename... Us>
struct is_type_any_of : std::bool_constant<(std::is_same_v<T, Us> || ...)>
{};

template <typename T, typename... Us>
inline constexpr bool is_type_any_of_v = is_type_any_of<T, Us...>::value;

template <typename T, typename... Us>
concept type_any_of = is_type_any_of_v<T, Us...>;
