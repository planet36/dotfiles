// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/*
time $CXX $CXXFLAGS as_bool.cpp -o as_bool-cpp ; d as_bool-cpp
*/

#include <regex>

// Evaluate the given string as a boolean
int main(int argc, char* argv[])
{
	const auto regex_flavor = std::regex::ECMAScript;

	const auto leading_spaces_pattern = std::regex(R"(^\s+)", regex_flavor);
	const auto trailing_spaces_pattern = std::regex(R"(\s+$)", regex_flavor);

	// https://docs.python.org/3/library/configparser.html#configparser.ConfigParser.getboolean
	// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Boolean
	const auto true_pattern_1 = std::regex("1|yes|y|true|on", regex_flavor | std::regex::icase);
	const auto false_pattern_1 = std::regex("0|no|n|false|off", regex_flavor | std::regex::icase);
	const auto false_pattern_2 = std::regex("null|nil|none|nan|undefined|-0", regex_flavor | std::regex::icase);

	int result = EXIT_SUCCESS;

	if (argc >= 2)
	{
		std::string s = argv[1];

		if (std::regex_search(s, trailing_spaces_pattern))
		{
			s = std::regex_replace(s, trailing_spaces_pattern, "");
		}

		if (std::regex_search(s, leading_spaces_pattern))
		{
			s = std::regex_replace(s, leading_spaces_pattern, "");
		}

		if (s.empty())
		{
			result = EXIT_FAILURE;
		}
		else if (std::regex_match(s, true_pattern_1))
		{
			result = EXIT_SUCCESS;
		}
		else if (std::regex_match(s, false_pattern_1))
		{
			result = EXIT_FAILURE;
		}
		else if (std::regex_match(s, false_pattern_2))
		{
			result = EXIT_FAILURE;
		}
	} // else: vacuous truth

	return result;
}
