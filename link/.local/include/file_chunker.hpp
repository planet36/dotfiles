// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Process a file stream in discrete chunks
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "iobytes.h"

#include <algorithm>
#include <array>
#include <cassert> // DEBUG
#include <cerrno>
#include <cstddef>
#include <ios>
#include <ranges>
#include <span>
#include <system_error>

/// Process the file stream \a fp in discrete chunks
/**
* \a func_process_chunk should take a <code>std::span<const std::byte></code>.
*
* \pre \a chunk_size is at least \c 1.
* \pre \a chunk_size is at most \a buf_size.
*/
template <size_t chunk_size, size_t buf_size = 32 * 1024>
void
file_chunker(FILE* fp, const auto& func_process_chunk)
{
    static_assert(chunk_size >= 1);
    static_assert(chunk_size <= buf_size);

    std::array<std::byte, buf_size> buf;

    bool continue_reading = true;

    do
    {
        size_t num_bytes_read = fread_bytes(std::data(buf), buf_size, fp);

        continue_reading = (num_bytes_read == buf_size);

        if (num_bytes_read != buf_size)
        {
            // https://www.gnu.org/software/libc/manual/html_node/EOF-and-Errors.html
            if (std::ferror(fp) != 0)
                throw std::system_error(std::make_error_code(std::errc{errno}));

            assert(std::feof(fp) != 0); // DEBUG
        }

        const std::span<std::byte> span_bytes{std::data(buf), num_bytes_read};

        std::ranges::for_each(std::views::chunk(span_bytes, chunk_size), func_process_chunk);
    }
    while (continue_reading);
}

/// Process the file stream \a fp in discrete chunks, and apply length padding
/**
* \a func_process_chunk should take a <code>std::span<const std::byte></code>.
*
* \pre \a chunk_size is at least \c 1.
* \pre \a chunk_size is at most \a buf_size.
* \pre \a chunk_size is at most \c 255.
* \pre \a buf_size must be an even multiple of \a chunk_size.
*
* Each chunk is padded to \a chunk_size bytes.
*
* The last byte of the last chunk indicates how many padding bytes were added.
*
* \sa https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS#5_and_PKCS#7
* > If the length of the original data is an integer multiple of the block size B, then an extra block of bytes with value B is added.
*
* This function is only different in that the value of the padding bytes increases, starting with \c 1 and ending with (at most) \a chunk_size.
*/
template <size_t chunk_size, size_t buf_size = 32 * 1024>
void
file_chunker_padded(FILE* fp, const auto& func_process_chunk)
{
    static_assert(chunk_size >= 1);
    static_assert(chunk_size <= buf_size);
    static_assert(chunk_size <= UINT8_MAX, "The maximum value of a padding byte is 255.");
    static_assert((buf_size % chunk_size) == 0,
                  "buf_size must be an even multiple of chunk_size.");

    std::array<std::byte, buf_size> buf;

    bool continue_reading = true;

    do
    {
        size_t num_bytes_read = fread_bytes(std::data(buf), buf_size, fp);

        continue_reading = (num_bytes_read == buf_size);

        if (num_bytes_read != buf_size)
        {
            // https://www.gnu.org/software/libc/manual/html_node/EOF-and-Errors.html
            if (std::ferror(fp) != 0)
                throw std::system_error(std::make_error_code(std::errc{errno}));

            assert(std::feof(fp) != 0); // DEBUG

            // pad to the next chunk boundary
            const size_t num_bytes_to_pad = chunk_size - num_bytes_read % chunk_size;

            assert(num_bytes_read + num_bytes_to_pad <= buf_size); // DEBUG

            // The padding bytes are 1..num_bytes_to_pad
            for (size_t i = 1; i <= num_bytes_to_pad; ++i)
            {
                buf[num_bytes_read++] = std::byte{static_cast<uint8_t>(i)};
            }
        }

        assert((num_bytes_read % chunk_size) == 0); // DEBUG

        const std::span<std::byte> span_bytes{std::data(buf), num_bytes_read};

        std::ranges::for_each(std::views::chunk(span_bytes, chunk_size), func_process_chunk);
    }
    while (continue_reading);
}
