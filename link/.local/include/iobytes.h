// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Wrappers for \c fread and \c fwrite that enforce bytes as the member type to read and write, respectively
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/c/io/fread
\sa https://en.cppreference.com/w/c/io/fwrite
*/

#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

inline size_t
fread_bytes(void* buf, const size_t buf_size, FILE* fp)
{
	// https://www.gnu.org/software/libc/manual/html_node/Block-Input_002fOutput.html
	// https://man7.org/linux/man-pages/man3/fread.3p.html#RETURN_VALUE
	// fread(3p) returns the number of items read
	// In our case, each item is 1 byte
	const size_t num_bytes_read = fread(buf, 1, buf_size, fp);

	return num_bytes_read;
}

inline size_t
fwrite_bytes(const void* buf, const size_t buf_size, FILE* fp)
{
	// https://www.gnu.org/software/libc/manual/html_node/Block-Input_002fOutput.html
	// https://man7.org/linux/man-pages/man3/fwrite.3p.html#RETURN_VALUE
	// fwrite(3p) returns the number of items written
	// In our case, each item is 1 byte
	const size_t num_bytes_written = fwrite(buf, 1, buf_size, fp);

	return num_bytes_written;
}

#ifdef __cplusplus
} // extern "C"
#endif
