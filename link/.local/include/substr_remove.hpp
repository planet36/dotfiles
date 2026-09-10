// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Remove all occurrences of a substring within a string
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <string>

/// remove all occurrences of \a sub from \a s
inline void
substr_remove(std::string& s, const std::string& sub)
{
    if (s.empty() || sub.empty())
        return;

    std::string::size_type loc = s.find(sub);
    if (loc == std::string::npos)
        return;

    std::string result;
    result.reserve(s.size() - sub.size());
    std::string::size_type pos = 0;

    while (loc != std::string::npos)
    {
        result.append(s, pos, loc - pos);
        pos = loc + sub.size();
        loc = s.find(sub, pos);
    }

    result.append(s, pos);
    s.swap(result);
}
