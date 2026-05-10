// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// POSIX fd and mmap utilities: size queries, page alignment, and access-pattern hints.
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

#if defined(__cplusplus)
extern "C" {
#endif

/// Determines whether a file descriptor refers to a seekable file.
/**
* Probes seekability by performing a no-op \c lseek to the current position.
* This succeeds on regular files and block devices, and fails on pipes,
* sockets, and other non-seekable descriptors.
*
* \param fd  Open file descriptor to test.
* \return    \c true if \p fd is seekable, \c false otherwise.
*/
static inline bool
is_seekable(const int fd)
{
    return lseek(fd, 0, SEEK_CUR) != -1;
}

/// Returns the size of the file referred to by a file descriptor.
/**
* Retrieves file metadata via \c fstat(2) and extracts \c st_size.
*
* \param fd  Open file descriptor.
* \return    File size in bytes on success, or \c -1 if \c fstat(2) fails
*            (with \c errno set by \c fstat).
*/
static inline long
get_file_size(const int fd)
{
    struct stat statbuf;

    if (fstat(fd, &statbuf) < 0)
        return -1;

    return statbuf.st_size;
}

/// Computes a page-aligned mapping size for a given file size.
/**
* Rounds \p file_size up to the nearest multiple of the system page size,
* as returned by \c sysconf(_SC_PAGESIZE). If \p file_size is zero, returns
* exactly one page so that the mapping is never empty.
*
* \note Assumes \c sysconf(_SC_PAGESIZE) succeeds and returns a positive
*       power-of-two value.
*
* \param file_size  Logical size of the file in bytes.
* \return           Smallest page-aligned size >= \p file_size, or one full
*                   page if \p file_size is zero.
*/
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

/// Advises the kernel that a file will be read sequentially and only once.
/**
* Issues two successive \c posix_fadvise(2) hints over the entire file:
*   - \c POSIX_FADV_SEQUENTIAL — expect sequential page references, prompting
*     aggressive read-ahead.
*   - \c POSIX_FADV_NOREUSE — pages are unlikely to be needed again, allowing
*     the kernel to reclaim them sooner.
*
* On failure of either call, \c errno is set to the returned error code and
* the function returns immediately without issuing the remaining hint.
*
* \param fd  Open file descriptor to advise on.
* \return    \c true if either \c posix_fadvise call failed (with \c errno set
*            to the error), \c false if both hints were accepted.
*/
static inline bool
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

/// Advises the kernel that a memory-mapped region will be accessed
/// sequentially and in the near future.
/**
* Issues two successive \c posix_madvise(3) hints over the mapping:
*   - \c POSIX_MADV_SEQUENTIAL — expect sequential access, prompting
*     aggressive read-ahead and allowing pages before the current position
*     to be released.
*   - \c POSIX_MADV_WILLNEED — the region will be needed soon; the kernel
*     may begin faulting pages in proactively.
*
* On failure of either call, \c errno is set to the returned error code and
* the function returns immediately without issuing the remaining hint.
*
* \param mmap_addr  Base address of the memory-mapped region.
* \param mmap_size  Length of the region in bytes.
* \return           \c true if either \c posix_madvise call failed (with
*                   \c errno set to the error), \c false if both hints were
*                   accepted.
*/
static inline bool
madvise_sequential_willneed(void* mmap_addr, const size_t mmap_size)
{
    int posix_madvise_result = 0;

    posix_madvise_result = posix_madvise(mmap_addr, mmap_size, POSIX_MADV_SEQUENTIAL);
    if (posix_madvise_result != 0)
    {
        errno = posix_madvise_result;
        return true;
    }

    posix_madvise_result = posix_madvise(mmap_addr, mmap_size, POSIX_MADV_WILLNEED);
    if (posix_madvise_result != 0)
    {
        errno = posix_madvise_result;
        return true;
    }

    return false;
}

#if defined(__cplusplus)
} // extern "C"
#endif
