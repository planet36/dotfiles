// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get the number of columns needed to represent a UTF-8 string
/**
\file
\author Steven Ward
\sa https://juliastrings.github.io/utf8proc/doc/
\sa https://juliastrings.github.io/utf8proc/doc/utf8proc_8h.html
This is similar to \c wcswidth
\sa https://pubs.opengroup.org/onlinepubs/9699919799/functions/wcswidth.html
\sa https://man7.org/linux/man-pages/man3/wcswidth.3.html
*/

#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <utf8proc.h>

/// Get the number of columns needed to represent a UTF-8 string
size_t
utf8width(const std::string& s)
{
	// https://juliastrings.github.io/utf8proc/doc/utf8proc_8h.html#a0a18a541ba5bedeb5c3e150024063c2d
	static constexpr unsigned int options = 0
		| UTF8PROC_NULLTERM
		| UTF8PROC_STABLE
		| UTF8PROC_COMPOSE
		//| UTF8PROC_IGNORE // removes 00AD
		| UTF8PROC_STRIPCC
		//| UTF8PROC_LUMP // converts FF0D to 002D
		| UTF8PROC_STRIPMARK
		| UTF8PROC_STRIPNA
	;

	size_t num_cols = 0;

	uint8_t* dst = nullptr;

	const ssize_t dstlen =
	    utf8proc_map(reinterpret_cast<const uint8_t*>(s.c_str()), s.size(),
	                 &dst, static_cast<utf8proc_option_t>(options));

	if (dstlen < 0)
		throw std::runtime_error(utf8proc_errmsg(dstlen));

	uint8_t* dst_copy = dst;

	ssize_t bytes_read = 0;
	int32_t codepoint = 0;

	while ((bytes_read = utf8proc_iterate(dst, -1, &codepoint)) > 0)
	{
		if (codepoint == 0)
			break;

		num_cols += utf8proc_charwidth(codepoint);
		dst += bytes_read;
	}

	std::free(dst_copy);

	if (bytes_read < 0)
		throw std::runtime_error(utf8proc_errmsg(bytes_read));

	return num_cols;
}
