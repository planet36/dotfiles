// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

// $CXX $CXXFLAGS -std=c++17 dir_is_empty.cpp -o dir_is_empty
#include <cstdlib>
#include <filesystem>

int main(const int argc, const char* const argv[])
{
	int result = EXIT_SUCCESS;

	if (argc >= 2)
	{
		try
		{
			const auto dir_iter = std::filesystem::directory_iterator(argv[1]);

			if (std::filesystem::begin(dir_iter) !=
				std::filesystem::end(dir_iter))
			{
				result = EXIT_FAILURE;
			}
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			result = EXIT_FAILURE;
		}
	} // else: vacuous truth

	return result;
}
