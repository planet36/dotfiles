// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// float-to-string wrapper function for std::to_chars
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/utility/to_chars
*/

#pragma once

#include <charconv>
#include <concepts>
#include <string>

void
resize_to_nul(std::string& s)
{
    const std::string::size_type i = s.find('\0');
    if (i != std::string::npos)
        s.resize(i);
}

std::string
f_to_s(const std::floating_point auto x,
       const std::chars_format chars_format,
       const int precision)
{
    std::string s;
    std::to_chars_result r{};

    do
    {
        s.resize(s.size() + 64);
        r = std::to_chars(s.data(), s.data() + s.size(), x, chars_format,
                          precision);
    }
    while (r.ec == std::errc::value_too_large);

    resize_to_nul(s);
    return s;
}

std::string
f_to_s_scientific(const std::floating_point auto x, const int precision)
{
    constexpr auto chars_format{std::chars_format::scientific};
    return f_to_s(x, chars_format, precision);
}

std::string
f_to_s_fixed(const std::floating_point auto x, const int precision)
{
    constexpr auto chars_format{std::chars_format::fixed};
    return f_to_s(x, chars_format, precision);
}

std::string
f_to_s_hex(const std::floating_point auto x, const int precision)
{
    constexpr auto chars_format{std::chars_format::hex};
    return f_to_s(x, chars_format, precision);
}

std::string
f_to_s_general(const std::floating_point auto x, const int precision)
{
    constexpr auto chars_format{std::chars_format::general};
    return f_to_s(x, chars_format, precision);
}
