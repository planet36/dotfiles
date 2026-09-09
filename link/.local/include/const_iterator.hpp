// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Concept for a const iterator type
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/iterator/const_iterator
*/

#pragma once

#include <concepts>
#include <iterator>

template <typename Iter>
concept const_iterator =
    std::input_iterator<Iter> && std::same_as<std::const_iterator<Iter>, Iter>;
