// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Small functions for file descriptors, etc.
/**
\file
\author Steven Ward
*/

#pragma once

#include <sys/stat.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline bool
is_seekable(const int fd)
{
    return lseek(fd, 0, SEEK_CUR) != -1;
}

static inline long
get_file_size(const int fd)
{
    struct stat statbuf;

    if (fstat(fd, &statbuf) < 0)
        return -1;

    return statbuf.st_size;
}

static inline size_t
get_mmap_size(const size_t file_size)
{
    // Presume that sysconf(_SC_PAGESIZE) will not fail.
    const size_t page_size = (size_t)sysconf(_SC_PAGESIZE);

    if (file_size == 0)
        return page_size;

    if ((file_size % page_size) == 0)
        return file_size;

    // align on page boundary
    return file_size + (page_size - (file_size % page_size));
}

#ifdef __cplusplus
} // extern "C"
#endif
