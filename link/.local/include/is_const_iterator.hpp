// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// is_const_iterator concept
/**
\file
\author Steven Ward
*/

#pragma once

#include <iterator>
#include <type_traits>

template <class Iter>
concept is_const_iterator = !std::is_swappable_v<typename std::iterator_traits<Iter>::reference>;
