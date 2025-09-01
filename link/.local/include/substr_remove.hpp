// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Remove all occurrences of a substring within a string
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <string>

/// remove all occurrences of \a sub from \a s
void
substr_remove(std::string& s, const std::string& sub)
{
    if (s.empty() || sub.empty())
        return;

    std::string::size_type loc = 0;
    while ((loc = s.find(sub, loc)) != std::string::npos)
    {
        s.erase(loc, sub.size());
    }
}
