// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// duration unit enum
/**
* \file
* \author Steven Ward
*/

#pragma once

#include <chrono>
#include <fmt/ostream.h>
#include <ostream>
#include <string>
#include <utility>

enum struct duration_unit : unsigned char
{
    second,
    minute,
    hour  ,
    day   ,
    week  ,
    month ,
    year  ,
};

//template <typename Rep, typename Period, std::chrono::duration<Rep, Period>>
template <typename Period>
constexpr duration_unit
duration_unit_from()
{
    if constexpr (std::is_same_v<Period, std::chrono::seconds::period>) {return duration_unit::second;}
    if constexpr (std::is_same_v<Period, std::chrono::minutes::period>) {return duration_unit::minute;}
    if constexpr (std::is_same_v<Period, std::chrono::hours  ::period>) {return duration_unit::hour  ;}
    if constexpr (std::is_same_v<Period, std::chrono::days   ::period>) {return duration_unit::day   ;}
    if constexpr (std::is_same_v<Period, std::chrono::weeks  ::period>) {return duration_unit::week  ;}
    if constexpr (std::is_same_v<Period, std::chrono::months ::period>) {return duration_unit::month ;}
    if constexpr (std::is_same_v<Period, std::chrono::years  ::period>) {return duration_unit::year  ;}
    std::unreachable();
}

template <duration_unit U>
constexpr std::string
to_string()
{
    if constexpr (U == duration_unit::second) {return "second";}
    if constexpr (U == duration_unit::minute) {return "minute";}
    if constexpr (U == duration_unit::hour  ) {return "hour"  ;}
    if constexpr (U == duration_unit::day   ) {return "day"   ;}
    if constexpr (U == duration_unit::week  ) {return "week"  ;}
    if constexpr (U == duration_unit::month ) {return "month" ;}
    if constexpr (U == duration_unit::year  ) {return "year"  ;}
    std::unreachable();
}

std::string
to_string(const duration_unit unit)
{
    switch (unit)
    {
    case duration_unit::second: {return to_string<duration_unit::second>();}
    case duration_unit::minute: {return to_string<duration_unit::minute>();}
    case duration_unit::hour  : {return to_string<duration_unit::hour  >();}
    case duration_unit::day   : {return to_string<duration_unit::day   >();}
    case duration_unit::week  : {return to_string<duration_unit::week  >();}
    case duration_unit::month : {return to_string<duration_unit::month >();}
    case duration_unit::year  : {return to_string<duration_unit::year  >();}
    default: std::unreachable();
    }
}

std::ostream&
operator<<(std::ostream& os, const duration_unit unit)
{
    return os << to_string(unit);
}

template <>
struct fmt::formatter<duration_unit> : ostream_formatter
{};
