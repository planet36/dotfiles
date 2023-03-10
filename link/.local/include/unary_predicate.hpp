// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Alias template for \c std::function that takes 1 arg and returns \c bool
/**
\file
\author Steven Ward
*/

#pragma once

#include <functional>

template <typename... Ts>
requires (sizeof...(Ts) == 1)
using unary_predicate = std::function<bool(const Ts&...)>;
