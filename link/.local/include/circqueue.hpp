// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Thread-safe C++ circular buffer
/**
\file
\author Steven Ward

\sa https://codetrips.com/2020/07/26/modern-c-writing-a-thread-safe-queue/
*/

#pragma once

#include "unary_predicate_wrapper.hpp"

#include <array>
#include <functional>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <vector>

enum PUSH_RESULT
{
	NOT_PUSHED,
	PUSHED_BUT_SIZE_UNCHANGED,
	PUSHED_AND_SIZE_INCREASED,
};

/// Thread-safe circular queue that uses a std::shared_mutex
template <typename T, size_t N>
class circqueue
{
private:
	size_t head = 0; // remove from the front (head)
	size_t tail = 0; // add to the back (tail)
	size_t size = 0; // the number of elements in the circular queue
	mutable std::shared_mutex mtx;
	std::array<T, N> buf;

	// intentionally private and not thread-safe
	constexpr bool is_empty() const { return size == 0; }

	// intentionally private and not thread-safe
	constexpr bool is_full() const { return size == N; }

	// intentionally private and not thread-safe
	constexpr bool next(size_t& i) const
	{
		if (++i == N)
			i = 0; // index rollover
		return i != tail;
	}

public:
	using value_type = T;

	/// the maximum possible number of elements in the circular queue
	constexpr auto max_size() const { return N; }

	// intentionally not thread-safe
	/// get information (which might be stale before the caller uses it) about the circular queue
	/*
	* https://codetrips.com/2020/07/26/modern-c-writing-a-thread-safe-queue/
	* """
	* A more subtle API change is the removal of the empty() method from public
	* access: now clients can no longer query the Queue about its state, but
	* can only infer its “emptiness state” by attempting to pop an element and
	* obtaining an empty optional.
	*
	* The reason for this is that under no circumstances the Queue can
	* guarantee that matters won’t change between the time the client queries
	* empty() and the time pop() is called, making the point entirely moot, and
	* this code a potential source of intermittent (read: hard to pin) bugs:
	*
	*   if (!queue.empty()) {
	*     // What could possibly go wrong? A lot, it turns out.
	*     auto elem = *queue.pop();
	*   }
	*
	* Obviously, there is a perfectly legitimate use case for the use of
	* empty() as a simple “informational” (and, necessarily, ephemeral)
	* assessment of the state of the Queue, but personally I just prefer to
	* take the gun away from the child, as it would require (a) adding in
	* large, bold font a warning to the user and (b) relying on the user to
	* actually heed that warning.
	*
	* This is a more general approach to API design that holds, loosely: “Make
	* interfaces easy to use right, and hard to use wrong” (originally
	* attributed to Martin Fowler).
	* """
	*/
	void get_stale_info(size_t& head_out,
	                    size_t& tail_out,
	                    size_t& size_out,
	                    bool& empty_out,
	                    bool& full_out) const
	{
		head_out = head;
		tail_out = tail;
		size_out = size;
		empty_out = is_empty();
		full_out = is_full();
	}

	/// add \a x to the back
	/**
	* \retval NOT_PUSHED if \a x was not pushed
	* \retval PUSHED_BUT_SIZE_UNCHANGED if \a x was pushed but the size did not change because the queue was full
	* \retval PUSHED_AND_SIZE_INCREASED if \a x was pushed and the size increased
	*/
	[[nodiscard]] PUSH_RESULT push(const T& x,
	                               const bool overwrite_if_full = false)
	{
		std::unique_lock lock{mtx};

		if (is_full() && !overwrite_if_full)
			return NOT_PUSHED;

		PUSH_RESULT ret;
		buf[tail] = x; // add to tail

		if (is_full())
		{
			if (++head == N) // inc head
				head = 0;    // head rollover

			ret = PUSHED_BUT_SIZE_UNCHANGED;
		}
		else
		{
			++size;

			ret = PUSHED_AND_SIZE_INCREASED;
		}

		if (++tail == N) // inc tail
			tail = 0;    // tail rollover

		return ret;
	}

	/// remove the value from the front
	[[nodiscard]] std::optional<T> pop()
	{
		std::unique_lock lock{mtx};

		if (is_empty())
			return std::nullopt;

		std::optional<T> ret{buf[head]}; // get from head
		buf[head] = T{};                 // reset element

		--size;

		if (++head == N) // inc head
			head = 0;    // head rollover

		return ret;
	}

	/// get the value at the front
	std::optional<T> front() const
	{
		std::shared_lock lock{mtx};

		return is_empty() ? std::nullopt : buf[head];
	}

	/// get the value at the back
	std::optional<T> back() const
	{
		std::shared_lock lock{mtx};

		return is_empty() ? std::nullopt : buf[tail];
	}

	void reset()
	{
		std::unique_lock lock{mtx};

		buf.fill(T{});
		tail = 0;
		head = 0;
		size = 0;
	}

	void for_each(const std::function<void(const T&)>& f) const
	{
		std::shared_lock lock{mtx};

		if (is_empty())
			return;

		size_t i = head;

		do
		{
			f(buf[i]);
		}
		while (next(i));
	}

	// https://en.cppreference.com/w/cpp/algorithm/all_any_none_of

	/// check if unary predicate \a f returns \c true for all elements
	bool all_of(const unary_predicate_wrapper<const T&>& f) const
	{
		std::shared_lock lock{mtx};

		if (is_empty())
			return true;

		size_t i = head;

		do
		{
			if (!f(buf[i]))
				return false;
		}
		while (next(i));

		return true;
	}

	/// check if unary predicate \a f returns \c true for at least one element
	bool any_of(const unary_predicate_wrapper<const T&>& f) const
	{
		std::shared_lock lock{mtx};

		if (is_empty())
			return false;

		size_t i = head;

		do
		{
			if (f(buf[i]))
				return true;
		}
		while (next(i));

		return false;
	}

	/// check if unary predicate \a f returns \c true for no elements
	bool none_of(const unary_predicate_wrapper<const T&>& f) const
	{
		std::shared_lock lock{mtx};

		if (is_empty())
			return true;

		size_t i = head;

		do
		{
			if (f(buf[i]))
				return false;
		}
		while (next(i));

		return true;
	}

	/// get a copy of the circular queue as a \c std::vector
	std::vector<T> as_vector() const
	{
		std::shared_lock lock{mtx};

		if (is_empty())
			return {};

		std::vector<T> ret;
		ret.reserve(size);

		size_t i = head;

		do
		{
			ret.push_back(buf[i]);
		}
		while (next(i));

		return ret;
	}
};
