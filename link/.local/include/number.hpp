// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for an arithmetic type (excluding boolean and character types)
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/language/types
\sa https://en.cppreference.com/w/cpp/types/is_arithmetic
\sa https://en.cppreference.com/w/cpp/types/is_same
*/

#pragma once

#include "character.hpp"

#include <type_traits>

// Adapted from
// https://www.sandordargo.com/blog/2021/03/24/concepts-in-real-life
template <typename T>
concept number = std::is_arithmetic_v<std::remove_cv_t<T>> &&
                 !std::is_same_v<std::remove_cv_t<T>, bool> &&
                 !is_character_v<T>;
