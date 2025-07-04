// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Get a uniformly distributed random number within an interval
/**
\file
\author Steven Ward
\sa https://en.cppreference.com/w/cpp/experimental/randint
*/

#pragma once

#include "int_bytes.hpp"
#include "integral_number.hpp"
#include "make_unit_float.hpp"
#include "wyrand.hpp"

#include <concepts>
#include <limits>
#include <random>

namespace
{

// This must satisfy std::uniform_random_bit_generator.
thread_local wyrand per_thread_random_number_engine;
static_assert(std::uniform_random_bit_generator<decltype(per_thread_random_number_engine)>);

}

/**
\pre \a a <= \a b
\sa https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
\return a uniformly distributed random integer within the interval [\a a, \a b]
*/
template <integral_number T, std::uniform_random_bit_generator URBG>
T
rand_int(const T a, const T b, URBG& gen)
{
    static_assert(std::numeric_limits<typename URBG::result_type>::digits >=
                  std::numeric_limits<T>::digits);
    return std::uniform_int_distribution<T>{a, b}(gen);
}

template <integral_number T, std::uniform_random_bit_generator URBG>
T
rand_int(const T a, const T b, URBG&& gen)
{
    return rand_int(a, b, gen);
}

template <integral_number T>
T
rand_int(const T a, const T b)
{
    return rand_int(a, b, per_thread_random_number_engine);
}

/**
\return a uniformly distributed random integer within the interval [min, max]
*/
template <integral_number T, std::uniform_random_bit_generator URBG>
T
rand_int(URBG& gen)
{
    static_assert(std::numeric_limits<typename URBG::result_type>::digits >=
                  std::numeric_limits<T>::digits);
    return static_cast<T>(gen());
}

template <integral_number T, std::uniform_random_bit_generator URBG>
T
rand_int(URBG&& gen)
{
    return rand_int<T>(gen);
}

template <integral_number T>
T
rand_int()
{
    return rand_int<T>(per_thread_random_number_engine);
}

/// get a random unsigned integer less than \a s
/**
\return a uniformly distributed random unsigned integer within the interval [0, \a s)
*/
template <std::unsigned_integral T, std::uniform_random_bit_generator URBG>
T
rand_uint_range(const T s, URBG& gen)
{
    constexpr T a = 0;
    const T b = s - 1;
    return rand_int<T>(a, b, gen);
}

template <std::unsigned_integral T, std::uniform_random_bit_generator URBG>
T
rand_uint_range(const T s, URBG&& gen)
{
    return rand_uint_range(s, gen);
}

template <std::unsigned_integral T>
T
rand_uint_range(const T s)
{
    return rand_uint_range(s, per_thread_random_number_engine);
}

/**
\return a uniformly distributed random floating-point number within the interval [0, 1)
*/
template <std::uniform_random_bit_generator URBG>
float
rand_float(URBG& gen)
{
    using T = float;

#if 1
    static_assert(std::numeric_limits<typename URBG::result_type>::digits >=
                      std::numeric_limits<T>::digits,
                  "PRNG does not provide sufficient bits");
    return make_unit_float(static_cast<uint_bytes<sizeof(T)>>(gen()));
#else
    if constexpr (std::numeric_limits<T>::digits <=
                  std::numeric_limits<typename URBG::result_type>::digits)
    {
        return make_unit_float(gen());
    }
    else if constexpr (std::numeric_limits<T>::digits <=
                       2 * std::numeric_limits<typename URBG::result_type>::digits)
    {
        return make_unit_float(int_join(gen(), gen()));
    }
#endif
}

template <std::uniform_random_bit_generator URBG>
float
rand_float(URBG&& gen)
{
    return rand_float(gen);
}

float
rand_float()
{
    return rand_float(per_thread_random_number_engine);
}

/**
\return a uniformly distributed random floating-point number within the interval [0, 1)
*/
template <std::uniform_random_bit_generator URBG>
double
rand_double(URBG& gen)
{
    using T = double;

#if 1
    static_assert(std::numeric_limits<typename URBG::result_type>::digits >=
                      std::numeric_limits<T>::digits,
                  "PRNG does not provide sufficient bits");
    return make_unit_double(static_cast<uint_bytes<sizeof(T)>>(gen()));
#else
    if constexpr (std::numeric_limits<T>::digits <=
                  std::numeric_limits<typename URBG::result_type>::digits)
    {
        return make_unit_double(gen());
    }
    else if constexpr (std::numeric_limits<T>::digits <=
                       2 * std::numeric_limits<typename URBG::result_type>::digits)
    {
        return make_unit_double(int_join(gen(), gen()));
    }
#endif
}

