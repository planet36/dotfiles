// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Cycle through an interval of integers
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <algorithm>

/// forward cycle in the interval <code>[0, MAX]</code>
/**
* The initial value is \c 0.
*/
template <unsigned int MAX>
class cycle
{
    using value_type = decltype(MAX);
    static constexpr value_type MIN{0};
    static_assert(MIN <= MAX);
    value_type val{MIN};

public:
    cycle() = default;

    explicit constexpr cycle(const value_type n) : val(std::clamp(n, MIN, MAX)) {}

    constexpr auto operator()() { return next(); }

    constexpr auto next()
    {
        const auto result{val};
        if (val == MAX)
            val = MIN;
        else
            ++val;
        return result;
    }
};

/// forward cycle in the interval <code>[MIN, MAX]</code>
/**
* The initial value is \c MIN.
*/
template <unsigned int MIN, unsigned int MAX>
class cycle2
{
    using value_type = decltype(MAX);
    static_assert(MIN <= MAX);
    value_type val{MIN};

public:
    cycle2() = default;

    explicit constexpr cycle2(const value_type n) : val(std::clamp(n, MIN, MAX)) {}

    constexpr auto operator()() { return next(); }

    constexpr auto next()
    {
        const auto result{val};
        if (val == MAX)
            val = MIN;
        else
            ++val;
        return result;
    }
};

/// reverse cycle in the interval <code>[0, MAX]</code>
/**
* The initial value is \c MAX.
*/
template <unsigned int MAX>
class rcycle
{
    using value_type = decltype(MAX);
    static constexpr value_type MIN{0};
    static_assert(MIN <= MAX);
    value_type val{MAX};

public:
    rcycle() = default;

    explicit constexpr rcycle(const value_type n) : val(std::clamp(n, MIN, MAX)) {}

    constexpr auto operator()() { return next(); }

    constexpr auto next()
    {
        const auto result{val};
        if (val == MIN)
            val = MAX;
        else
            --val;
        return result;
    }
};

/// reverse cycle in the interval <code>[MIN, MAX]</code>
/**
* The initial value is \c MAX.
*/
template <unsigned int MIN, unsigned int MAX>
class rcycle2
{
    using value_type = decltype(MAX);
    static_assert(MIN <= MAX);
    value_type val{MAX};

public:
    rcycle2() = default;

    explicit constexpr rcycle2(const value_type n) : val(std::clamp(n, MIN, MAX)) {}

    constexpr auto operator()() { return next(); }

    constexpr auto next()
    {
        const auto result{val};
        if (val == MIN)
            val = MAX;
        else
            --val;
        return result;
    }
};
