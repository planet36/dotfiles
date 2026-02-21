// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: MPL-2.0

/// time conversion utilities
/**
* \file
* \author Steven Ward
*/

#pragma once

#include "i_to_f.hpp"
#include "number.hpp"

#include <concepts>
#include <type_traits>

inline constexpr unsigned int seconds_per_minute = 60;
inline constexpr unsigned int minutes_per_hour = 60;
inline constexpr unsigned int hours_per_day = 24;
inline constexpr unsigned int days_per_week = 7;
inline constexpr unsigned int months_per_year = 12;

template <std::floating_point T>
inline constexpr T days_per_year{365.2425L}; // Gregorian calendar

template <std::floating_point T>
inline constexpr T days_per_month{30.436875L}; // days_per_year / months_per_year

template <std::floating_point T>
inline constexpr T weeks_per_month{4.348125L}; // days_per_month / days_per_week

template <std::floating_point T>
inline constexpr T weeks_per_year{52.1775L}; // days_per_year / days_per_week

inline constexpr unsigned int seconds_per_hour = 3600;
inline constexpr unsigned int seconds_per_day = 86'400;
inline constexpr unsigned int seconds_per_week = 604'800;
inline constexpr unsigned int seconds_per_year = 31'556'952;
inline constexpr unsigned int seconds_per_month = 2'629'746;

static_assert(seconds_per_hour == seconds_per_minute * minutes_per_hour);
static_assert(seconds_per_day == seconds_per_hour * hours_per_day);
static_assert(seconds_per_week == seconds_per_day * days_per_week);
static_assert(seconds_per_year ==
              static_cast<unsigned int>(days_per_year<long double> * seconds_per_day));
static_assert(seconds_per_month == seconds_per_year / months_per_year);

constexpr auto
seconds_from_minutes(const number auto x_minutes)
{
    return x_minutes * seconds_per_minute;
}

constexpr auto
seconds_from_hours(const number auto x_hours)
{
    return x_hours * seconds_per_hour;
}

constexpr auto
seconds_from_days(const number auto x_days)
{
    return x_days * seconds_per_day;
}

constexpr auto
seconds_from_weeks(const number auto x_weeks)
{
    return x_weeks * seconds_per_week;
}

constexpr auto
seconds_from_months(const number auto x_months)
{
    return x_months * seconds_per_month;
}

constexpr auto
seconds_from_years(const number auto x_years)
{
    return x_years * seconds_per_year;
}

constexpr auto
minutes_from_seconds(const std::unsigned_integral auto x_seconds_abs)
{
    return i_to_f(x_seconds_abs) / seconds_per_minute;
}

constexpr auto
hours_from_seconds(const std::unsigned_integral auto x_seconds_abs)
{
    return i_to_f(x_seconds_abs) / seconds_per_hour;
}

constexpr auto
days_from_seconds(const std::unsigned_integral auto x_seconds_abs)
{
    return i_to_f(x_seconds_abs) / seconds_per_day;
}

constexpr auto
weeks_from_seconds(const std::unsigned_integral auto x_seconds_abs)
{
    return i_to_f(x_seconds_abs) / seconds_per_week;
}

constexpr auto
months_from_seconds(const std::unsigned_integral auto x_seconds_abs)
{
    return i_to_f(x_seconds_abs) / seconds_per_month;
}

constexpr auto
years_from_seconds(const std::unsigned_integral auto x_seconds_abs)
{
    return i_to_f(x_seconds_abs) / seconds_per_year;
}

constexpr auto
minutes_from_seconds(const std::unsigned_integral auto x_seconds_abs,
                     std::remove_const_t<decltype(x_seconds_abs)>& remainder_seconds)
{
    remainder_seconds = x_seconds_abs % seconds_per_minute;
    return x_seconds_abs / seconds_per_minute;
}

constexpr auto
hours_from_seconds(const std::unsigned_integral auto x_seconds_abs,
                   std::remove_const_t<decltype(x_seconds_abs)>& remainder_seconds)
{
    remainder_seconds = x_seconds_abs % seconds_per_hour;
    return x_seconds_abs / seconds_per_hour;
}

constexpr auto
days_from_seconds(const std::unsigned_integral auto x_seconds_abs,
                  std::remove_const_t<decltype(x_seconds_abs)>& remainder_seconds)
{
    remainder_seconds = x_seconds_abs % seconds_per_day;
    return x_seconds_abs / seconds_per_day;
}

constexpr auto
weeks_from_seconds(const std::unsigned_integral auto x_seconds_abs,
                   std::remove_const_t<decltype(x_seconds_abs)>& remainder_seconds)
{
    remainder_seconds = x_seconds_abs % seconds_per_week;
    return x_seconds_abs / seconds_per_week;
}

constexpr auto
months_from_seconds(const std::unsigned_integral auto x_seconds_abs,
                    std::remove_const_t<decltype(x_seconds_abs)>& remainder_seconds)
{
    remainder_seconds = x_seconds_abs % seconds_per_month;
    return x_seconds_abs / seconds_per_month;
}

constexpr auto
years_from_seconds(const std::unsigned_integral auto x_seconds_abs,
                   std::remove_const_t<decltype(x_seconds_abs)>& remainder_seconds)
{
    remainder_seconds = x_seconds_abs % seconds_per_year;
    return x_seconds_abs / seconds_per_year;
}
