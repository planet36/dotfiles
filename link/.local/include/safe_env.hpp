// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Thread-safe access to environment variables
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <mutex>
#include <optional>
#include <string>
#include <system_error>

namespace safe_env
{
namespace { std::mutex mtx; }

/// similar to \c clearenv
/**
* \sa https://man7.org/linux/man-pages/man3/clearenv.3.html
*/
void
clear()
{
    std::lock_guard lock{mtx};
    assert(clearenv() == 0);
}

/// similar to \c getenv
/**
* \sa https://man7.org/linux/man-pages/man3/getenv.3.html
*/
std::optional<std::string>
get(const std::string& name)
{
    std::lock_guard lock{mtx};
    const char* value = getenv(name.c_str());
    return value == nullptr ? std::nullopt : std::optional<std::string>(value);
}

/// similar to \c setenv
/**
* \sa https://man7.org/linux/man-pages/man3/setenv.3.html
*/
void
set(const std::string& name, const std::string& value, const bool overwrite = true)
{
    std::lock_guard lock{mtx};
    if (setenv(name.c_str(), value.c_str(), overwrite) < 0)
        throw std::system_error(std::make_error_code(std::errc{errno}), "setenv");
}

/// similar to \c unsetenv
/**
* \sa https://man7.org/linux/man-pages/man3/unsetenv.3.html
*/
void
unset(const std::string& name)
{
    std::lock_guard lock{mtx};
    if (unsetenv(name.c_str()) < 0)
        throw std::system_error(std::make_error_code(std::errc{errno}), "unsetenv");
}

}
