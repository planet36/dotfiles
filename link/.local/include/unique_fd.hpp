// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// RAII wrapper for a POSIX file descriptor
/**
* \file
* \author Steven Ward
* \sa https://cs.android.com/android/platform/superproject/+/android-latest-release:frameworks/native/libs/binder/include/binder/unique_fd.h?q=unique_fd.h
* \sa https://cs.android.com/android/platform/superproject/+/main:system/libbase/include/android-base/unique_fd.h
* \sa https://android.googlesource.com/platform/system/core/+/c0e6e40/base/include/android-base/unique_fd.h
* \sa https://stackoverflow.com/a/15762682
* \sa http://linuxvox.com/blog/why-are-unix-file-descriptors-not-implemented-by-their-own-type-especially-in-c/
*/

#pragma once

#include <unistd.h>
#include <utility>

/// RAII wrapper for a POSIX file descriptor
class unique_fd final
{
public:

    static constexpr int invalid_fd = -1;

    constexpr unique_fd() noexcept = default;

    constexpr explicit unique_fd(int fd) noexcept : fd_{fd} {}

    // Disallow copying
    unique_fd(const unique_fd&) = delete;
    unique_fd& operator=(const unique_fd&) = delete;

    // Allow moving
    constexpr unique_fd(unique_fd&& that) noexcept : fd_{that.release()} {}

    unique_fd& operator=(unique_fd&& that) noexcept
    {
        if (this != &that)
        {
            close_if_valid();
            fd_ = that.release();
        }

        return *this;
    }

    ~unique_fd() noexcept { close_if_valid(); }

    [[nodiscard]] constexpr int get() const noexcept { return fd_; }

    [[nodiscard]] constexpr bool ok() const noexcept { return fd_ >= 0; }

    [[nodiscard]] constexpr int release() noexcept { return std::exchange(fd_, invalid_fd); }

private:

    int fd_{invalid_fd};

    // Ignore return value of `close`
    // https://lkml.indiana.edu/hypermail/linux/kernel/0509.1/0877.html
    // Intentionally not const.
    void close_if_valid() noexcept // NOLINT(readability-make-member-function-const)
    { if (ok()) { (void)::close(fd_); } }
};
