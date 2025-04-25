// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Type trait and concept for a const iterator type
/**
\file
\author Steven Ward
*/

#pragma once

#include <iterator>
#include <type_traits>

template <typename Iter>
struct is_const_iterator : std::bool_constant<!std::is_swappable_v<
    typename std::iterator_traits<Iter>::reference>>
{};

template <typename Iter>
inline constexpr bool is_const_iterator_v = is_const_iterator<Iter>::value;

template <typename Iter>
concept const_iterator = is_const_iterator_v<Iter>;
