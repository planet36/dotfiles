# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=invalid-name
# pylint: disable=line-too-long
# pylint: disable=redefined-outer-name

"""
Usage:
python3 generate-bit-patterns.py > bit_patterns.hpp
"""

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

import datetime as dt
import itertools
import math
import os.path
import platform
import random
import warnings

now = dt.datetime.now(dt.timezone.utc)
brief_description = 'selected bit patterns'
generated_by_file_name = os.path.basename(__file__)
generated_datetime = now.isoformat(timespec='seconds')
system_info = platform.platform()

print(fr'''// SPDX-FileCopyrightText: {__author__}
// SPDX-License-Identifier: {__license__}

// vim: set foldmethod=marker foldlevel=0:

/// {brief_description}
/**
\file
\author {__author__}
Only odd integers whose most significant bit is set are included.
*/

// Generated by "{generated_by_file_name}" on {generated_datetime}
// system information: {system_info}

#pragma once

#include <array>
#include <cstdint>
''')


def has_forbidden_substring(s: str) -> bool:
    '''Determine if the string has a forbidden substring.'''

    for substr in (
            '000',
            '111',
            #'0011',
            #'1100',
            '00100',
            '11011',
            '001100',
            '110011',
            '0010100',
            '1101011',
            #'11001100', # 0xcc
            #'00110011', # 0x33
            #'010101010101', # 0x555
            #'101010101010', # 0xaaa
            ):
        if substr in s:
            return True

    return False


def has_forbidden_prefix(s: str) -> bool:
    '''Determine if the string has a forbidden prefix.'''

    for prefix in (
            #'0b0',
            #'0b00',
            #'0b100',
            #'0b11',
            #'0b100100',
            ):
        if s.startswith(prefix):
            return True

    return False


def has_forbidden_suffix(s: str) -> bool:
    '''Determine if the string has a forbidden suffix.'''

    for suffix in (
            #'0',
            #'00',
            #'11',
            #'001',
            #'001001',
            ):
        if s.endswith(suffix):
            return True

    return False


def to_bin_str(i: int, bits: int) -> str:
    '''Get the binary representation of the int with padding.'''
    return f'0b{i:0{bits}b}'


def to_hex_str(i: int, bits: int) -> str:
    '''Get the hexadecimal representation of the int with padding.'''
    nibbles = bits // 4
    return f'0x{i:0{nibbles}x}'


def to_dec_thou_str(i: int, max_len: int = None, sep: str = None) -> str:
    '''Get the decimal representation of the int with padding and the given separator as the thousands separator.'''
    result = None
    if max_len is None:
        result = f'{i:,}'
    else:
        result = f'{i:{max_len},}'
    if sep is None or sep == ',':
        return result
    return result.replace(',', sep)


def to_dec_thou_str_cpp(i: int, max_len: int = None) -> str:
    '''Get the decimal representation of the int with padding and single quotes as the thousands separator (for C++).'''
    return to_dec_thou_str(i, max_len, "'")


# Generate sample bytes
bits = 8
sample_bytes_all = []
#for i in range(0x50, 0xb0):
#for i in range(0x40, 0xc0):
for i in range(0x00, 0xff+1):
    if i.bit_count() != bits // 2:
        continue
    #if i % 2 == 0: # even number
        #continue
    #if i >> (bits-1) == 0: # MSB is 0
        #continue
    s = to_bin_str(i, bits)
    if has_forbidden_substring(s):
        continue
    #if has_forbidden_prefix(s):
        #continue
    #if has_forbidden_suffix(s):
        #continue
    sample_bytes_all.append(i)

# A limited selection of sample bytes (manually chosen)
sample_bytes_limited = [
    #0x2b, # 0b00101011
    #0x2d, # 0b00101101
    #0x35, # 0b00110101
    0x4b, # 0b01001011
    #0x4d, # 0b01001101
    #0x53, # 0b01010011
    0x55, # 0b01010101
    #0x56, # 0b01010110
    #0x59, # 0b01011001
    0x5a, # 0b01011010
    0x65, # 0b01100101
    #0x69, # 0b01101001
    0x6a, # 0b01101010
    0x95, # 0b10010101
    #0x96, # 0b10010110
    0x9a, # 0b10011010
    0xa5, # 0b10100101
    #0xa6, # 0b10100110
    #0xa9, # 0b10101001
    0xaa, # 0b10101010
    #0xac, # 0b10101100
    #0xb2, # 0b10110010
    0xb4, # 0b10110100
    #0xca, # 0b11001010
    #0xd2, # 0b11010010
    #0xd4, # 0b11010100
]

print(r'''/**
Python snippet
\code{.py}''')

print(f'# {len(sample_bytes_all) = }')
print('sample_bytes_all = [')
for i in sample_bytes_all:
    print(f'    {to_hex_str(i, bits)}, # {to_bin_str(i, bits)}')
