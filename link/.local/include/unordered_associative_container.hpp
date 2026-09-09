// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Concept for an Unordered Associative Container type
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/named_req/UnorderedAssociativeContainer
* \sa https://eel.is/c++draft/unord.req
*/

#pragma once

#include <concepts>

template <typename Container>
concept UnorderedAssociativeContainer =
    requires (const Container& c, const Container::key_type& k) {
        typename Container::key_type;
        typename Container::hasher;
        typename Container::key_equal;
        typename Container::size_type;
        typename Container::const_iterator;
        { c.find(k) } -> std::same_as<typename Container::const_iterator>;
        { c.bucket_count() } -> std::same_as<typename Container::size_type>;
        { c.cbegin() } -> std::same_as<typename Container::const_iterator>;
        { c.cend() } -> std::same_as<typename Container::const_iterator>;
    };
