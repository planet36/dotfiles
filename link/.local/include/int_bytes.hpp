// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// compile-time typing of integers based on a given byte size
/**
\file
\author Steven Ward
\sa https://peter.bloomfield.online/using-cpp-templates-for-size-based-type-selection/
*/

#pragma once

#include <cstdint>
#include <type_traits>

template <unsigned int N>
using int_bytes =
std::conditional_t<N <= sizeof(std::int8_t), std::int8_t,
	std::conditional_t<N <= sizeof(std::int16_t), std::int16_t,
		std::conditional_t<N <= sizeof(std::int32_t), std::int32_t,
			std::conditional_t<N <= sizeof(std::int64_t), std::int64_t,
#if defined(__SIZEOF_INT128__)
				std::conditional_t<N <= sizeof(__int128), __int128, void>
#else
				void
#endif
			>
		>
	>
>;

template <unsigned int N>
using uint_bytes =
std::conditional_t<N <= sizeof(std::uint8_t), std::uint8_t,
	std::conditional_t<N <= sizeof(std::uint16_t), std::uint16_t,
		std::conditional_t<N <= sizeof(std::uint32_t), std::uint32_t,
			std::conditional_t<N <= sizeof(std::uint64_t), std::uint64_t,
#if defined(__SIZEOF_INT128__)
				std::conditional_t<N <= sizeof(unsigned __int128), unsigned __int128, void>
#else
				void
#endif
			>
		>
	>
>;
