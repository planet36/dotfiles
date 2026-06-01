// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// C++ equivalent of C23 \c typeof_unqual
/**
* \file
* \author Steven Ward
*
* \sa https://en.cppreference.com/c/language/typeof
* > The result of the \c typeof_unqual operator is the non-atomic unqualified
* > type that would result from the \c typeof operator. The \c typeof operator
* > preserves all qualifiers.
*/

#pragma once

#include <type_traits>

#if !defined(decltype_unqual)
#define decltype_unqual(EXPR) std::remove_cvref_t<decltype(EXPR)>
#endif
