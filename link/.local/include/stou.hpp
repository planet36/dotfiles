// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// string to unsigned int
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/string/basic_string/stoul
* \sa https://en.cppreference.com/w/cpp/string/basic_string/stol
*/

#pragma once

#include <stdexcept>
#include <string>
#include <utility>

/// Convert \a s to <code>unsigned int</code>, similar to \c std::stoul
/**
* \exception std::invalid_argument no conversion could be performed
* \exception std::out_of_range the value is negative or greater than the maximum of
* <code>unsigned int</code>
*/
inline unsigned int
stou(const std::string& s, std::size_t* pos = nullptr, int base = 10)
{
    const long i = std::stol(s, pos, base);
    if (!std::in_range<unsigned int>(i))
        throw std::out_of_range("stou");
    return static_cast<unsigned int>(i);
}
