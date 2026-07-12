# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name
# pylint: disable=line-too-long
# pylint: disable=missing-function-docstring
# pylint: disable=no-else-return
# pylint: disable=pointless-string-statement

'''
Quote and escape strings for various styles (shell, C string literal, CSV, PCRE, octal/hex escapes).
'''

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'
__version__ = '2026-07-12'

import argparse
import os
import re
import signal
import string
import sys

r"""
From the C++ standard:

2.13.3 Character literals

simple-escape-sequence: one of
    \' \" \? \\
    \a \b \f \n \r \t \v

https://en.cppreference.com/w/c/language/escape
https://en.cppreference.com/w/cpp/language/escape
https://eel.is/c++draft/lex.ccon#:simple-escape-sequence-char
"""
simple_esc_seq = {
    '\a': r'\a', # alert
    '\b': r'\b', # backspace
    '\t': r'\t', # horizontal tab
    '\n': r'\n', # new line
    '\v': r'\v', # vertical tab
    '\f': r'\f', # form feed
    '\r': r'\r', # carriage return
    '\"': r'\"', # double quote
    '\'': r'\'', # single quote
    '?' : r'\?', # question mark
    '\\': r'\\', # backslash
}

def escape_char_to_octal(c):
    """Escape the character to a simple-escape-sequence or an octal-escape-sequence."""

    if c in simple_esc_seq:
        return simple_esc_seq[c]
    else:
        return fr'\{ord(c):03o}'

def escape_char_to_hexadecimal(c):
    """Escape the character to a simple-escape-sequence or a hexadecimal-escape-sequence."""

    if c in simple_esc_seq:
        return simple_esc_seq[c]
    else:
        return fr'\x{ord(c):02X}'

def escape_non_printable_char_to_octal(c):
    """Escape the non-printable character to octal digits.  \
If the character is printable, it is not escaped."""

    if c.isprintable():
        return c
    else:
        return escape_char_to_octal(c)

def escape_non_printable_char_to_hexadecimal(c):
    """Escape the non-printable character to hexadecimal digits.  \
If the character is printable, it is not escaped."""

    if c.isprintable():
        return c
    else:
        return escape_char_to_hexadecimal(c)

def literal(s):
    """Do not quote the string."""

    return s

def shell_always(s):
    """Quote the string (in all cases) for a shell.  \
Escape single quotes, and surround the result with single quotes."""

    pattern = "'"
    replacement = r"'\''"

    return "'" + s.replace(pattern, replacement) + "'"

def shell(s):
    """Quote the string (in some cases) for a shell.  \
If the string contains special characters specified by the POSIX standard, then quote the string for a shell.  \
<https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_02>"""

    pattern = re.compile(r'''[\t\n "#$%&'()*;<=>?[\\`|~]''')

    if not s or pattern.search(s):
        return shell_always(s)
    else:
        return s

def escape(s):
    """Escape non-printable characters, spaces, and backslashes."""

    # Escape spaces and backslashes.
    pattern = re.compile(r'([ \\])')
    replacement = r'\\\1'

    s = pattern.sub(replacement, s)

    # Escape non-printable characters.
    pattern2 = re.compile('([^\x20-\x7E])')

    def replacement2(match_object):
        '''Replacement function'''
        return escape_char_to_octal(match_object.group(1))

    s = pattern2.sub(replacement2, s)

    return s

def cstr(s):
    """Quote the string for a C string literal.  \
Escape non-printable characters, double quotes, and backslashes, and surround the result with double quotes."""

    # Escape double quotes and backslashes.
    pattern = re.compile(r'(["\\])')
    replacement = r'\\\1'

    s = pattern.sub(replacement, s)

    # Escape non-printable characters.
    pattern2 = re.compile('([^\x20-\x7E])')

    def replacement2(match_object):
        '''Replacement function'''
        return escape_char_to_octal(match_object.group(1))

    s = pattern2.sub(replacement2, s)

    # Surround the result with double quotes.
    return '"' + s + '"'

def cstr_maybe(s):
    """Quote the string (in some cases) for a C string literal.  \
Escape non-printable characters, double quotes, and backslashes, and surround the result with double quotes.  \
If no characters were escaped, the original string is returned."""

    # Look for double quotes and backslashes.
    pattern = re.compile(r'["\\]')

    # Look for non-printable characters.
    pattern2 = re.compile('[^\x20-\x7E]')

    if pattern.search(s) or pattern2.search(s):
        return cstr(s)
    else:
        return s