print(']')

print()

print(f'# {len(sample_bytes_limited) = }')
print('sample_bytes_limited = [')
for i in sample_bytes_limited:
    print(f'    {to_hex_str(i, bits)}, # {to_bin_str(i, bits)}')
print(']')

print(r'''\endcode
*/''')

# Ensure correct bit count
for i in sample_bytes_all:
    assert i.bit_count() == bits // 2
for i in sample_bytes_limited:
    assert i.bit_count() == bits // 2

max_iterations_allowed = 10_000_000

bit_patterns = {}

for bits in (16, 32, 64):
    bit_patterns[bits] = []

    bytes_per_int = bits // 8

    num_products_all = len(sample_bytes_all) ** bytes_per_int
    num_permutations_all = math.perm(len(sample_bytes_all), bytes_per_int)
    num_products_limited = len(sample_bytes_limited) ** bytes_per_int
    num_permutations_limited = math.perm(len(sample_bytes_limited), bytes_per_int)

    print()
    print(f'// {len(sample_bytes_all) = }, {len(sample_bytes_limited) = }, {bytes_per_int = }')
    print(f'// {len(sample_bytes_all)} ** {bytes_per_int} = {to_dec_thou_str(num_products_all)}')
    print(f'// math.perm({len(sample_bytes_all)}, {bytes_per_int}) = {to_dec_thou_str(num_permutations_all)}')
    print(f'// {len(sample_bytes_limited)} ** {bytes_per_int} = {to_dec_thou_str(num_products_limited)}')
    print(f'// math.perm({len(sample_bytes_limited)}, {bytes_per_int}) = {to_dec_thou_str(num_permutations_limited)}')

    if num_products_all <= max_iterations_allowed:
        print('// using itertools.product(sample_bytes_all, repeat=bytes_per_int)')
        iterable = itertools.product(sample_bytes_all, repeat=bytes_per_int)
    elif num_permutations_all <= max_iterations_allowed:
        print('// using itertools.permutations(sample_bytes_all, bytes_per_int)')
        iterable = itertools.permutations(sample_bytes_all, bytes_per_int)
    elif num_products_limited <= max_iterations_allowed:
        print('// using itertools.product(sample_bytes_limited, repeat=bytes_per_int)')
        iterable = itertools.product(sample_bytes_limited, repeat=bytes_per_int)
    elif num_permutations_limited <= max_iterations_allowed:
        print('// using itertools.permutations(sample_bytes_limited, bytes_per_int)')
        iterable = itertools.permutations(sample_bytes_limited, bytes_per_int)
    else:
        warnings.warn("Too many iterations")
        print('// using itertools.permutations(sample_bytes_limited, bytes_per_int)')
        iterable = itertools.permutations(sample_bytes_limited, bytes_per_int)

    for tuple_bytes in iterable:
        # The default argument value for byteorder was added in Python 3.11.
        # https://docs.python.org/3/library/stdtypes.html#int.from_bytes
        # TODO: When pypy3 is updated to support 3.11, remove the byteorder argument.
        i = int.from_bytes(tuple_bytes, byteorder='big')
        if i.bit_count() != bits // 2: # redundant check
            continue
        if i % 2 == 0: # even number
            continue
        if i >> (bits - 1) == 0: # MSB is 0
            continue
        s = to_bin_str(i, bits)
        if has_forbidden_substring(s):
            continue
        if has_forbidden_prefix(s):
            continue
        if has_forbidden_suffix(s):
            continue
        bit_patterns[bits].append(i)

    # Ensure correct bit count
    for i in bit_patterns[bits]:
        assert i.bit_count() == bits // 2

    print(f'namespace bit_patterns_{bits} {{') # namespace begin

    print(f'inline constexpr std::array<uint{bits}_t, {to_dec_thou_str_cpp(len(bit_patterns[bits]))}> C {{')
    print('    // {{{')
    for i in bit_patterns[bits]:
        print(f'    {to_hex_str(i, bits)}, // {to_bin_str(i, bits)}')
    print('    // }}}')
    print('};')

    print()

    last_index = len(bit_patterns[bits]) - 1
    max_len = len(to_dec_thou_str(last_index))

    shuffled_indexes = list(range(len(bit_patterns[bits])))
    random.shuffle(shuffled_indexes)

    print('/// shuffled indexes')
    print(f'inline constexpr std::array<unsigned int, {to_dec_thou_str_cpp(len(bit_patterns[bits]))}> shuf_i {{')
    print('    // {{{')
    for i, shuffled_index in enumerate(shuffled_indexes):
        print(f'    {to_dec_thou_str_cpp(shuffled_index, max_len)}, // {to_dec_thou_str_cpp(i, max_len)}')
    print('    // }}}')
    print('};')

    print('}') # namespace end