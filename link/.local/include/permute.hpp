// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Permute the elements of an array
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <type_traits>

/// y[i] ← x[p[i]]
/**
* The output index \c i comes from the input index \c p[i].
*/
template <typename T, size_t N, std::unsigned_integral I>
void
permute_from(std::array<T, N>& x, const std::array<I, N>& p)
{
    std::remove_reference_t<decltype(x)> y;

    for (size_t i = 0; i < N; ++i)
    {
        y[i] = x[p[i]];
    }

    x = y;
}

/// y[p[i]] ← x[i]
/**
* The input index \c i goes to the output index \c p[i].
*/
template <typename T, size_t N, std::unsigned_integral I>
void
permute_to(std::array<T, N>& x, const std::array<I, N>& p)
{
    std::remove_reference_t<decltype(x)> y;

    for (size_t i = 0; i < N; ++i)
    {
        y[p[i]] = x[i];
    }

    x = y;
}
