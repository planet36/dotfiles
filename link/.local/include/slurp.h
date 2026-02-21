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

#ifdef __cplusplus
extern "C" {
#endif

#if 1

// this version calls fopen, stat, fread, fclose
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
    if (stat(path, &statbuf) < 0)
    {
        (void)fclose(fp);
        warn("stat \"%s\"", path);
        return -1;
    }

    if (S_ISDIR(statbuf.st_mode))
    {
        (void)fclose(fp);
        errno = EISDIR;
        warn("%s \"%s\"", __func__, path);
        return -1;
    }

    if (!S_ISREG(statbuf.st_mode) && !S_ISLNK(statbuf.st_mode))
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

    const size_t expected_size_bytes = (size_t)statbuf.st_size;

    unsigned char* buf = (unsigned char*)malloc(expected_size_bytes);
    if (buf == nullptr)
    {
        (void)fclose(fp);
        warn("malloc %zu ", expected_size_bytes);
        return -1;
    }

    const size_t actual_size_bytes = fread_bytes(buf, expected_size_bytes, fp);
    if (actual_size_bytes != expected_size_bytes)
    {
        (void)fclose(fp);
        free(buf);
        buf = nullptr;
        warn("fread %zu, returned %zu", expected_size_bytes, actual_size_bytes);
        return -1;
    }

    *bytes = buf;
    *num_bytes = expected_size_bytes;

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

    if (!S_ISREG(statbuf.st_mode) && !S_ISLNK(statbuf.st_mode))
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

    const size_t expected_size_bytes = (size_t)statbuf.st_size;

    unsigned char* buf = (unsigned char*)malloc(expected_size_bytes);
    if (buf == nullptr)
    {
        (void)close(fd);
        warn("malloc %zu", expected_size_bytes);
        return -1;
    }

    // https://www.man7.org/linux/man-pages/man3/read.3p.html#RETURN_VALUE
    // read(3p) returns either an error code or the number of bytes read
    const ssize_t actual_size_bytes = read(fd, buf, expected_size_bytes);
    if (actual_size_bytes < 0 || (size_t)actual_size_bytes != expected_size_bytes)
    {
        (void)close(fd);
        free(buf);
        buf = nullptr;
        warn("read %zu, returned %zd", expected_size_bytes, actual_size_bytes);
        return -1;
    }

    *bytes = buf;
    *num_bytes = expected_size_bytes;

    (void)close(fd);
    return 0;
}

#endif

#ifdef __cplusplus
} // extern "C"
#endif
