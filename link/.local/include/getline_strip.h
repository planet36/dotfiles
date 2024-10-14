// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// C wrappers for getline and getdelim
/**
\file
\author Steven Ward
\sa https://www.man7.org/linux/man-pages/man3/getline.3.html
\sa https://en.cppreference.com/w/c/experimental/dynamic/getline
\sa https://www.gnu.org/software/libc/manual/html_node/Line-Input.html
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/// wrapper for \c getdelim with param \a strip_delim
/**
\param strip_delim if the \a delim should be stripped from the result
*/
ssize_t
getdelim_strip(char** buf,
               size_t* buf_size,
               const int delim,
               FILE* stream,
               const bool strip_delim)
{
	ssize_t bytes_read = getdelim(buf, buf_size, delim, stream);
	if (bytes_read > 0)
	{
		const bool remove_last_char =
		    strip_delim && ((*buf)[bytes_read - 1] == delim);
		if (remove_last_char)
		{
			// Even if delim == '\0', bytes_read must be decremented.
			(*buf)[bytes_read - 1] = '\0';
			--bytes_read;
		}
	}
	return bytes_read;
}

/// wrapper for \c getline with param \a strip_delim
/**
\param strip_delim if the \a delim should be stripped from the result
*/
ssize_t
getline_strip(char** buf,
              size_t* buf_size,
              FILE* stream,
              const bool strip_delim)
{
	constexpr char delim = '\n';
	return getdelim_strip(buf, buf_size, delim, stream, strip_delim);
}

#ifdef __cplusplus
} // extern "C"
#endif
