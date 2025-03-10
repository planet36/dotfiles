// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Acquire/release a read/write lock on a file descriptor
/**
\file
\author Steven Ward
\sa https://www.gnu.org/software/libc/manual/html_node/File-Locks.html
\sa https://www.gnu.org/software/libc/manual/html_node/Open-File-Description-Locks.html
\sa https://www.gnu.org/software/libc/manual/html_node/Open-File-Description-Locks-Example.html
\sa https://man7.org/linux/man-pages/man2/fcntl.2.html
*/

#pragma once

#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline int
acq_read_lock_fd(int fd)
{
#ifdef __cplusplus
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

static inline int
acq_write_lock_fd(int fd)
{
#ifdef __cplusplus
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

static inline int
rel_lock_fd(int fd)
{
#ifdef __cplusplus
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

#ifdef __cplusplus
} // extern "C"
#endif
