// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Alias template for \c std::function that takes 1 arg and returns \c bool
/**
\file
\author Steven Ward
*/

#pragma once

#include <functional>

template <typename T>
using unary_predicate = std::function<bool(const T&)>;
