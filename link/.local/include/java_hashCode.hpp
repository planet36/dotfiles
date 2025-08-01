// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// constexpr Java string.hashCode() function for string_view
/**
\file
\author Steven Ward
\sa https://bugs.java.com/bugdatabase/view_bug.do?bug_id=4045622
\sa https://docs.oracle.com/en/java/javase/24/docs/api/java.base/java/lang/String.html#hashCode()
*/

#pragma once

#include <cstdint>
#include <string>

/// Java string.hashCode() hash
/** NOTE: this operates on bytes, not characters */
constexpr int32_t
java_hashCode(const std::string_view s)
{
    int32_t result = 0;

    for (const auto c : s)
    {
        const auto octet = static_cast<uint8_t>(c);
        result = 31 * result + octet;
    }

    return result;
}
