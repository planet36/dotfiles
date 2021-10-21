// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for Associative Container types
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/named_req/AssociativeContainer
\sa https://eel.is/c++draft/associative.reqmts
*/

#pragma once

#include <concepts>
#include <map>
#include <set>

template <typename Container>
concept AssociativeContainer =
   std::derived_from<Container, std::map<typename Container::key_type, typename Container::mapped_type>>
|| std::derived_from<Container, std::multimap<typename Container::key_type, typename Container::mapped_type>>
|| std::derived_from<Container, std::set<typename Container::key_type>>
|| std::derived_from<Container, std::multiset<typename Container::key_type>>
;
