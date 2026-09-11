// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Concept for the bool type
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/language/type
*/

#pragma once

#include <type_traits>

template <typename T>
struct is_bool : std::bool_constant<std::is_same_v<bool, std::remove_cv_t<T>>>
{};

template <typename T>
inline constexpr bool is_bool_v = is_bool<T>::value;

template <typename T>
concept boolean = is_bool_v<T>;
