// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Alias template for \c std::function that takes 2 args and returns \c bool
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <functional>

template <typename... Ts>
requires (sizeof...(Ts) == 2)
using binary_predicate_wrapper = std::function<bool(const Ts&...)>;
