// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Slurp a file into memory
/**
* \file
* \author Steven Ward
* \sa https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/
*/

#pragma once

#include "iobytes.h"

// https://man7.org/linux/man-pages/man3/err.3.html
#include <err.h>

// https://www.man7.org/linux/man-pages/man3/error.3.html
//#include <error.h> // glibc

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if 1

// this version calls fopen, fstat, fread, fclose
int
slurp(const char* path, unsigned char** bytes, size_t* num_bytes)
{
    FILE* fp = fopen(path, "rb");
    if (fp == nullptr)
    {
        warn("fopen \"%s\"", path);
        return -1;
    }

    struct stat statbuf = {0};
    if (fstat(fileno(fp), &statbuf) < 0)
    {
        (void)fclose(fp);
        warn("fstat \"%s\"", path);
        return -1;
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        (void)fclose(fp);
        errno = EISDIR;
        warn("%s \"%s\"", __func__, path);
        return -1;
    }

    if (!S_ISREG(statbuf.st_mode))
    {
        (void)fclose(fp);
        errno = EOPNOTSUPP;
        warn("%s \"%s\"", __func__, path);
        return -1;
    }

    if (statbuf.st_size < 0)
    {
        (void)fclose(fp);
        errno = ERANGE;
        warn("%s \"%s\"", __func__, path);
        return -1;
    }

    size_t buf_size = (size_t)statbuf.st_size + 1;

    unsigned char* buf = (unsigned char*)malloc(buf_size);
    if (buf == nullptr)
    {
        (void)fclose(fp);
        warn("malloc %zu", buf_size);
        return -1;
    }

    size_t num_bytes_read = 0;

    while (true)
    {
        num_bytes_read += fread_bytes(buf + num_bytes_read, buf_size - num_bytes_read, fp);
        if (feof(fp) != 0 || ferror(fp) != 0)
            break;

        unsigned char* const new_buf = (unsigned char*)realloc(buf, buf_size * 2);
        if (new_buf == nullptr)
        {
            (void)fclose(fp);
            free(buf);
            warn("realloc %zu", buf_size * 2);
            return -1;
        }

        buf = new_buf;
        buf_size *= 2;
    }

    if (ferror(fp) != 0)
    {
        (void)fclose(fp);
        free(buf);
        warn("fread \"%s\"", path);
        return -1;
    }

    *bytes = buf;
    *num_bytes = num_bytes_read;

    (void)fclose(fp);
    return 0;
}

#else

// this version calls open, fstat, read, close
int
slurp(const char* path, unsigned char** bytes, size_t* num_bytes)
{
    const int fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        warn("open \"%s\"", path);
        return -1;
    }

    struct stat statbuf = {0};
    if (fstat(fd, &statbuf) < 0)
    {
        (void)close(fd);
        warn("fstat \"%s\"", path);
        return -1;
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        (void)close(fd);
        errno = EISDIR;
        warn("%s \"%s\"", __func__, path);
        return -1;
    }

    if (!S_ISREG(statbuf.st_mode))
    {
        (void)close(fd);
        errno = EOPNOTSUPP;
        warn("%s \"%s\"", __func__, path);
        return -1;
    }

    if (statbuf.st_size < 0)
    {
        (void)close(fd);
        errno = ERANGE;
        warn("%s \"%s\"", __func__, path);
        return -1;
    }

    size_t buf_size = (size_t)statbuf.st_size + 1;

    unsigned char* buf = (unsigned char*)malloc(buf_size);
    if (buf == nullptr)
    {
        (void)close(fd);
        warn("malloc %zu", buf_size);
        return -1;
    }

    size_t num_bytes_read = 0;

    while (true)
    {
        if (num_bytes_read == buf_size)
        {
            unsigned char* const new_buf = (unsigned char*)realloc(buf, buf_size * 2);
            if (new_buf == nullptr)
            {
                (void)close(fd);
                free(buf);
                warn("realloc %zu", buf_size * 2);
                return -1;
            }

            buf = new_buf;
            buf_size *= 2;
        }

        // https://www.man7.org/linux/man-pages/man3/read.3p.html#RETURN_VALUE
        // read(3p) returns the number of bytes read, 0 at end of file, or -1 on error
        const ssize_t n = read(fd, buf + num_bytes_read, buf_size - num_bytes_read);
        if (n < 0)
        {
            if (errno == EINTR)
                continue;

            (void)close(fd);
            free(buf);
            warn("read \"%s\"", path);
            return -1;
        }

        if (n == 0)
            break;

        num_bytes_read += (size_t)n;
    }

    *bytes = buf;
    *num_bytes = num_bytes_read;

    (void)close(fd);
    return 0;
}

#endif

#if defined(__cplusplus)
} // extern "C"
#endif
