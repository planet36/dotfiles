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

/// convert the datum to an array of bytes
template <typename DatumT>
constexpr auto
datum_to_bytes(const DatumT& datum)
{
	array_of_bytes<sizeof(DatumT)> bytes{};
	(void)std::memcpy(bytes.data(), &datum, bytes.size());
	return bytes;
}

/// convert the array of bytes to a datum
template <typename DatumT>
constexpr auto
bytes_to_datum(const array_of_bytes<sizeof(DatumT)>& bytes)
{
	DatumT datum{};
	(void)std::memcpy(&datum, bytes.data(), sizeof(DatumT));
	return datum;
}

/// convert the array of data to an array of bytes
template <typename DatumT, std::size_t num_data>
constexpr auto
array_to_bytes(const array_of_data<DatumT, num_data>& data)
{
	array_of_bytes<sizeof(data)> bytes{};
	(void)std::memcpy(bytes.data(), data.data(), bytes.size());
	return bytes;
}

/// convert the array of bytes to an array of data
/** \a num_bytes must be an whole multiple of \c sizeof(DatumT).
* The size of the result array is calculated for you.
*/
template <typename DatumT, std::size_t num_bytes>
requires (num_bytes % sizeof(DatumT) == 0)
constexpr auto
bytes_to_array_of(const array_of_bytes<num_bytes>& bytes)
{
	static constexpr std::size_t num_data = num_bytes / sizeof(DatumT);
	array_of_data<DatumT, num_data> data;
	(void)std::memcpy(data.data(), bytes.data(), num_bytes);
	return data;
}
