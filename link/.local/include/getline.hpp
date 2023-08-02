// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// C++ wrappers for getline and getdelim
/**
\file
\author Steven Ward
\sa https://www.man7.org/linux/man-pages/man3/getline.3.html
\sa https://en.cppreference.com/w/c/experimental/dynamic/getline
\sa https://www.gnu.org/software/libc/manual/html_node/Line-Input.html
*/

#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>

/**
\retval true success
\retval false failure
The return value matches the behavior of https://en.cppreference.com/w/cpp/io/basic_ios/operator_bool
*/
bool
getdelim(std::string& line,
         FILE* stream,
         const char delim,
         const bool strip_delim = false)
{
	char* buf = nullptr;
	size_t buf_size = 0;
	const ssize_t bytes_read = ::getdelim(&buf, &buf_size, delim, stream);
	if (bytes_read > 0)
	{
		const bool remove_last_char = strip_delim &&
		                              (buf[bytes_read - 1] == delim);
		line.assign(buf, bytes_read - remove_last_char);
	}
	else
	{
		line.clear();
	}
	std::free(buf);
	return bytes_read != -1;
}

bool
getline(std::string& line, FILE* stream, const bool strip_delim = false)
{
	return getdelim(line, stream, '\n', strip_delim);
}
