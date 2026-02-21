// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Cast floating-point to integer of sufficient size
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>
#include <limits>

constexpr auto
f_to_i(const std::floating_point auto x)
{
    using result_type = int_bits<std::numeric_limits<decltype(x)>::digits>;
    return static_cast<result_type>(x);
}

constexpr auto
f_to_u(const std::floating_point auto x)
{
    using result_type = uint_bits<std::numeric_limits<decltype(x)>::digits>;
    return static_cast<result_type>(x);
}
