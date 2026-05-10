// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Acquire/release a read/write lock on a file descriptor
/**
* \file
* \author Steven Ward
* \sa https://www.gnu.org/software/libc/manual/html_node/File-Locks.html
* \sa https://www.gnu.org/software/libc/manual/html_node/Open-File-Description-Locks.html
* \sa https://www.gnu.org/software/libc/manual/html_node/Open-File-Description-Locks-Example.html
* \sa https://man7.org/linux/man-pages/man2/fcntl.2.html
*/

#pragma once

#include <fcntl.h>

#if defined(__cplusplus)
extern "C" {
#endif

/// Acquires a blocking OFD read (shared) lock on an entire file.
/**
* Applies an \c F_RDLCK over the whole file (offset 0, length 0) using
* \c F_OFD_SETLKW, blocking until the lock is available.
*
* The lock is an Open File Description (OFD) lock, associated with the
* open file description rather than the process. Unlike traditional POSIX
* advisory locks (\c F_SETLKW), OFD locks are:
*   - not released when another file descriptor referring to the same
*     open file description is closed;
*   - not shared among threads of the same process — each thread acquires
*     and releases independently.
*
* Multiple readers may hold the lock simultaneously; the call blocks only
* if a write lock is currently held by another open file description.
*
* \param fd  Open file descriptor to lock. Must be open for reading.
* \return    \c 0 on success, \c -1 on error (with \c errno set by
*            \c fcntl(2)).
*
* \note OFD locks (\c F_OFD_SETLKW) require Linux 3.15 or later.
* \sa acq_write_lock_fd(), rel_lock_fd()
*/
static inline int
acq_read_lock_fd(int fd)
{
#if defined(__cplusplus)
    using flock_t = flock;
#else
    typedef struct flock flock_t;
#endif

    flock_t lock = {
        .l_type = F_RDLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0,
        .l_pid = 0,
    };
    return fcntl(fd, F_OFD_SETLKW, &lock); // or F_OFD_SETLK
}

/// Acquires a blocking OFD write (exclusive) lock on an entire file.
/**
* Applies an \c F_WRLCK over the whole file (offset 0, length 0) using
* \c F_OFD_SETLKW, blocking until the lock is available.
*
* The lock is an Open File Description (OFD) lock, associated with the
* open file description rather than the process. Unlike traditional POSIX
* advisory locks (\c F_SETLKW), OFD locks are:
*   - not released when another file descriptor referring to the same
*     open file description is closed;
*   - not shared among threads of the same process — each thread acquires
*     and releases independently.
*
* The call blocks until all read and write locks held by other open file
* descriptions are released. Only one writer may hold the lock at a time.
*
* \param fd  Open file descriptor to lock. Must be open for writing.
* \return    \c 0 on success, \c -1 on error (with \c errno set by
*            \c fcntl(2)).
*
* \note OFD locks (\c F_OFD_SETLKW) require Linux 3.15 or later.
* \sa acq_read_lock_fd(), rel_lock_fd()
*/
static inline int
acq_write_lock_fd(int fd)
{
#if defined(__cplusplus)
    using flock_t = flock;
#else
    typedef struct flock flock_t;
#endif

    flock_t lock = {
        .l_type = F_WRLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0,
        .l_pid = 0,
    };
    return fcntl(fd, F_OFD_SETLKW, &lock); // or F_OFD_SETLK
}

/// Releases an OFD lock held on an entire file.
/**
* Applies \c F_UNLCK over the whole file (offset 0, length 0) using
* \c F_OFD_SETLKW, unconditionally releasing any read or write OFD lock
* held by the current open file description.
*
* \param fd  Open file descriptor whose lock should be released.
* \return    \c 0 on success, \c -1 on error (with \c errno set by
*            \c fcntl(2)).
*
* \note OFD locks (\c F_OFD_SETLKW) require Linux 3.15 or later.
* \sa acq_read_lock_fd(), acq_write_lock_fd()
*/
static inline int
rel_lock_fd(int fd)
{
#if defined(__cplusplus)
    using flock_t = flock;
#else
    typedef struct flock flock_t;
#endif

    flock_t lock = {
        .l_type = F_UNLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0,
        .l_pid = 0,
    };
    return fcntl(fd, F_OFD_SETLKW, &lock); // or F_OFD_SETLK
}

#if defined(__cplusplus)
} // extern "C"
#endif
