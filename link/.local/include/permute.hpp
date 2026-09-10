// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Permute the elements of an array
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <array>
#if defined(DEBUG)
#include <cassert>
#endif
#include <concepts>
#include <cstddef>
#include <type_traits>

/// Verify that \a p is a permutation of the indices <code>[0, N)</code>
template <size_t N, std::unsigned_integral I>
bool
is_index_permutation(const std::array<I, N>& p)
{
    std::array<bool, N> seen{};

    for (size_t i = 0; i < N; ++i)
    {
        const size_t j = static_cast<size_t>(p[i]);

        if (j >= N || seen[j])
            return false;

        seen[j] = true;
    }

    return true;
}

/// y[i] ← x[p[i]]
/**
* The output index \c i comes from the input index \c p[i].
*
* \pre \a p must be a permutation of the indices <code>[0, N)</code>.
*/
template <typename T, size_t N, std::unsigned_integral I>
void
permute_from(std::array<T, N>& x, const std::array<I, N>& p)
{
#if defined(DEBUG)
    assert(is_index_permutation(p));
#endif

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
*
* \pre \a p must be a permutation of the indices <code>[0, N)</code>.
*/
template <typename T, size_t N, std::unsigned_integral I>
void
permute_to(std::array<T, N>& x, const std::array<I, N>& p)
{
#if defined(DEBUG)
    assert(is_index_permutation(p));
#endif

    std::remove_reference_t<decltype(x)> y;

    for (size_t i = 0; i < N; ++i)
    {
        y[p[i]] = x[i];
    }

    x = y;
}