def pcre(s):
    """Escape non-alphanumeric characters and non-underscore characters for a Perl Compatible Regular Expression (PCRE)."""

    pattern = re.compile('([^A-Za-z0-9_])')
    replacement = r'\\\1'

    return pattern.sub(replacement, s)

def csv(s, field_separator = ',', record_separator = '\n'):
    """Quote the string (in some cases) for a CSV field.  \
If the string contains a double quote, then escape double quotes, and surround the result with double quotes.  \
If the string contains a field separator, contains a record separator, begins with whitespace, or ends with whitespace, then surround the result with double quotes."""

    if '"' in s:
        # Replace double quotes with 2 double quotes.
        # Surround the result with double quotes.
        return '"' + s.replace('"', '""') + '"'

    if (field_separator in s) or (record_separator in s) or ((len(s) > 0) and ((s[0] in string.whitespace) or (s[-1] in string.whitespace))):
        # Surround the result with double quotes.
        return '"' + s + '"'

    return s

quoting_style_to_function_map = {
    'literal'      : literal     ,
    'shell-always' : shell_always,
    'shell'        : shell       ,
    'escape'       : escape      ,
    'cstr'         : cstr        ,
    'cstr-maybe'   : cstr_maybe  ,
    'pcre'         : pcre        ,
    'csv'          : csv         ,
}

def quote(s, quoting_style):
    '''Quote the string with the quoting style.'''

    if quoting_style in quoting_style_to_function_map:
        return quoting_style_to_function_map[quoting_style](s)
    else:
        return s

# pylint: disable=too-many-locals
def main(argv: list[str] | None = None) -> int | None:

    # Restore default SIGPIPE handling so broken pipes terminate silently.
    # Done here rather than at module level to avoid side effects on import.
    signal.signal(signal.SIGPIPE, signal.SIG_DFL)

    # valid values
    valid_quoting_styles = sorted(quoting_style_to_function_map.keys())

    # default values
    default_quoting_style = 'literal'
    default_delimiter = os.linesep

    description_lines = (
            'Quote the lines of FILE according to a quoting style.',
            '',
            "If FILE is absent, or if FILE is '-', read standard input.",
            )

    epilog_lines = ['quoting styles:', '']
    for key in valid_quoting_styles:
        epilog_lines.append(f'  {key}')
        epilog_lines.append(f'    {quoting_style_to_function_map[key].__doc__}')
        epilog_lines.append('')

    version_lines = (f'%(prog)s {__version__}',
                    f'License: {__license__}',
                    f'Written by {__author__}')

    parser = argparse.ArgumentParser(
            description='\n'.join(description_lines),
            epilog='\n'.join(epilog_lines),
            formatter_class=argparse.RawTextHelpFormatter)

    parser.add_argument('-V', '--version', action='version', version='\n'.join(version_lines))

    parser.add_argument('-q', '--quoting-style', choices=valid_quoting_styles,
            default=default_quoting_style, metavar='STYLE',
            help='quoting style used to quote lines (default: %(default)s)\n'
                 'see below for descriptions of all quoting styles')

    parser.add_argument('-0', '--null', dest='delimiter', action='store_const',
            const='\0', default=default_delimiter,
            help='use NUL as the line delimiter instead of NEWLINE')

    parser.add_argument('FILE', nargs='*', default=['-'],
            help="the file(s) whose lines to quote (default: standard input)")

    args = parser.parse_args(argv)

    quoting_style = args.quoting_style
    delimiter = args.delimiter

    def print_error(s):
        """Print the error message"""
        print(f"Error: {s}", file=sys.stderr)

    def quote_lines(lines):

        quote_function = quoting_style_to_function_map[quoting_style]

        for line in lines:
            print(quote_function(line.rstrip(delimiter)), end=delimiter)

    def quote_file_data(file_data):

        lines = file_data.split(delimiter)

        # If the last line ended with the delimiter,
        if not lines[-1]: # empty
            del lines[-1]

        quote_lines(lines)

    for file_name in args.FILE:

        try:
            if file_name == '-':
                # Read standard input.

                if delimiter == os.linesep:
                    quote_lines(sys.stdin)
                else:
                    quote_file_data(sys.stdin.read())

            else:
                # Read the file.

                with open(file_name, mode='r', encoding='utf-8') as f:

                    if delimiter == os.linesep:
                        quote_lines(f)
                    else:
                        quote_file_data(f.read())

        except (OSError, UnicodeDecodeError) as err:
            print_error(err)
            return 1

    return 0

if __name__ == '__main__':
    sys.exit(main())
