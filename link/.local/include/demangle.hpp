// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// demangle a mangled name
/**
\file
\author Steven Ward
\sa https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html
\sa https://en.wikipedia.org/wiki/Name_mangling
*/

#pragma once

#include <cstdlib>
#include <cxxabi.h>
#include <string>
#include <typeinfo>

std::string demangle(const char* mangled_name)
{
	char* demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, nullptr);
	const std::string result = (demangled_name == nullptr) ? mangled_name : demangled_name;
	std::free(demangled_name);
	return result;
}

std::string demangle(const std::string& mangled_name)
{
	return demangle(mangled_name.c_str());
}

std::string demangle(const std::type_info& ti)
{
	return demangle(ti.name());
}
