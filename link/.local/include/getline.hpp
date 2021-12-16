// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// C++ wrappers for getline and getdelim
/**
\file
\author Steven Ward
\sa https://www.man7.org/linux/man-pages/man3/getline.3.html
*/

#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>

ssize_t getline(std::string& line, FILE* stream)
{
	char* line_ptr = nullptr;
	size_t buf_size = 0;
	const ssize_t bytes_read = getline(&line_ptr, &buf_size, stream);
	if (bytes_read >= 0)
		line.assign(line_ptr, bytes_read);
	std::free(line_ptr);
	return bytes_read;
}

ssize_t getdelim(std::string& line, char delim, FILE* stream)
{
	char* line_ptr = nullptr;
	size_t buf_size = 0;
	const ssize_t bytes_read = getdelim(&line_ptr, &buf_size, delim, stream);
	if (bytes_read >= 0)
		line.assign(line_ptr, bytes_read);
	std::free(line_ptr);
	return bytes_read;
}
