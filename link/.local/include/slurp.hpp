// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Slurp a file into memory
/**
\file
\author Steven Ward
\sa https://www.delftstack.com/howto/cpp/read-file-into-string-cpp/
*/

#pragma once

// Description of values for errno
// https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html

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

// this version calls fopen, stat, fread, fclose
std::vector<uint8_t>
slurp(const std::filesystem::path& path)
{
	std::FILE* fp = std::fopen(path.c_str(), "r");
	if (fp == nullptr)
	{
		throw std::system_error(std::make_error_code(std::errc{errno}), path);
	}

	struct stat statbuf;
	if (::stat(path.c_str(), &statbuf) < 0)
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

	if (!S_ISREG(statbuf.st_mode) && !S_ISLNK(statbuf.st_mode))
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

	const size_t get_bytes = static_cast<size_t>(statbuf.st_size);

	std::vector<uint8_t> result;

	if (get_bytes == 0)
	{
		result.clear();
	}
	else
	{
		try
		{
			result.resize(get_bytes);
		}
		catch (...)
		{
			(void)std::fclose(fp);
			throw;
		}

		// https://man7.org/linux/man-pages/man3/fread.3p.html#RETURN_VALUE
		// fread(3p) returns the number of items read
		// In our case, each item is 1 byte
		const size_t got_bytes = std::fread(result.data(), 1, result.size(), fp);
		if (got_bytes != get_bytes)
		{
			(void)std::fclose(fp);
			throw std::system_error(std::make_error_code(std::errc{errno}), path);
		}
	}

	(void)std::fclose(fp);
	return result;
}

#else

// this version calls open, fstat, read, close
std::vector<uint8_t>
slurp(const std::filesystem::path& path)
{
	const int fd = ::open(path.c_str(), O_RDONLY);
	if (fd < 0)
	{
		throw std::system_error(std::make_error_code(std::errc{errno}), path);
	}

	struct stat statbuf;
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

	if (!S_ISREG(statbuf.st_mode) && !S_ISLNK(statbuf.st_mode))
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

	const size_t get_bytes = static_cast<size_t>(statbuf.st_size);

	std::vector<uint8_t> result;

	if (get_bytes == 0)
	{
		result.clear();
	}
	else
	{
		try
		{
			result.resize(get_bytes);
		}
		catch (...)
		{
			(void)::close(fd);
			throw;
		}

		// https://www.man7.org/linux/man-pages/man3/read.3p.html#RETURN_VALUE
		// read(3p) returns either an error code or the number of bytes read
		const ssize_t got_bytes = ::read(fd, result.data(), result.size());
		if (got_bytes < 0 || static_cast<size_t>(got_bytes) != get_bytes)
		{
			(void)::close(fd);
			throw std::system_error(std::make_error_code(std::errc{errno}), path);
		}
	}

	(void)::close(fd);
	return result;
}

#endif