template <std::uniform_random_bit_generator URBG>
double
rand_double(URBG&& gen)
{
    return rand_double(gen);
}

double
rand_double()
{
    return rand_double(per_thread_random_number_engine);
}

/**
\return a uniformly distributed random floating-point number within the interval [0, 1)
*/
template <std::uniform_random_bit_generator URBG>
long double
rand_long_double(URBG& gen)
{
    using T = long double;

#if 1
    static_assert(std::numeric_limits<typename URBG::result_type>::digits >=
                      std::numeric_limits<T>::digits,
                  "PRNG does not provide sufficient bits");
    return make_unit_long_double(static_cast<uint_bytes<sizeof(T)>>(gen()));
#else
    if constexpr (std::numeric_limits<T>::digits <=
                  std::numeric_limits<typename URBG::result_type>::digits)
    {
        return make_unit_long_double(gen());
    }
    else if constexpr (std::numeric_limits<T>::digits <=
                       2 * std::numeric_limits<typename URBG::result_type>::digits)
    {
        return make_unit_long_double(int_join(gen(), gen()));
    }
#endif
}

template <std::uniform_random_bit_generator URBG>
long double
rand_long_double(URBG&& gen)
{
    return rand_long_double(gen);
}

long double
rand_long_double()
{
    return rand_long_double(per_thread_random_number_engine);
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
template <std::uniform_random_bit_generator URBG>
float
rand_float(const float a, const float b, URBG& gen)
{
    const auto x = rand_float(gen);
    // x * (b - a) + a == 2 * (x * (b/2 - a/2) + a/2)
    return 2 * (x * (b/2 - a/2) + a/2);
}

template <std::uniform_random_bit_generator URBG>
float
rand_float(const float a, const float b, URBG&& gen)
{
    return rand_float(a, b, gen);
}

float
rand_float(const float a, const float b)
{
    return rand_float(a, b, per_thread_random_number_engine);
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
template <std::uniform_random_bit_generator URBG>
double
rand_double(const double a, const double b, URBG& gen)
{
    const auto x = rand_double(gen);
    // x * (b - a) + a == 2 * (x * (b/2 - a/2) + a/2)
    return 2 * (x * (b/2 - a/2) + a/2);
}

template <std::uniform_random_bit_generator URBG>
double
rand_double(const double a, const double b, URBG&& gen)
{
    return rand_double(a, b, gen);
}

double
rand_double(const double a, const double b)
{
    return rand_double(a, b, per_thread_random_number_engine);
}

/**
\pre \a a < \a b
\return a uniformly distributed random floating-point number within the interval [\a a, \a b)
*/
template <std::uniform_random_bit_generator URBG>
long double
rand_long_double(const long double a, const long double b, URBG& gen)
{
    const auto x = rand_long_double(gen);
    // x * (b - a) + a == 2 * (x * (b/2 - a/2) + a/2)
    return 2 * (x * (b/2 - a/2) + a/2);
}

template <std::uniform_random_bit_generator URBG>
long double
rand_long_double(const long double a, const long double b, URBG&& gen)
{
    return rand_long_double(a, b, gen);
}

long double
rand_long_double(const long double a, const long double b)
{
    return rand_long_double(a, b, per_thread_random_number_engine);
}

/**
* \sa https://martin.ankerl.com/2018/12/08/fast-random-bool/
* \sa https://gist.github.com/martinus/c43d99ad0008e11fcdbf06982e25f464
*/
template <std::uniform_random_bit_generator URBG>
bool
rand_bool(URBG& gen)
{
    using T = typename URBG::result_type;
    static constexpr T mask_one_msb = T{1} << (std::numeric_limits<T>::digits - 1);
    static thread_local T x = 1;

    if (x == 1) [[unlikely]]
    {
        x = gen() | mask_one_msb;
    }

    const bool ret = x & 1;
    x >>= 1;
    return ret;
}

template <std::uniform_random_bit_generator URBG>
bool
rand_bool(URBG&& gen)
{
    return rand_bool(gen);
}

bool
rand_bool()
{
    return rand_bool(per_thread_random_number_engine);
}
