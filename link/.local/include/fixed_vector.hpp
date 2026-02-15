// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/**
* \file
* \author Steven Ward
*
* Defines the class \c fixed_vector, a fixed-capacity vector with in-place storage.
*/

#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <new>
#include <ranges>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <utility>

/// A resizable array container with fixed capacity.
/**
* This is similar to \c std::inplace_vector and \c boost::container::static_vector,
* except for these important differences:
*   - The data is stored in a `std::array<T, N>`.
*   - \a N elements are value-initialized upon instantiation.
*   - \c clear(), \c pop_back(), and \c resize() only change the size -- they do not destroy
*     any removed elements.
*   - Array elements are never explicitly destroyed.
*
* \warning This container is only suitable for trivially destructible types.
*
* \sa https://cppreference.com/w/cpp/container/inplace_vector.html
* \sa https://www.boost.org/doc/libs/latest/doc/html/doxygen/boost_container_header_reference/classboost_1_1container_1_1static__vector.html
*/
template <typename T, std::size_t N>
requires (N > 0) && std::default_initializable<T> && std::movable<T> &&
         std::is_trivially_destructible_v<T>
class fixed_vector
{
private:

    std::size_t size_{};
    std::array<T, N> data_{};

    /// Check the index \a i against \c size()
    constexpr void check_idx_(const std::size_t i) const
    {
        if (i >= size())
            throw std::out_of_range("fixed_vector: index >= size");
    }

    constexpr void common_append_range_(const std::span<const T> spn)
    {
        (void)std::ranges::copy(spn, end());
        size_ += std::size(spn);
    }

    template <std::input_iterator It>
    constexpr void common_append_range_(It first, const std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            unchecked_emplace_back(*first);
            ++first;
        }
    }

