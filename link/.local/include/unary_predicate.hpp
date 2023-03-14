// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// unary predicate concept
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/concepts/predicate
*/

#pragma once

#include <concepts>
#include <type_traits>

template <typename F, typename... Ts>
concept unary_predicate =
std::regular_invocable<F, Ts...> &&
std::convertible_to<std::invoke_result_t<F, Ts...>, bool> &&
sizeof...(Ts) == 1;
