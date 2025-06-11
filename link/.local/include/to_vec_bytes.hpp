// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Convert a container to a \c std::vector of \c std::byte
/**
\file
\author Steven Ward
*/

#pragma once

#include <ranges>
#include <span>
#include <vector>

auto
to_vec_bytes(const std::ranges::contiguous_range auto& container)
{
    const auto sp_bytes = std::as_bytes(std::span(container));
    return std::vector(std::cbegin(sp_bytes), std::cend(sp_bytes));
}