public:

    constexpr fixed_vector() noexcept = default;
    fixed_vector(const fixed_vector&) noexcept(std::is_nothrow_copy_constructible_v<T>) = default;
    fixed_vector(fixed_vector&&) noexcept(std::is_nothrow_move_constructible_v<T>) = default;
    fixed_vector& operator=(const fixed_vector&) noexcept(std::is_nothrow_copy_assignable_v<T>) = default;
    fixed_vector& operator=(fixed_vector&&) noexcept(std::is_nothrow_move_assignable_v<T>) = default;
    ~fixed_vector() = default;

    constexpr explicit fixed_vector(const std::size_t count, const T& value)
    { resize(count, value); }

    constexpr explicit fixed_vector(const std::size_t count)
    {
        if (count > max_size())
            throw std::bad_alloc{};

        // Elements of \c data_ are already value-initialized.
        size_ = count;
    }

    constexpr explicit fixed_vector(const std::span<const T> spn)
    { append_range(spn); }

    template <std::input_iterator It, std::sentinel_for<It> S>
    constexpr explicit fixed_vector(It first, S last)
    { append_range(first, last); }

    template <std::input_iterator It>
    constexpr explicit fixed_vector(It first, const std::size_t count)
    { append_range(first, count); }

    constexpr fixed_vector(const std::initializer_list<T> il)
    { append_range(il); }

    template <std::ranges::input_range R>
    constexpr explicit fixed_vector(std::from_range_t, R&& rg)
    { append_range(std::forward<R>(rg)); }

    constexpr fixed_vector& operator=(const std::initializer_list<T> il)
    { assign_range(il); return *this; }

    [[nodiscard]] static constexpr std::size_t capacity() noexcept { return N; }

    [[nodiscard]] static constexpr std::size_t max_size() noexcept { return N; }

    [[nodiscard]] constexpr std::size_t size() const noexcept { return size_; }

    [[nodiscard]] constexpr std::size_t remaining_space() const noexcept
    { return max_size() - size(); }

    [[nodiscard]] constexpr bool is_empty() const noexcept { return size() == 0; }

    [[nodiscard]] constexpr bool is_full() const noexcept { return size() == max_size(); }

    /**
    * \note Does not destroy elements.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/clear.html
    */
    constexpr void clear() noexcept { size_ = 0; }

    /// Resize to \a count elements
    /**
    * If \a count > \c size(), new elements are assigned \a value.
    * If \a count <= \c size(), removed elements are unchanged.
    * \note Does not destroy elements.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/resize.html
    */
    constexpr void resize(const std::size_t count, const T& value)
    {
        if (count > max_size())
            throw std::bad_alloc{};

        for (std::size_t i = size(); i < count; ++i)
        {
            data_[i] = value;
        }

        size_ = count;
    }

    constexpr void resize(const std::size_t count) { resize(count, T{}); }

    /**
    * \note Does not destroy elements.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/pop_back.html
    */
    constexpr void pop_back() noexcept
    {
        if (is_empty())
            return;

        --size_;
    }

    /**
    * \pre \c !is_full()
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/unchecked_emplace_back.html
    */
    template <class... Args>
    requires std::constructible_from<T, Args...> && std::assignable_from<T&, T>
    constexpr void unchecked_emplace_back(Args&&... args)
    {
        *end() = T(std::forward<Args>(args)...);
        ++size_;
    }

    /**
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/emplace_back.html
    */
    template <class... Args>
    requires std::constructible_from<T, Args...> && std::assignable_from<T&, T>
    constexpr void emplace_back(Args&&... args)
    {
        if (is_full())
            throw std::bad_alloc{};

        unchecked_emplace_back(std::forward<Args>(args)...);
    }

    /**
    * \retval true if success
    * \retval false if failure
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/try_emplace_back.html
    */
    template <class... Args>
    requires std::constructible_from<T, Args...> && std::assignable_from<T&, T>
    [[nodiscard]] constexpr bool try_emplace_back(Args&&... args)
    {
        if (is_full())
            return false;

        unchecked_emplace_back(std::forward<Args>(args)...);
        return true;
    }

    /**
    * \pre \c !is_full()
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/unchecked_push_back.html
    */
    constexpr void unchecked_push_back(const T& value) { unchecked_emplace_back(value); }

    constexpr void unchecked_push_back(T&& value) { unchecked_emplace_back(std::move(value)); }

    /**
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/push_back.html
    */
    constexpr void push_back(const T& value) { emplace_back(value); }

    constexpr void push_back(T&& value) { emplace_back(std::move(value)); }

    /**
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/try_push_back.html
    */
    [[nodiscard]] constexpr bool try_push_back(const T& value)
    { return try_emplace_back(value); }

    [[nodiscard]] constexpr bool try_push_back(T&& value)
    { return try_emplace_back(std::move(value)); }

    /**
    * \sa https://cppreference.com/w/cpp/container/array/fill.html
    */
    constexpr void fill_capacity(const T& value) { data_.fill(value); size_ = max_size(); }

    /**
    * \sa https://cppreference.com/w/cpp/algorithm/ranges/fill
    */
    constexpr void fill_size(const T& value) { (void)std::ranges::fill(span(), value); }

    /**
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/append_range.html
    */
    constexpr void append_range(const std::span<const T> spn)
    {
        if (std::size(spn) > remaining_space())
            throw std::bad_alloc{};

        common_append_range_(spn);
    }

    template <std::input_iterator It, std::sentinel_for<It> S>
    constexpr void append_range(It first, S last)
    {
        for (; first != last; ++first)
        {
            emplace_back(*first);
        }
    }

    template <std::input_iterator It>
    constexpr void append_range(It first, const std::size_t count)
    {
        if (count > remaining_space())
            throw std::bad_alloc{};

        common_append_range_(first, count);
    }

    constexpr void append_range(const std::initializer_list<T> il)
    { append_range(std::begin(il), std::end(il)); }

    template <std::ranges::input_range R>
    constexpr void append_range(R&& rg)
    {
        if constexpr (std::ranges::sized_range<R>)
        {
            if (std::ranges::size(rg) > remaining_space())
                throw std::bad_alloc{};
        }

        for (auto&& e : rg)
        {
            emplace_back(std::forward<decltype(e)>(e));
        }
    }

    /**
    * \retval false if failure
    * \retval true if success
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/try_append_range.html
    */
    [[nodiscard]] constexpr bool try_append_range(const std::span<const T> spn)
    {
        if (std::size(spn) > remaining_space())
            return false;

        common_append_range_(spn);
        return true;
    }

    template <std::input_iterator It, std::sentinel_for<It> S>
    [[nodiscard]] constexpr bool try_append_range(It first, S last)
    {
        for (; first != last; ++first)
        {
            if (!try_emplace_back(*first))
                return false;
        }

        return true;
    }

    template <std::input_iterator It>
    [[nodiscard]] constexpr bool try_append_range(It first, const std::size_t count)
    {
        if (count > remaining_space())
            return false;

        common_append_range_(first, count);
        return true;
    }

    [[nodiscard]] constexpr bool try_append_range(const std::initializer_list<T> il)
    { return try_append_range(std::begin(il), std::end(il)); }

    template <std::ranges::input_range R>
    [[nodiscard]] constexpr bool try_append_range(R&& rg)
    {
        if constexpr (std::ranges::sized_range<R>)
        {
            if (std::ranges::size(rg) > remaining_space())
                return false;
        }

        for (auto&& e : rg)
        {
            if (!try_emplace_back(std::forward<decltype(e)>(e)))
                return false;
        }

        return true;
    }

    /**
    * \note Does not destroy elements.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/assign_range.html
    */
    constexpr void assign_range(const std::span<const T> spn) { clear(); append_range(spn); }

    template <std::input_iterator It, std::sentinel_for<It> S>
    constexpr void assign_range(It first, S last) { clear(); append_range(first, last); }

    template <std::input_iterator It>
    constexpr void assign_range(It first, const std::size_t count)
    { clear(); append_range(first, count); }

    constexpr void assign_range(const std::initializer_list<T> il) { clear(); append_range(il); }

    template <std::ranges::input_range R>
    constexpr void assign_range(R&& rg) { clear(); append_range(std::forward<R>(rg)); }

    [[nodiscard]] constexpr std::span<T> span() noexcept { return {data(), size()}; }

    [[nodiscard]] constexpr std::span<const T> span() const noexcept { return {data(), size()}; }

    [[nodiscard]] constexpr explicit operator std::span<T>() noexcept { return span(); }

    [[nodiscard]] constexpr explicit operator std::span<const T>() const noexcept { return span(); }

    [[nodiscard]] constexpr T* data() noexcept { return std::data(data_); }

    [[nodiscard]] constexpr const T* data() const noexcept { return std::data(data_); }

    /**
    * \pre \c !is_empty()
    */
    [[nodiscard]] constexpr T& front() noexcept { return *begin(); }

    [[nodiscard]] constexpr const T& front() const noexcept { return *begin(); }

    /**
    * \pre \c !is_empty()
    */
    [[nodiscard]] constexpr T& back() noexcept { return *rbegin(); }

    [[nodiscard]] constexpr const T& back() const noexcept { return *rbegin(); }

    /**
    * \pre \a i < \c size()
    * \note Does not check bounds.
    */
    [[nodiscard]] constexpr T& operator[](const std::size_t i) noexcept { return data_[i]; }

    [[nodiscard]] constexpr const T& operator[](const std::size_t i) const noexcept
    { return data_[i]; }

    [[nodiscard]] constexpr T& at(const std::size_t i) { check_idx_(i); return data_[i]; }

    [[nodiscard]] constexpr const T& at(const std::size_t i) const
    { check_idx_(i); return data_[i]; }

    [[nodiscard]] constexpr T* begin() noexcept { return data(); }

    [[nodiscard]] constexpr const T* begin() const noexcept { return data(); }

    [[nodiscard]] constexpr const T* cbegin() const noexcept { return data(); }

    [[nodiscard]] constexpr T* end() noexcept { return data() + size(); }

    [[nodiscard]] constexpr const T* end() const noexcept { return data() + size(); }

    [[nodiscard]] constexpr const T* cend() const noexcept { return data() + size(); }

    [[nodiscard]] constexpr std::reverse_iterator<T*> rbegin() noexcept
    { return std::reverse_iterator(end()); }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> rbegin() const noexcept
    { return std::reverse_iterator(end()); }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> crbegin() const noexcept
    { return std::reverse_iterator(cend()); }

    [[nodiscard]] constexpr std::reverse_iterator<T*> rend() noexcept
    { return std::reverse_iterator(begin()); }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> rend() const noexcept
    { return std::reverse_iterator(begin()); }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> crend() const noexcept
    { return std::reverse_iterator(cbegin()); }

    [[nodiscard]] constexpr bool operator==(const fixed_vector& rhs) const
    requires std::equality_comparable<T>
    { return std::ranges::equal(span(), rhs.span()); }

    [[nodiscard]] constexpr auto operator<=>(const fixed_vector& rhs) const
    requires std::three_way_comparable<T>
    { return std::lexicographical_compare_three_way(begin(), end(), rhs.begin(), rhs.end()); }
};
