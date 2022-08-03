# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=C0103
# pylint: disable=C0114
# pylint: disable=C0116
# pylint: disable=C0301
# pylint: disable=R1705
# pylint: disable=W0311

import re
import string
import sys

__author__ = 'Steven Ward'
__version__ = '2016-06-12'


r"""
From the C++ standard:

2.13.3 Character literals

simple-escape-sequence: one of
	\' \" \? \\
	\a \b \f \n \r \t \v
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
		return r'\{:03o}'.format(ord(c))


def escape_char_to_hexadecimal(c):
	"""Escape the character to a simple-escape-sequence or a hexadecimal-escape-sequence."""

	if c in simple_esc_seq:
		return simple_esc_seq[c]
	else:
		return r'\x{:02X}'.format(ord(c))


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

	if pattern.search(s):
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
Escape non-printable characters, double quotes, backslashes, and trigraphs, and surround the result with double quotes."""

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
Escape non-printable characters, double quotes, backslashes, and trigraphs, and surround the result with double quotes.  \
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



# pylint: disable=R0912
# pylint: disable=R0915
def main(argv = None):

	# pylint: disable=C0415
	# pylint: disable=R0914
	import getopt
	import os.path
	import signal


	if argv is None:
		argv = sys.argv


	program_name = os.path.basename(argv[0])

	program_authors = [__author__]


	# valid values
	valid_quoting_styles = sorted(quoting_style_to_function_map.keys())

	# default values
	default_quoting_style = 'literal'
	default_delimiter = os.linesep

	# mutable values
	quoting_style = default_quoting_style
	delimiter = default_delimiter


	# pylint: disable=W0613
	def signal_handler(signal_num, execution_frame):
		print()
		sys.exit(0)

	signal.signal(signal.SIGINT, signal_handler) # Interactive attention signal. (Ctrl-C)
	signal.signal(signal.SIGTERM, signal_handler) # Termination request. (kill default signal)


	def print_version():
		"""Print version information"""
		print("{} {}".format(program_name, __version__))
		print("Written by {}".format(', '.join(program_authors)))


	# pylint: disable=W0612
	def print_warning(s):
		"""Print the warning message"""
		print("Warning: {}".format(s), file=sys.stderr)


	def print_error(s):
		"""Print the error message"""
		print("Error: {}".format(s), file=sys.stderr)
		print("Try '{} --help' for more information.".format(program_name), file=sys.stderr)


	def print_help():
		"""Print the help message"""

		print("""Usage: {} [OPTIONS] [FILE...]
Quote the lines of FILE according to a quoting style.

If FILE is absent, or if FILE is '-', read standard input.

OPTIONS

-V, --version
    Print the version information, then exit.

-h, --help
    Print this message, then exit.

-q, --quoting-style=STYLE
    Use quoting style STYLE to quote lines. See below for descriptions of all quoting styles.
    (default: {})
    (valid: {})

-0, --null
    Use NULL as the line delimiter instead of NEWLINE.
""".format(
			program_name,
			default_quoting_style,
			','.join(valid_quoting_styles),
			))

		print("QUOTING STYLES")
		print()
		for key in sorted(quoting_style_to_function_map):
			value = quoting_style_to_function_map[key]
			#print("'{}' : {}".format(key, value.__doc__))
			print("    {} : {}".format(key, value.__doc__))
			print()


	short_options = 'Vhq:0'
	long_options = ['version', 'help', 'quoting-style=', 'null']

	try:
		(options, remaining_args) = getopt.getopt(argv[1:], short_options, long_options)
	except getopt.GetoptError as err:
		print_error(err)
		return 1

	for (option, value) in options:
		if option in ['-V', '--version']:
			print_version()
			return 0
		elif option in ['-h', '--help']:
			print_help()
			return 0
		elif option in ['-q', '--quoting-style']:
			quoting_style = value
		elif option in ['-0', '--null']:
			delimiter = '\0'
		else:
			print_error(f"Unhandled option: {option}")
			return 1

	# Validate quoting_style.

	if quoting_style not in valid_quoting_styles:
		print_error("{} is not a valid quoting style.".format(quoting_style))
		return 1


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


	# No file was given.
	if not remaining_args: # empty
		remaining_args.append('-')

	for file_name in remaining_args:

		try:

			if file_name == '-':

				# Read standard input.

				if delimiter == os.linesep:
					quote_lines(sys.stdin)
				else:
					quote_file_data(sys.stdin.read())

			else:

				# Read the file.

				with open(file_name, 'r') as f:

					if delimiter == os.linesep:
						quote_lines(f)
					else:
						quote_file_data(f.read())

		except (OSError, UnicodeDecodeError) as err:
			print_error(err)
			return 1



if __name__ == '__main__':
	sys.exit(main())
