// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Slurp a file into memory
/**
* \file
* \author Steven Ward
* \sa https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/
*/

#pragma once

// Description of values for errno
// https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html

#include "iobytes.h"

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <fcntl.h>
#include <filesystem>
#include <sys/stat.h>
#include <system_error>
#include <unistd.h>
#include <vector>

#if 1

// this version calls fopen, fstat, fread, fclose
inline std::vector<uint8_t>
slurp(const std::filesystem::path& path)
{
    std::FILE* fp = std::fopen(path.c_str(), "r");
    if (fp == nullptr)
    {
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    struct stat statbuf{};
    if (::fstat(::fileno(fp), &statbuf) < 0)
    {
        (void)std::fclose(fp);
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        (void)std::fclose(fp);
        errno = EISDIR;
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    if (!S_ISREG(statbuf.st_mode))
    {
        (void)std::fclose(fp);
        errno = EOPNOTSUPP;
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    if (statbuf.st_size < 0)
    {
        (void)std::fclose(fp);
        errno = ERANGE;
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    std::vector<uint8_t> result;
    size_t num_bytes_read = 0;

    try
    {
        result.resize(static_cast<size_t>(statbuf.st_size) + 1);

        while (true)
        {
            num_bytes_read += fread_bytes(result.data() + num_bytes_read,
                                          result.size() - num_bytes_read, fp);
            if (std::feof(fp) != 0 || std::ferror(fp) != 0)
                break;

            result.resize(result.size() * 2);
        }
    }
    catch (...)
    {
        (void)std::fclose(fp);
        throw;
    }

    if (std::ferror(fp) != 0)
    {
        (void)std::fclose(fp);
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    (void)std::fclose(fp);
    result.resize(num_bytes_read);
    return result;
}

#else

// this version calls open, fstat, read, close
inline std::vector<uint8_t>
slurp(const std::filesystem::path& path)
{
    const int fd = ::open(path.c_str(), O_RDONLY);
    if (fd < 0)
    {
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    struct stat statbuf{};
    if (::fstat(fd, &statbuf) < 0)
    {
        (void)::close(fd);
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        (void)::close(fd);
        errno = EISDIR;
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    if (!S_ISREG(statbuf.st_mode))
    {
        (void)::close(fd);
        errno = EOPNOTSUPP;
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    if (statbuf.st_size < 0)
    {
        (void)::close(fd);
        errno = ERANGE;
        throw std::system_error(std::make_error_code(std::errc{errno}), path);
    }

    std::vector<uint8_t> result;
    size_t num_bytes_read = 0;
    int read_errno = 0;

    try
    {
        result.resize(static_cast<size_t>(statbuf.st_size) + 1);

        while (true)
        {
            if (num_bytes_read == result.size())
                result.resize(result.size() * 2);

            // https://www.man7.org/linux/man-pages/man3/read.3p.html#RETURN_VALUE
            // read(3p) returns the number of bytes read, 0 at end of file, or -1 on error
            const ssize_t n = ::read(fd, result.data() + num_bytes_read,
                                     result.size() - num_bytes_read);
            if (n < 0)
            {
                if (errno == EINTR)
                    continue;

                read_errno = errno;
                break;
            }

            if (n == 0)
                break;

            num_bytes_read += static_cast<size_t>(n);
        }
    }
    catch (...)
    {
        (void)::close(fd);
        throw;
    }

    (void)::close(fd);

    if (read_errno != 0)
        throw std::system_error(std::make_error_code(std::errc{read_errno}), path);

    result.resize(num_bytes_read);
    return result;
}

#endif
