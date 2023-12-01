// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/*
* Usage: printints [TYPE]
* Read integers from stdin and print them in various bases.
*
* The output order is:
*     binary    octal    hexadecimal    unsigned decimal    (signed decimal)
* The signed decimal is only printed if it's not equal to the unsigned decimal.
*
* TYPE is one of:
*   int8
*   int16
*   int32
*   int64
*   uint8
*   uint16
*   uint32
*   uint64
*
* The default TYPE is int32.
*/

#include <concepts>
#include <cstdint>
#include <err.h>
#include <fmt/core.h>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

template <std::unsigned_integral T>
void
print_uint(const T x)
{
	constexpr size_t digits2 = std::numeric_limits<T>::digits;
	// Get the ceiling of the integer division.
	// For all standard T, digits2 is never evenly divisible by 3.
	constexpr size_t digits8 = digits2 / 3 + 1; // == ceil_div(digits2, 3)
	// For all standard T, digits2 is always evenly divisible by 4
	constexpr size_t digits16 = digits2 / 4;

	fmt::print("0b{:0{}b}", x, digits2);
	fmt::print("\t0{:0{}o}", x, digits8);
	fmt::print("\t0x{:0{}x}", x, digits16);
	fmt::print("\t{:d}", x);

	if (const auto i = static_cast<std::make_signed_t<T>>(x); i < 0)
		fmt::print("\t({:d})", i);

	fmt::print("\n");
}

template <std::integral T>
void
read_write_int()
{
	for (std::string line; std::getline(std::cin, line); line.clear())
	{
		try
		{
			if constexpr (std::is_unsigned_v<T>)
			{
				const unsigned long long big_i = std::stoull(line, nullptr, 0);
				print_uint(static_cast<T>(big_i));
			}
			else
			{
				const long long big_i = std::stoll(line, nullptr, 0);
				using U = std::make_unsigned_t<T>;
				print_uint(static_cast<U>(static_cast<T>(big_i)));
			}
		}
		catch (const std::invalid_argument& e)
		{
			errx(EXIT_FAILURE, "%s: %s: %s", e.what(), "std::invalid_argument",
			     line.c_str());
		}
		catch (const std::out_of_range& e)
		{
			errx(EXIT_FAILURE, "%s: %s: %s", e.what(), "std::out_of_range",
			     line.c_str());
		}
	}
}

int
main(int argc, char* const argv[])
{
	std::string type_name = "int32";

	for (int i = 1; i < argc; ++i)
	{
		type_name = argv[i];
	}

	if      (type_name == "int8"  ) read_write_int<int8_t>();
	else if (type_name == "int16" ) read_write_int<int16_t>();
	else if (type_name == "int32" ) read_write_int<int32_t>();
	else if (type_name == "int64" ) read_write_int<int64_t>();
	else if (type_name == "uint8" ) read_write_int<uint8_t>();
	else if (type_name == "uint16") read_write_int<uint16_t>();
	else if (type_name == "uint32") read_write_int<uint32_t>();
	else if (type_name == "uint64") read_write_int<uint64_t>();
	else
		errx(EXIT_FAILURE, "invalid input integer type: %s", type_name.c_str());

	return 0;
}
