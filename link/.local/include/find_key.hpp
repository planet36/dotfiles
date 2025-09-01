// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Find a key in an \c AssociativeContainer
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "associative_container.hpp"

/**
* Return an iterator to the last element whose key is < \a key.
* If no such element is found, the past-the-end iterator is returned.
*/
template <AssociativeContainer C>
typename C::const_iterator
find_key_less(const C& c, const typename C::key_type& key)
{
    auto iter = c.lower_bound(key);
    if (iter == c.cbegin())
        return c.cend();
    return --iter;
}

/**
* Return an iterator to the last element whose key is <= \a key.
* If no such element is found, the past-the-end iterator is returned.
*/
template <AssociativeContainer C>
typename C::const_iterator
find_key_less_equal(const C& c, const typename C::key_type& key)
{
    auto iter = c.upper_bound(key);
    if (iter == c.cbegin())
        return c.cend();
    return --iter;
}

/**
* Return an iterator to the first element whose key is >= \a key.
* If no such element is found, the past-the-end iterator is returned.
*/
template <AssociativeContainer C>
typename C::const_iterator
find_key_greater_equal(const C& c, const typename C::key_type& key)
{
    return c.lower_bound(key);
}

/**
* Return an iterator to the first element whose key is > \a key.
* If no such element is found, the past-the-end iterator is returned.
*/
template <AssociativeContainer C>
typename C::const_iterator
find_key_greater(const C& c, const typename C::key_type& key)
{
    return c.upper_bound(key);
}
