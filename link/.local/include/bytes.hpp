// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// convert between array of bytes, datum, and array of data
/**
\file
\author Steven Ward
*/

#pragma once

#include "ne_arr.hpp"

#include <cstdint>
#include <cstring>
#include <type_traits>

/// Alias template for an array of bytes of length \a num_bytes
template <std::size_t num_bytes>
using array_of_bytes = ne_arr<std::uint8_t, num_bytes>;

/// Alias template for an array of \a DatumT of length \a num_data
template <typename DatumT, std::size_t num_data>
using array_of_data = ne_arr<DatumT, num_data>;
