// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Cast integer to floating-point of sufficient precision
/**
\file
\author Steven Ward
*/

#pragma once

#include <concepts>
#include <limits>

template <std::integral T>
requires (std::numeric_limits<T>::digits <= std::numeric_limits<float>::digits)
constexpr auto
i_to_f(const T x) {return static_cast<float>(x);}

template <std::integral T>
requires (std::numeric_limits<T>::digits >  std::numeric_limits<float>::digits) &&
         (std::numeric_limits<T>::digits <= std::numeric_limits<double>::digits)
constexpr auto
i_to_f(const T x) {return static_cast<double>(x);}

// XXX: Every uint64_t (digits=64) cannot be cast exactly to long double (digits=64)
template <std::integral T>
requires (std::numeric_limits<T>::digits >  std::numeric_limits<double>::digits) &&
         (std::numeric_limits<T>::digits <= std::numeric_limits<long double>::digits)
constexpr auto
i_to_f(const T x) {return static_cast<long double>(x);}
