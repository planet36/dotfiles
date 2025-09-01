// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Small functions for file descriptors, etc.
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
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

static bool
fadvise_sequential_noreuse(const int fd)
{
    int posix_fadvise_result = 0;

    // Expect sequential page references.
    posix_fadvise_result = posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL);
    if (posix_fadvise_result != 0)
    {
        errno = posix_fadvise_result;
        return true;
    }

    // Data will be accessed once.
    posix_fadvise_result = posix_fadvise(fd, 0, 0, POSIX_FADV_NOREUSE);
    if (posix_fadvise_result != 0)
    {
        errno = posix_fadvise_result;
        return true;
    }

    return false;
}

static bool
madvise_sequential_willneed(void* mmap_addr, const size_t mmap_size)
{
    if (posix_madvise(mmap_addr, mmap_size, POSIX_MADV_SEQUENTIAL) < 0)
        return true;

    if (posix_madvise(mmap_addr, mmap_size, POSIX_MADV_WILLNEED) < 0)
        return true;

    return false;
}

#ifdef __cplusplus
} // extern "C"
#endif
