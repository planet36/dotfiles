// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/**
* \file
* \author Steven Ward
* \sa https://github.com/planet36/vectors
*
* Defines the class \c fixed_vector, a fixed-capacity vector with in-place storage.
*/

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#if defined(DEBUG)
#include <cassert>
#endif
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstring>
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
*   - An alignment for the data may be given.
*   - \a N elements are value-initialized upon instantiation.
*   - \c clear(), \c pop_back(), and \c resize() only change the size -- they do not destroy
*     any removed elements.
*   - Array elements are never explicitly destroyed.
*   - \c operator[] is unchecked and \b capacity-based: an index in [\c size(), \c capacity())
*     legitimately reads a live element.  \c at() is the only bounds-checked accessor.
*
* Like \c std::inplace_vector, capacity overflow throws \c std::bad_alloc and the \c try_* /
* \c unchecked_* families are provided -- though the \c try_* members return \c bool here
* rather than \c std::inplace_vector's pointer/iterator.
*
* \note <code>Align >= alignof(T)</code> is not needed for correctness here -- \c alignas
* cannot weaken a type's natural alignment -- but is required as a diagnostic: a weakened
* \c alignas is ill-formed ([dcl.align]/5), yet GCC accepts it silently (Clang rejects it), so
* without the constraint an under-alignment request would be quietly ignored.  In
* \c dynamic_fixed_vector the same bound is instead required for correctness: its storage is
* raw bytes from the aligned \c ::operator \c new, which a smaller \a Align would under-align.
*
* \invariant \c size() \c <= \c capacity(), which is \a N.
* \invariant \c data() is never null: the storage is an in-place \c std::array member, so there
* is no empty state that lacks a block (hence none of the null handling in the heap-backed
* siblings' \c data()).
*
* \warning This container is only suitable for trivially destructible types.
*
* \sa https://cppreference.com/w/cpp/container/inplace_vector.html
* \sa https://www.boost.org/doc/libs/latest/doc/html/doxygen/boost_container_header_reference/classboost_1_1container_1_1static__vector.html
*/
template <typename T,
          std::size_t N,
          std::size_t Align = std::max(alignof(std::size_t), alignof(T))>
requires (N > 0) && std::default_initializable<T> && std::movable<T> &&
         std::is_trivially_destructible_v<T> &&
         (std::has_single_bit(Align)) && (Align >= alignof(T))
class fixed_vector
{
private:
    std::size_t size_{};
    alignas(Align) std::array<T, N> data_{};

    constexpr void check_idx_(const std::size_t i) const
    {
        if (i >= size())
            throw std::out_of_range("fixed_vector: index >= size");
    }

    /// \pre \a spn does not overlap this vector's storage.
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

    /// True if \a R is a sized, contiguous range of exactly \c T.
    /**
    * Such a range is handed to the \c std::span overload for its bulk copy.  Overload
    * resolution will not do this on its own: for e.g. \c std::vector<T> the \c R&& template is
    * an exact match while the \c std::span overload needs a user-defined conversion, so the
    * template wins and the bulk path is dead code for callers who do not hand-write a span.
    */
    template <typename R>
    static constexpr bool is_bulk_appendable_ =
        std::ranges::contiguous_range<R> && std::ranges::sized_range<R> &&
        std::same_as<std::ranges::range_value_t<R>, T>;

    /// \pre \a rg satisfies \c is_bulk_appendable_.
    template <typename R>
    [[nodiscard]] static constexpr std::span<const T> as_span_(R& rg)
    {
        return std::span<const T>{std::ranges::data(rg),
                                  static_cast<std::size_t>(std::ranges::size(rg))};
    }

    /// Zero \a n bytes at \a p with stores the compiler must not optimize away.
    /**
    * Uses \c ::memset_explicit (C23) or \c explicit_bzero (glibc, BSDs) when the C library
    * declares one, else writes through a \c volatile pointer.  Neither has a feature-test
    * macro, so availability is probed by unqualified name lookup on the dependent parameter
    * \a P.
    *
    * \note The lookup must stay unqualified; do \b not "modernize" it to
    * \c std::memset_explicit.  libstdc++ 16 does not define that C++26 spelling at any
    * \c -std, and a qualified name into a namespace lacking the member is a hard error rather
    * than a substitution failure -- so the \c requires probe cannot reject it, and the build
    * fails outright instead of reaching the branches below.
    */
    template <typename P>
    static void zero_explicit_(P const p, const std::size_t n) noexcept
    {
        if constexpr (requires { memset_explicit(p, 0, n); })
        {
            memset_explicit(p, 0, n);
        }
        else if constexpr (requires { explicit_bzero(p, n); })
        {
            explicit_bzero(p, n);
        }
        else
        {
            volatile auto* const q = static_cast<volatile unsigned char*>(p);
            for (std::size_t i = 0; i < n; ++i)
            {
                q[i] = 0;
            }
        }
    }

public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// \note Not unconditionally \c noexcept: the in-place \c std::array<T, N> member
    /// value-initializes all \a N elements on this path, and \c std::default_initializable<T>
    /// does not require that construction be non-throwing.
    constexpr fixed_vector() noexcept(std::is_nothrow_default_constructible_v<T>) = default;
    /// \note Copy and move are member-wise (defaulted): moving a trivially copyable \c T leaves
    /// the source unchanged, \b not emptied -- unlike the heap-backed siblings, whose move
    /// construction empties it.
    fixed_vector(const fixed_vector&) noexcept(std::is_nothrow_copy_constructible_v<T>) = default;
    fixed_vector(fixed_vector&&) noexcept(std::is_nothrow_move_constructible_v<T>) = default;
    fixed_vector& operator=(const fixed_vector&) noexcept(std::is_nothrow_copy_assignable_v<T>) = default;
    fixed_vector& operator=(fixed_vector&&) noexcept(std::is_nothrow_move_assignable_v<T>) = default;
    ~fixed_vector() = default;

    /// Create \a count elements equal to \a value (\c size()==count).
    /// \throws std::bad_alloc if \a count > \c max_size().
    constexpr explicit fixed_vector(const std::size_t count, const T& value)
    {
        resize(count, value);
    }

    /// Create \a count value-initialized elements (\c size()==count).
    /**
    * \note This creates elements, unlike the heap-backed siblings' \c X(n), which reserves
    * capacity \a n and starts empty.  Capacity here is already \a N, so the argument can only
    * mean the size.
    * \throws std::bad_alloc if \a count > \c max_size().
    */
    constexpr explicit fixed_vector(const std::size_t count)
    {
        if (count > max_size())
            throw std::bad_alloc{};

        // Elements of data_ are already value-initialized.
        size_ = count;
    }

    /// Copy the elements of \a spn (\c size()==spn.size()).
    /// \throws std::bad_alloc if \a spn does not fit in \c max_size().
    constexpr explicit fixed_vector(const std::span<const T> spn) { append_range(spn); }

    /// Copy the elements of <code>[first, last)</code>.
    /// \throws std::bad_alloc if the source does not fit in \c max_size().
    template <std::input_iterator It, std::sentinel_for<It> S>
    constexpr explicit fixed_vector(It first, S last)
    {
        append_range(first, last);
    }

    /// Copy \a count elements starting at \a first (\c size()==count).
    /// \throws std::bad_alloc if \a count > \c max_size().
    template <std::input_iterator It>
    constexpr explicit fixed_vector(It first, const std::size_t count)
    {
        append_range(first, count);
    }

    /// Copy the elements of \a il (\c size()==il.size()).
    /// \throws std::bad_alloc if \a il does not fit in \c max_size().
    constexpr fixed_vector(const std::initializer_list<T> il) { append_range(il); }

    /// Copy the elements of \a rg.
    /// \throws std::bad_alloc if the source does not fit in \c max_size().
    template <std::ranges::input_range R>
    constexpr explicit fixed_vector(std::from_range_t, R&& rg)
    {
        append_range(std::forward<R>(rg));
    }

    constexpr fixed_vector& operator=(const std::initializer_list<T> il)
    {
        assign_range(il);
        return *this;
    }

    /// Swap the sizes and all \c max_size() array slots (not just the live elements).
    constexpr void swap(fixed_vector& other) noexcept(std::is_nothrow_swappable_v<T>)
    {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    friend constexpr void swap(fixed_vector& a, fixed_vector& b)
        noexcept(std::is_nothrow_swappable_v<T>)
    {
        a.swap(b);
    }

    [[nodiscard]] static constexpr std::size_t capacity() noexcept { return N; }

    [[nodiscard]] static constexpr std::size_t max_size() noexcept { return N; }

    [[nodiscard]] constexpr std::size_t size() const noexcept { return size_; }

    [[nodiscard]] constexpr std::size_t remaining_space() const noexcept
    {
        return max_size() - size();
    }

    [[nodiscard]] constexpr bool is_empty() const noexcept { return size() == 0; }

    [[nodiscard]] constexpr bool is_full() const noexcept { return size() == max_size(); }

    /**
    * \note Does not destroy elements.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/clear.html
    */
    constexpr void clear() noexcept { size_ = 0; }

    /// Resize to \a count elements
    /**
    * Growing assigns \a value to the new elements; shrinking leaves the removed ones alive and
    * unchanged (nothing is destroyed).
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/resize.html
    */
    constexpr void resize(const std::size_t count, const T& value)
    {
        if (count > max_size())
            throw std::bad_alloc{};

        if (count > size())
            (void)std::ranges::fill(data() + size(), data() + count, value);

        size_ = count;
    }

    constexpr void resize(const std::size_t count) { resize(count, T{}); }

    /**
    * \note Does not destroy elements.
    * \note No-op if empty (unlike \c std::inplace_vector::pop_back, where that is UB).
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
    * \note "Emplace" cannot construct in place here: the slot already holds a live element, so
    * a temporary \c T is constructed from \a args and move-assigned in -- equivalent to
    * \c push_back(T(args...)).  Kept for API parity with \c std::inplace_vector.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/unchecked_emplace_back.html
    */
    template <class... Args>
    requires std::constructible_from<T, Args...> && std::assignable_from<T&, T>
    constexpr void unchecked_emplace_back(Args&&... args)
        noexcept(std::is_nothrow_constructible_v<T, Args...> &&
                 std::is_nothrow_assignable_v<T&, T>)
    {
#if defined(DEBUG)
        assert(!is_full());
#endif
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

    /// \sa https://cppreference.com/w/cpp/container/inplace_vector/try_emplace_back.html
    template <class... Args>
    requires std::constructible_from<T, Args...> && std::assignable_from<T&, T>
    [[nodiscard]] constexpr bool try_emplace_back(Args&&... args)
        noexcept(std::is_nothrow_constructible_v<T, Args...> &&
                 std::is_nothrow_assignable_v<T&, T>)
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
    constexpr void unchecked_push_back(const T& value)
        noexcept(noexcept(unchecked_emplace_back(value)))
    {
        unchecked_emplace_back(value);
    }

    /**
    * \pre \c !is_full()
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/unchecked_push_back.html
    */
    constexpr void unchecked_push_back(T&& value)
        noexcept(noexcept(unchecked_emplace_back(std::move(value))))
    {
        unchecked_emplace_back(std::move(value));
    }

    /**
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/push_back.html
    */
    constexpr void push_back(const T& value) { emplace_back(value); }

    constexpr void push_back(T&& value) { emplace_back(std::move(value)); }

    /**
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/try_push_back.html
    */
    [[nodiscard]] constexpr bool try_push_back(const T& value)
        noexcept(noexcept(try_emplace_back(value)))
    {
        return try_emplace_back(value);
    }

    [[nodiscard]] constexpr bool try_push_back(T&& value)
        noexcept(noexcept(try_emplace_back(std::move(value))))
    {
        return try_emplace_back(std::move(value));
    }

    /**
    * Fill all \c max_size() elements with \a value and set \c size() to \c max_size().
    * \sa https://cppreference.com/w/cpp/container/array/fill.html
    */
    constexpr void fill_capacity(const T& value)
        noexcept(std::is_nothrow_copy_assignable_v<T>)
    {
        data_.fill(value);
        size_ = max_size();
    }

    /**
    * Fill the live elements [0, \c size()) with \a value; \c size() is unchanged.
    * \sa https://cppreference.com/w/cpp/algorithm/ranges/fill
    */
    constexpr void fill_size(const T& value)
        noexcept(std::is_nothrow_copy_assignable_v<T>)
    {
        (void)std::ranges::fill(span(), value);
    }

    /// Zeroize the reserved tail elements [\c size(), \c max_size()); \c size() is unchanged.
    /**
    * Each tail element stays alive; its object representation is set to all-zero bytes (for
    * scalar \c T, the value-initialized value).  At run time the stores happen even if nothing
    * reads the tail afterward, so \c clear() followed by this scrubs the whole array -- for
    * sensitive contents, where a plain fill is a dead store the optimizer may elide.  During
    * constant evaluation, where there is no memory to scrub, the tail is value-assigned.
    */
    constexpr void zeroize_remaining_space() noexcept
    requires std::is_trivially_copyable_v<T>
    {
        if consteval
        {
            for (std::size_t i = size(); i < max_size(); ++i)
                data_[i] = T{};
        }
        else
        {
            if (remaining_space() != 0)
                zero_explicit_(static_cast<void*>(data() + size()), remaining_space() * sizeof(T));
        }
    }

    /**
    * \pre \a spn does not overlap this vector's storage.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/append_range.html
    */
    constexpr void append_range(const std::span<const T> spn)
    {
        if (std::size(spn) > remaining_space())
            throw std::bad_alloc{};

        common_append_range_(spn);
    }

    /**
    * \pre <code>[first, last)</code> is a valid range.  For a \c std::sized_sentinel_for this
    * keeps <code>last - first</code> non-negative, so the size check's cast to \c std::size_t
    * is well-defined.
    * \note A \c std::sized_sentinel_for source is checked up front (all-or-nothing); otherwise
    * the elements that fit are appended before \c std::bad_alloc is thrown.
    */
    template <std::input_iterator It, std::sentinel_for<It> S>
    constexpr void append_range(It first, S last)
    {
        if constexpr (std::sized_sentinel_for<S, It>)
        {
            if (static_cast<std::size_t>(last - first) > remaining_space())
                throw std::bad_alloc{};
        }

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
    {
        append_range(std::span<const T>{std::data(il), std::size(il)});
    }

    /**
    * \pre If \a rg is a contiguous range of \c T, it does not overlap this vector's storage:
    * that case is forwarded to the \c std::span overload, which carries the same tag.
    * \note Sized sources are checked up front (all-or-nothing); unsized sources append
    * element-wise and may partially append before throwing \c std::bad_alloc.
    */
    template <std::ranges::input_range R>
    constexpr void append_range(R&& rg)
    {
        if constexpr (is_bulk_appendable_<R>)
        {
            append_range(as_span_(rg));
        }
        else if constexpr (std::ranges::sized_range<R>)
        {
            if (std::ranges::size(rg) > remaining_space())
                throw std::bad_alloc{};

            // The size check above covers every element, so skip the per-element repeat.
            for (auto&& e : std::forward<R>(rg))
            {
                unchecked_emplace_back(std::forward<decltype(e)>(e));
            }
        }
        else
        {
            for (auto&& e : std::forward<R>(rg))
            {
                emplace_back(std::forward<decltype(e)>(e));
            }
        }
    }

    /**
    * \pre \a spn does not overlap this vector's storage.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/try_append_range.html
    */
    [[nodiscard]] constexpr bool try_append_range(const std::span<const T> spn)
    {
        if (std::size(spn) > remaining_space())
            return false;

        common_append_range_(spn);
        return true;
    }

    /**
    * \pre <code>[first, last)</code> is a valid range.  For a \c std::sized_sentinel_for this
    * keeps <code>last - first</code> non-negative, so the size check's cast to \c std::size_t
    * is well-defined.
    * \note A \c std::sized_sentinel_for source is checked up front (nothing appended on
    * \c false); otherwise the elements that fit have already been appended when \c false is
    * returned (observe \c size()).
    */
    template <std::input_iterator It, std::sentinel_for<It> S>
    [[nodiscard]] constexpr bool try_append_range(It first, S last)
    {
        if constexpr (std::sized_sentinel_for<S, It>)
        {
            if (static_cast<std::size_t>(last - first) > remaining_space())
                return false;
        }

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
    {
        return try_append_range(std::span<const T>{std::data(il), std::size(il)});
    }

    /**
    * \pre If \a rg is a contiguous range of \c T, it does not overlap this vector's storage:
    * that case is forwarded to the \c std::span overload, which carries the same tag.
    * \note Sized sources are checked up front (nothing appended on \c false); unsized
    * sources append element-wise, so on \c false the elements that fit have already been
    * appended (observe \c size()).
    */
    template <std::ranges::input_range R>
    [[nodiscard]] constexpr bool try_append_range(R&& rg)
    {
        if constexpr (is_bulk_appendable_<R>)
        {
            return try_append_range(as_span_(rg));
        }
        else if constexpr (std::ranges::sized_range<R>)
        {
            if (std::ranges::size(rg) > remaining_space())
                return false;

            // The size check above covers every element, so skip the per-element repeat.
            for (auto&& e : std::forward<R>(rg))
            {
                unchecked_emplace_back(std::forward<decltype(e)>(e));
            }

            return true;
        }
        else
        {
            for (auto&& e : std::forward<R>(rg))
            {
                if (!try_emplace_back(std::forward<decltype(e)>(e)))
                    return false;
            }

            return true;
        }
    }

    /**
    * \note Does not destroy elements.
    * \pre \a spn does not overlap this vector's storage.
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/assign_range.html
    */
    constexpr void assign_range(const std::span<const T> spn)
    {
        clear();
        append_range(spn);
    }

    template <std::input_iterator It, std::sentinel_for<It> S>
    constexpr void assign_range(It first, S last)
    {
        clear();
        append_range(first, last);
    }

    template <std::input_iterator It>
    constexpr void assign_range(It first, const std::size_t count)
    {
        clear();
        append_range(first, count);
    }

    constexpr void assign_range(const std::initializer_list<T> il)
    {
        clear();
        append_range(il);
    }

    template <std::ranges::input_range R>
    constexpr void assign_range(R&& rg)
    {
        clear();
        append_range(std::forward<R>(rg));
    }

    [[nodiscard]] constexpr std::span<T> span() noexcept { return {data(), size()}; }

    [[nodiscard]] constexpr std::span<const T> span() const noexcept
    {
        return {data(), size()};
    }

    [[nodiscard]] constexpr explicit operator std::span<T>() noexcept { return span(); }

    [[nodiscard]] constexpr explicit operator std::span<const T>() const noexcept
    {
        return span();
    }

    /// \note No \c std::assume_aligned<Align> is needed, unlike the heap-backed siblings: the
    /// array is a member of an \c alignas(Align) object, so the compiler derives the alignment.
    [[nodiscard]] constexpr T* data() noexcept { return std::data(data_); }

    [[nodiscard]] constexpr const T* data() const noexcept { return std::data(data_); }

    /**
    * \pre \c !is_empty()
    */
    [[nodiscard]] constexpr T& front() noexcept
    {
#if defined(DEBUG)
        assert(!is_empty());
#endif
        return *begin();
    }

    [[nodiscard]] constexpr const T& front() const noexcept
    {
#if defined(DEBUG)
        assert(!is_empty());
#endif
        return *begin();
    }

    /**
    * \pre \c !is_empty()
    */
    [[nodiscard]] constexpr T& back() noexcept
    {
#if defined(DEBUG)
        assert(!is_empty());
#endif
        return *rbegin();
    }

    [[nodiscard]] constexpr const T& back() const noexcept
    {
#if defined(DEBUG)
        assert(!is_empty());
#endif
        return *rbegin();
    }

    /**
    * \pre \a i < \c capacity()
    * \note Unchecked and capacity-based: an index in [size(), capacity()) is a valid read,
    * since every capacity slot holds a live element.  \c at() is the bounds-checked accessor.
    */
    [[nodiscard]] constexpr T& operator[](const std::size_t i) noexcept
    {
#if defined(DEBUG)
        assert(i < capacity());
#endif
        return data_[i];
    }

    [[nodiscard]] constexpr const T& operator[](const std::size_t i) const noexcept
    {
#if defined(DEBUG)
        assert(i < capacity());
#endif
        return data_[i];
    }

    /**
    * \returns A reference to the element at index \a i.
    * \note The only bounds-checked accessor, and checked against \c size(), not \c capacity():
    * an element in [size(), capacity()) is alive and \c operator[] reads it, but this rejects
    * that index.
    * \throws std::out_of_range if \a i >= \c size().
    * \sa https://cppreference.com/w/cpp/container/inplace_vector/at.html
    */
    [[nodiscard]] constexpr T& at(const std::size_t i)
    {
        check_idx_(i);
        return data_[i];
    }

    [[nodiscard]] constexpr const T& at(const std::size_t i) const
    {
        check_idx_(i);
        return data_[i];
    }

    [[nodiscard]] constexpr T* begin() noexcept { return data(); }

    [[nodiscard]] constexpr const T* begin() const noexcept { return data(); }

    [[nodiscard]] constexpr const T* cbegin() const noexcept { return data(); }

    [[nodiscard]] constexpr T* end() noexcept { return data() + size(); }

    [[nodiscard]] constexpr const T* end() const noexcept { return data() + size(); }

    [[nodiscard]] constexpr const T* cend() const noexcept { return data() + size(); }

    [[nodiscard]] constexpr std::reverse_iterator<T*> rbegin() noexcept
    {
        return std::reverse_iterator(end());
    }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> rbegin() const noexcept
    {
        return std::reverse_iterator(end());
    }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> crbegin() const noexcept
    {
        return std::reverse_iterator(cend());
    }

    [[nodiscard]] constexpr std::reverse_iterator<T*> rend() noexcept
    {
        return std::reverse_iterator(begin());
    }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> rend() const noexcept
    {
        return std::reverse_iterator(begin());
    }

    [[nodiscard]] constexpr std::reverse_iterator<const T*> crend() const noexcept
    {
        return std::reverse_iterator(cbegin());
    }

    [[nodiscard]] constexpr bool operator==(const fixed_vector& rhs) const
    requires std::equality_comparable<T>
    {
        return std::ranges::equal(span(), rhs.span());
    }

    [[nodiscard]] constexpr auto operator<=>(const fixed_vector& rhs) const
    requires std::three_way_comparable<T>
    {
        return std::lexicographical_compare_three_way(begin(), end(), rhs.begin(), rhs.end());
    }
};
