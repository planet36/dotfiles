// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Join a range of strings into a single string
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <concepts>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>

template <std::ranges::input_range R>
requires std::convertible_to<std::ranges::range_reference_t<R>, std::string_view>
[[nodiscard]] std::string
str_join(R&& range_strings, std::string_view joiner)
{
    std::string result;

    bool first = true;

    for (auto&& s : std::forward<R>(range_strings))
    {
        if (first)
        {
            first = false;
        }
        else
        {
            result += joiner;
        }

        if constexpr (std::is_pointer_v<std::remove_cvref_t<decltype(s)>>)
        {
            if (s != nullptr)
                result += s;
        }
        else
        {
            result += std::string_view{s};
        }
    }

    return result;
}
