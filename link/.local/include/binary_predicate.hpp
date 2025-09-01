// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// binary predicate concept
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/concepts/predicate
*/

#pragma once

#include <concepts>

template <typename F, typename... Ts>
concept binary_predicate = std::predicate<F, Ts...> && (sizeof...(Ts) == 2);
