// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get a sample of N elements from a \c string or \c vector
/**
\file
\author Steven Ward
\c sample_n works on types that satisfy both \c AllocatorAwareContainer and \c ContiguousContainer.
*/

#pragma once

#include "rand.hpp"

#include <random>
#include <string>
#include <type_traits>
#include <vector>

template <std::uniform_random_bit_generator G>
auto sample_n(const std::string& in, const size_t num_samples, G& gen)
{
	std::remove_cvref_t<decltype(in)> out;

	if (!in.empty())
	{
		out.reserve(num_samples);

		// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution/uniform_int_distribution
		std::uniform_int_distribution<size_t> dis(0, in.size()-1);

		for (size_t n = 0; n < num_samples; ++n)
		{
			out.push_back(in[dis(gen)]);
		}
	}

	return out;
}

template <std::uniform_random_bit_generator G>
auto sample_n(const std::string& in, const size_t num_samples, G&& gen)
{
	return sample_n(in, num_samples, gen);
}

auto sample_n(const std::string& in, const size_t num_samples)
{
	return sample_n(in, num_samples, per_thread_random_number_engine::instance());
}

template <typename T, std::uniform_random_bit_generator G>
auto sample_n(const std::vector<T>& in, const size_t num_samples, G& gen)
{
	std::remove_cvref_t<decltype(in)> out;

	if (!in.empty())
	{
		out.reserve(num_samples);

		// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution/uniform_int_distribution
		std::uniform_int_distribution<size_t> dis(0, in.size()-1);

		for (size_t n = 0; n < num_samples; ++n)
		{
			out.push_back(in[dis(gen)]);
		}
	}

	return out;
}

template <typename T, std::uniform_random_bit_generator G>
auto sample_n(const std::vector<T>& in, const size_t num_samples, G&& gen)
{
	return sample_n(in, num_samples, gen);
}

template <typename T>
auto sample_n(const std::vector<T>& in, const size_t num_samples)
{
	return sample_n(in, num_samples, per_thread_random_number_engine::instance());
}
