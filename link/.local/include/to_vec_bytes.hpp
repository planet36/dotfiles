// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Convert a container to a \c std::vector of \c std::byte or \c uint8_t
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <ranges>
#include <span>
#include <vector>

/// Convert a container to a \c std::vector of \c std::byte
auto
to_vec_bytes(const std::ranges::contiguous_range auto& container)
{
    const auto sp_bytes = std::as_bytes(std::span(container));
    return sp_bytes | std::ranges::to<std::vector>();
}

/// Convert a container to a \c std::vector of \c uint8_t
auto
to_vec_uint8(const std::ranges::contiguous_range auto& container)
{
    auto byte_to_uint8 = [](const std::byte b) { return std::to_integer<uint8_t>(b); };
    const auto sp_bytes = std::as_bytes(std::span(container));
    return sp_bytes | std::views::transform(byte_to_uint8) | std::ranges::to<std::vector>();
}
