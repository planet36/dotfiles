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
#include <type_traits>

/// Alias template for an array of bytes of length \a num_bytes
template <std::size_t num_bytes>
using array_of_bytes = ne_arr<std::uint8_t, num_bytes>;

/// Alias template for an array of \a DatumT of length \a num_data
template <typename DatumT, std::size_t num_data>
using array_of_data = ne_arr<DatumT, num_data>;

/// Union with an array of bytes and an array of data of the same size
template <typename DatumT, std::size_t num_data = 1>
requires (std::is_standard_layout_v<DatumT> && std::is_trivial_v<DatumT>)
union byte_array_union
{
	array_of_data<DatumT, num_data> data;
	array_of_bytes<sizeof(data)>    bytes;
};

/// convert the datum to an array of bytes
template <typename DatumT>
constexpr auto
datum_to_bytes(const DatumT& datum)
{
	return byte_array_union<DatumT>{.data{datum}}.bytes;
}

/// convert the array of bytes to a datum
template <typename DatumT>
constexpr auto
bytes_to_datum(const array_of_bytes<sizeof(DatumT)>& bytes)
{
	return byte_array_union<DatumT>{.bytes{bytes}}.data[0];
}

/// convert the array of data to an array of bytes
template <typename DatumT, std::size_t num_data>
constexpr auto
array_to_bytes(const array_of_data<DatumT, num_data>& data)
{
	return byte_array_union<DatumT, num_data>{.data{data}}.bytes;
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
	return byte_array_union<DatumT, num_data>{.bytes{bytes}}.data;
}
