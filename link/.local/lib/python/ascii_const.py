# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=line-too-long
# pylint: disable=bad-indentation
# pylint: disable=fixme
# pylint: disable=invalid-name
# pylint: disable=pointless-string-statement
# pylint: disable=trailing-newlines

"""
This module defines the following strings for ASCII POSIX character classes.
* all
* uppercase (upper)
* lowercase (lower)
* alphabetical (alpha)
* decimal (digit)
* alphanumeric (alnum)
* word
* hexadecimal (xdigit)
* octal
* binary
* whitespace (space)
* blank (blank)
* visible (graph)
* printable (print)
* control (cntrl)
* punctuation (punct)

https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap07.html#tag_07_03_01
"""

__author__ = 'Steven Ward'
__version__ = '2022-11-07'
__license__ = 'OSL-3.0'

set_ascii_all          = frozenset(range(128))
set_ascii_uppercase    = frozenset(range(ord('A'), ord('Z') + 1))
set_ascii_lowercase    = frozenset(range(ord('a'), ord('z') + 1))
set_ascii_alphabetical = set_ascii_uppercase | set_ascii_lowercase
set_ascii_decimal      = frozenset(range(ord('0'), ord('9') + 1))
set_ascii_alphanumeric = set_ascii_alphabetical | set_ascii_decimal
set_ascii_word         = set_ascii_alphanumeric | frozenset(b'_')
set_ascii_hexadecimal  = set_ascii_decimal | frozenset(range(ord('A'), ord('F') + 1)) | frozenset(range(ord('a'), ord('f') + 1))
set_ascii_octal        = frozenset(range(ord('0'), ord('7') + 1))
set_ascii_binary       = frozenset(b'01')
set_ascii_whitespace   = frozenset(b'\t\n\v\f\r ')
set_ascii_blank        = frozenset(b'\t ')
set_ascii_visible      = frozenset(range(ord('!'), ord('~') + 1))
set_ascii_printable    = frozenset(b' ') | set_ascii_visible
set_ascii_control      = set_ascii_all - set_ascii_printable
set_ascii_punctuation  = set_ascii_visible - set_ascii_alphanumeric

assert len(set_ascii_all         ) == 128
assert len(set_ascii_uppercase   ) ==  26
assert len(set_ascii_lowercase   ) ==  26
assert len(set_ascii_alphabetical) ==  52
assert len(set_ascii_decimal     ) ==  10
assert len(set_ascii_alphanumeric) ==  62
assert len(set_ascii_word        ) ==  63
assert len(set_ascii_hexadecimal ) ==  22
assert len(set_ascii_octal       ) ==   8
assert len(set_ascii_binary      ) ==   2
assert len(set_ascii_whitespace  ) ==   6
assert len(set_ascii_blank       ) ==   2
assert len(set_ascii_visible     ) ==  94
assert len(set_ascii_printable   ) ==  95
assert len(set_ascii_control     ) ==  33
assert len(set_ascii_punctuation ) ==  32

ascii_all          = bytes(sorted(set_ascii_all         )).decode()
ascii_uppercase    = bytes(sorted(set_ascii_uppercase   )).decode()
ascii_lowercase    = bytes(sorted(set_ascii_lowercase   )).decode()
ascii_alphabetical = bytes(sorted(set_ascii_alphabetical)).decode()
ascii_decimal      = bytes(sorted(set_ascii_decimal     )).decode()
ascii_alphanumeric = bytes(sorted(set_ascii_alphanumeric)).decode()
ascii_word         = bytes(sorted(set_ascii_word        )).decode()
ascii_hexadecimal  = bytes(sorted(set_ascii_hexadecimal )).decode()
ascii_octal        = bytes(sorted(set_ascii_octal       )).decode()
ascii_binary       = bytes(sorted(set_ascii_binary      )).decode()
ascii_whitespace   = bytes(sorted(set_ascii_whitespace  )).decode()
ascii_blank        = bytes(sorted(set_ascii_blank       )).decode()
ascii_visible      = bytes(sorted(set_ascii_visible     )).decode()
ascii_printable    = bytes(sorted(set_ascii_printable   )).decode()
ascii_control      = bytes(sorted(set_ascii_control     )).decode()
ascii_punctuation  = bytes(sorted(set_ascii_punctuation )).decode()

ascii_not_uppercase    = bytes(sorted(set_ascii_all - set_ascii_uppercase   )).decode()
ascii_not_lowercase    = bytes(sorted(set_ascii_all - set_ascii_lowercase   )).decode()
ascii_not_alphabetical = bytes(sorted(set_ascii_all - set_ascii_alphabetical)).decode()
ascii_not_decimal      = bytes(sorted(set_ascii_all - set_ascii_decimal     )).decode()
ascii_not_alphanumeric = bytes(sorted(set_ascii_all - set_ascii_alphanumeric)).decode()
ascii_not_word         = bytes(sorted(set_ascii_all - set_ascii_word        )).decode()
ascii_not_hexadecimal  = bytes(sorted(set_ascii_all - set_ascii_hexadecimal )).decode()
ascii_not_octal        = bytes(sorted(set_ascii_all - set_ascii_octal       )).decode()
ascii_not_binary       = bytes(sorted(set_ascii_all - set_ascii_binary      )).decode()
ascii_not_whitespace   = bytes(sorted(set_ascii_all - set_ascii_whitespace  )).decode()
ascii_not_blank        = bytes(sorted(set_ascii_all - set_ascii_blank       )).decode()
ascii_not_visible      = bytes(sorted(set_ascii_all - set_ascii_visible     )).decode()
ascii_not_printable    = bytes(sorted(set_ascii_all - set_ascii_printable   )).decode()
ascii_not_control      = bytes(sorted(set_ascii_all - set_ascii_control     )).decode()
ascii_not_punctuation  = bytes(sorted(set_ascii_all - set_ascii_punctuation )).decode()

del set_ascii_all
del set_ascii_uppercase
del set_ascii_lowercase
del set_ascii_alphabetical
del set_ascii_decimal
del set_ascii_alphanumeric
del set_ascii_word
del set_ascii_hexadecimal
del set_ascii_octal
del set_ascii_binary
del set_ascii_whitespace
del set_ascii_blank
del set_ascii_visible
del set_ascii_printable
del set_ascii_control
del set_ascii_punctuation
