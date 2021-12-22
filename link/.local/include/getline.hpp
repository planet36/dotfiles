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

ssize_t getline(std::string& line, FILE* stream, char delim = '\n')
{
	char* buf = nullptr;
	size_t buf_size = 0;
	const ssize_t bytes_read = getdelim(&buf, &buf_size, delim, stream);
	if (bytes_read >= 0)
		line.assign(buf, bytes_read);
	std::free(buf);
	return bytes_read;
}
