// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Alias template for a non-empty array
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <array>

/// Alias template of \c std::array that requires \c N>0
template <typename T, std::size_t N>
requires (N > 0)
using ne_arr = std::array<T, N>;
