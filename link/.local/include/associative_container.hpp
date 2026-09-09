// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Concept for an Associative Container type
/**
* \file
* \author Steven Ward
* \sa https://en.cppreference.com/w/cpp/named_req/AssociativeContainer
* \sa https://eel.is/c++draft/associative.reqmts
*/

#pragma once

#include <concepts>

template <typename Container>
concept AssociativeContainer =
    requires (const Container& c, const Container::key_type& k) {
        typename Container::key_type;
        typename Container::key_compare;
        typename Container::const_iterator;
        { c.lower_bound(k) } -> std::same_as<typename Container::const_iterator>;
        { c.upper_bound(k) } -> std::same_as<typename Container::const_iterator>;
        { c.cbegin() } -> std::same_as<typename Container::const_iterator>;
        { c.cend() } -> std::same_as<typename Container::const_iterator>;
    };
