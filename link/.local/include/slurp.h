// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Slurp a file into memory
/**
\file
\author Steven Ward
\sa https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/
*/

#pragma once

// https://man.openbsd.org/err.3
#include <err.h> // libbsd

// https://www.man7.org/linux/man-pages/man3/error.3.html
//#include <error.h> // glibc

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#if 1

// this version calls fopen, stat, fread, fclose
int
slurp(const char* path, unsigned char** bytes, size_t* num_bytes)
{
	FILE* fp = fopen(path, "rb");
	if (fp == NULL)
	{
		warn("fopen \"%s\"", path);
		return -1;
	}

	struct stat statbuf;
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

	const size_t get_bytes = (size_t)statbuf.st_size;

	unsigned char* buf = (unsigned char*)malloc(get_bytes);
	if (buf == NULL)
	{
		(void)fclose(fp);
		warn("malloc %zu ", get_bytes);
		return -1;
	}

	// https://man7.org/linux/man-pages/man3/fread.3p.html#RETURN_VALUE
	// fread(3p) returns the number of items read
	// In our case, each item is 1 byte
	const size_t got_bytes = fread(buf, 1, get_bytes, fp);
	if (got_bytes != get_bytes)
	{
		(void)fclose(fp);
		free(buf);
		buf = NULL;
		warn("fread %zu, returned %zu", get_bytes, got_bytes);
		return -1;
	}

	*bytes = buf;
	*num_bytes = get_bytes;

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

	struct stat statbuf;
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

	const size_t get_bytes = (size_t)statbuf.st_size;

	unsigned char* buf = (unsigned char*)malloc(get_bytes);
	if (buf == NULL)
	{
		(void)close(fd);
		warn("malloc %zu", get_bytes);
		return -1;
	}

	// https://www.man7.org/linux/man-pages/man3/read.3p.html#RETURN_VALUE
	// read(3p) returns either an error code or the number of bytes read
	const ssize_t got_bytes = read(fd, buf, get_bytes);
	if (got_bytes < 0 || (size_t)got_bytes != get_bytes)
	{
		(void)close(fd);
		free(buf);
		buf = NULL;
		warn("read %zu, returned %zd", get_bytes, got_bytes);
		return -1;
	}

	*bytes = buf;
	*num_bytes = get_bytes;

	(void)close(fd);
	return 0;
}

#endif
