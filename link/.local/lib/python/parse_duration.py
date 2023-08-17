# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

'''
This module defines a function to parse a duration string into a timedelta object.
'''

__all__ = ['parse_duration']
__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

from collections import OrderedDict
from datetime import timedelta
import re

from number_pattern import FLOAT_FIXED

time_unit_to_abbr_pattern = OrderedDict((
    ('weeks'       , 'weeks?|w|wks?'   ),
    ('days'        , 'days?|d'         ),
    ('hours'       , 'hours?|h|hrs?'   ),
    ('minutes'     , 'minutes?|m|mins?'),
    ('seconds'     , 'seconds?|s|secs?'),
    ('milliseconds', 'milliseconds?|ms'),
    ('microseconds', 'microseconds?|us'),
    ))
'''A dict of time unit strings to abbreviation pattern strings.'''

duration_pattern = re.compile(r',?\s*'.join(
    '((?P<' + time_unit + '>' + FLOAT_FIXED + r')\s*(?:' + abbr_pattern +'))?'
    for time_unit, abbr_pattern in time_unit_to_abbr_pattern.items()
    ), flags=re.ASCII)

timedelta_pattern = re.compile(
    '(?:(?P<days>[0-9]+) days?, )?'
    '(?P<hours>[01]?[0-9]|2[0-3]):'
    '(?P<minutes>[0-5][0-9]):'
    r'(?P<seconds>[0-5][0-9](?:\.[0-9]+)?)'
    , flags=re.ASCII)

def parse_duration(duration: str) -> timedelta:
    '''
    Parse a duration string into a timedelta object.

    The duration time units are restricted to those allowed in datetime.timedelta(),
    and they must be given in descending order of significance.
    <https://docs.python.org/3/library/datetime.html#datetime.timedelta>

    Time-like strings with ":" delimiters are not supported.

    Examples:
        '1 week, 2 days 3hrs, 4minute 5 s 6 milliseconds 7 microseconds' =>
            datetime.timedelta(days=9, seconds=11045, microseconds=6007)

        '12.3456 hours' => datetime.timedelta(seconds=44444, microseconds=160000)

        '11 days, 22:33:44.555666' => datetime.timedelta(days=11, seconds=81224, microseconds=555666)

        '1:02:03.444555' => datetime.timedelta(seconds=3723, microseconds=444555)

        '12:34' => ValueError

        '0:60:00' => ValueError

    Adapted from <https://stackoverflow.com/a/51916936>, which was adapted from
    <https://stackoverflow.com/a/4628148/851699>.

    See also <https://github.com/wroberts/pytimeparse>
    '''

    match = duration_pattern.fullmatch(duration) or timedelta_pattern.fullmatch(duration)

    if match is None:
        raise ValueError(f'Could not parse {duration=}')

    timedelta_params = {time_unit: float(val) for time_unit, val in
                     match.groupdict().items() if val}

    return timedelta(**timedelta_params)
