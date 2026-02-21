// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// Get the load averages of the system
/**
* \file
* \author Steven Ward
* \sa https://man7.org/linux/man-pages/man3/getloadavg.3.html
* \sa https://www.gnu.org/software/libc/manual/html_node/Processor-Resources.html
*/

#pragma once

#include <cmath>
#include <cstdlib>
#include <vector>

namespace
{

// XXX: Do not change
constexpr int min_samples = 1;
constexpr int max_samples = 3;

static_assert(min_samples >= 1);
static_assert(max_samples <= 3);
static_assert(min_samples <= max_samples);

}

auto
get_load_avg(int num_samples = max_samples)
{
    if (num_samples < min_samples)
        num_samples = min_samples;
    else if (num_samples > max_samples)
        num_samples = max_samples;

    std::vector<double> load_avg(static_cast<size_t>(num_samples));

    const int num_samples_ret = getloadavg(load_avg.data(), num_samples);

    if (num_samples_ret == -1)
        load_avg.clear();
    else if (num_samples_ret != num_samples)
        load_avg.resize(static_cast<size_t>(num_samples_ret));

    return load_avg;
}

auto
get_load_avg_int(int num_samples = max_samples)
{
    const std::vector<double> load_avg = get_load_avg(num_samples);
    std::vector<long int> load_avg_int;
    load_avg_int.reserve(load_avg.size());

    // https://github.com/torvalds/linux/blob/master/include/linux/sched/loadavg.h#L19
    constexpr long int factor = 1U << 11;

    for (const auto& x : load_avg)
    {
        load_avg_int.push_back(std::lround(x * factor));
    }

    return load_avg_int;
}
