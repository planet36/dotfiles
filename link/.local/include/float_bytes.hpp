// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// compile-time typing of floats based on a given byte size or bit size
/**
\file
\author Steven Ward
\sa https://peter.bloomfield.online/using-cpp-templates-for-size-based-type-selection/
*/

#pragma once

#include <limits>
#include <type_traits>

template <unsigned int N>
using float_bytes = std::conditional_t<N <= sizeof(float), float,
                    std::conditional_t<N <= sizeof(double), double,
                    std::conditional_t<N <= sizeof(long double), long double,
                    void
>>>;

/**
* \sa https://en.cppreference.com/w/cpp/types/numeric_limits/digits
*/
template <unsigned int N>
using float_bits = std::conditional_t<N <= std::numeric_limits<float>::digits, float,
                   std::conditional_t<N <= std::numeric_limits<double>::digits, double,
                   std::conditional_t<N <= std::numeric_limits<long double>::digits, long double,
                   void
>>>;
