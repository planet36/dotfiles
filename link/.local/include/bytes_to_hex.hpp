// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Convert a span of bytes to a hexadecimal string
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>

/// Convert a nibble to a character
/**
* \param x the nibble value to convert
* \return the lowercase hexadecimal character representing \a x
* \pre \a x is in the interval <code>[0, 15]</code>
*/
[[nodiscard]] static constexpr char
nibble_char(const uint8_t x) noexcept
{
    return static_cast<char>(x + (x < 10 ? '0' : -10 + 'a'));
}

/// Convert a span of bytes to a hexadecimal string
/**
* \param byte_sp the bytes to convert
* \return a lowercase hexadecimal string representing \a byte_sp
*/
[[nodiscard]] static std::string
bytes_to_hex(const std::span<const std::byte> byte_sp)
{
    const size_t result_len = std::size(byte_sp) * 2;

    std::string result(result_len, '\0'); // size == result_len

    size_t i = 0;
    for (const auto b : byte_sp)
    {
        const auto val = std::to_integer<uint8_t>(b);
        const uint8_t hi = val >> 4;
        const uint8_t lo = val & 0x0F;
        result[i++] = nibble_char(hi);
        result[i++] = nibble_char(lo);
    }

    return result;
}
