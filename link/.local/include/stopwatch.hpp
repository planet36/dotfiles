// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// A stopwatch
/**
\file
\author Steven Ward

You can start, stop, and reset the stopwatch.
*/

#pragma once

#include <chrono>

struct stopwatch
{
public:
	// http://www.cplusplus.com/forum/general/187899/#msg913531
	using stopwatch_clock = typename std::conditional_t<
		std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock, std::chrono::steady_clock>;

	stopwatch()
	{
		reset();
	}

	stopwatch(const stopwatch&) = delete;

	void start()
	{
		if (!running)
		{
			running = true;
			t0 = stopwatch_clock::now();
		}
	}

	void stop()
	{
		if (running)
		{
			dt += stopwatch_clock::now() - t0;
			running = false;
		}
	}

	void reset()
	{
		dt = decltype(dt)::zero();
		running = false;
	}

	std::chrono::duration<double> get_elapsed_time() const
	{
		if (!running)
			return dt;
		else
			return dt + (stopwatch_clock::now() - t0);
	}

	bool is_running() const
	{
		return running;
	}

private:
	std::chrono::time_point<stopwatch_clock> t0{};
	std::chrono::duration<double> dt{};
	bool running{};
};
