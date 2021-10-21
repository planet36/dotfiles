// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Concept for Unordered Associative Container types
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer
\sa https://eel.is/c++draft/unord.req
*/

#pragma once

#include <concepts>
#include <unordered_map>
#include <unordered_set>

template <typename Container>
concept UnorderedAssociativeContainer =
   std::derived_from<Container, std::unordered_map<typename Container::key_type, typename Container::mapped_type>>
|| std::derived_from<Container, std::unordered_multimap<typename Container::key_type, typename Container::mapped_type>>
|| std::derived_from<Container, std::unordered_set<typename Container::key_type>>
|| std::derived_from<Container, std::unordered_multiset<typename Container::key_type>>
;
