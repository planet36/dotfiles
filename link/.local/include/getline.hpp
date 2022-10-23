// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// C++ wrappers for getline and getdelim
/**
\file
\author Steven Ward
\sa https://www.man7.org/linux/man-pages/man3/getline.3.html
\sa https://en.cppreference.com/w/c/experimental/dynamic/getline
*/

#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>

ssize_t
getdelim(std::string& line, FILE* stream, char delim, const bool strip_delim = false)
{
	char* buf = nullptr;
	size_t buf_size = 0;
	const ssize_t bytes_read = getdelim(&buf, &buf_size, delim, stream);
	if (bytes_read > 0)
	{
		if (strip_delim && (buf[bytes_read-1] == delim))
			line.assign(buf, bytes_read-1);
		else
			line.assign(buf, bytes_read);
	}
	else
	{
		line.clear();
	}
	std::free(buf);
	return bytes_read;
}

ssize_t
getline(std::string& line, FILE* stream, const bool strip_delim = false)
{
	return getdelim(line, stream, '\n', strip_delim);
}
