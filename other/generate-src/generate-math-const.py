# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

"""
Usage:
python3 generate-math-const.py > math-const.hpp
"""

# pylint: disable=invalid-name
# pylint: disable=no-member
# pylint: disable=eval-used
# pylint: disable=bad-indentation
# pylint: disable=fixme
# pylint: disable=invalid-name
# pylint: disable=pointless-string-statement
# pylint: disable=trailing-newlines

import datetime as dt
#import math
import os.path
import platform
import regex

import gmpy2

# https://gmpy2.readthedocs.io/en/latest/mpfr.html

gmpy2.set_context(gmpy2.ieee(256))

atan = gmpy2.atan
atanh = gmpy2.atanh
cbrt = gmpy2.cbrt
gamma = gmpy2.gamma
log = gmpy2.log
log10 = gmpy2.log10
log2 = gmpy2.log2
sqrt = gmpy2.sqrt
zeta = gmpy2.zeta

_1 = gmpy2.mpfr(1)
_2 = gmpy2.mpfr(2)
_3 = gmpy2.mpfr(3)
_4 = gmpy2.mpfr(4)
_5 = gmpy2.mpfr(5)
_6 = gmpy2.mpfr(6)
_7 = gmpy2.mpfr(7)
_8 = gmpy2.mpfr(8)
_9 = gmpy2.mpfr(9)
_10 = gmpy2.mpfr(10)
_11 = gmpy2.mpfr(11)

# https://www.boost.org/doc/libs/1_74_0/libs/math/doc/html/math_toolkit/constants.html

# https://en.wikipedia.org/wiki/List_of_mathematical_constants
# https://en.wikipedia.org/wiki/Mathematical_constant#Basic_mathematical_constants

#pi = gmpy2.const_pi()
# https://oeis.org/A000796/constant
pi = gmpy2.mpfr('3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214')

#e = gmpy2.exp(1)
# https://oeis.org/A001113/constant
e = gmpy2.mpfr('2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746')

# imaginary unit
i = gmpy2.mpc(1j)

# https://en.wikipedia.org/wiki/Mathematical_constant#Constants_in_advanced_mathematics

# Feigenbaum constants
# https://oeis.org/A006890/constant
feigenbaum_1 = gmpy2.mpfr('4.66920160910299067185320382046620161725818557747576863274565134300413433021131473713868974402394801381716')
# https://oeis.org/A006891/constant
feigenbaum_2 = gmpy2.mpfr('2.50290787509589282228390287321821578638127137672714997733619205677923546317959020670329964974643383412959')

# Apéry's constant
#apery = zeta(3)
# https://oeis.org/A002117/constant
apery = gmpy2.mpfr('1.20205690315959428539973816151144999076498629234049888179227155534183820578631309018645587360933525814619915')

# golden ratio
#phi = (1 + sqrt(5)) / 2
phi = gmpy2.mpfr('1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475')

# Euler–Mascheroni constant
# https://oeis.org/A001620/constant
#egamma = gmpy2.const_euler()
egamma = gmpy2.mpfr('.577215664901532860606512090082402431042159335939923598805767234884867726777664670936947063291746749')

# Conway's constant
# https://oeis.org/A014715/constant
conway = gmpy2.mpfr('1.30357726903429639125709911215255189073070250465940487575486139062855088785246155712681576686442522555')

# Khinchin's constant
# https://oeis.org/A002210/constant
khinchin = gmpy2.mpfr('2.68545200106530644530971483548179569382038229399446295305115234555721885953715200280114117493184769799515')

# Glaisher–Kinkelin constant
# https://oeis.org/A074962/constant
glaisher = gmpy2.mpfr('1.28242712910062263687534256886979172776768892732500119206374002174040630885882646112973649195820237439420646120')

# Catalan's constant
# https://oeis.org/A006752/constant
#catalan = gmpy2.const_catalan() # Catalan's constant
catalan = gmpy2.mpfr('.915965594177219015054603514932384110774149374281672134266498119621763019776254769479356512926115106248574')

# universal parabolic constant
# https://en.wikipedia.org/wiki/Universal_parabolic_constant
# https://mathworld.wolfram.com/UniversalParabolicConstant.html
# https://oeis.org/A103710/constant
P = gmpy2.mpfr('2.29558714939263807403429804918949038759783220363858348392997534664410966268413312668409442623789761559175')

math_expr_list = (
	'pi', # math.h (M_PI)
	'pi**2',
	'e', # math.h (M_E)
	'e**2',

	'pi+e',
	'pi-e',
	'pi*e',
	'pi/e',
	'e/pi',
	'pi**pi',
	'pi**e',
	'e**pi',
	'e**e',
	'e**(-pi/2)', # (i**i).real
	'e**pi - pi',
	'e**pi - pi**e',

	'1 / e',
	#'2 / e',
	#'3 / e',
	#'4 / e',
	#'5 / e',
	#'6 / e',
	'1 - 1 / e',

	'pi / 6',
	'pi / 4', # math.h (M_PI_4)
	'pi / 3',
	'pi / 2', # math.h (M_PI_2)
	'2 * pi / 3',
	'5 * pi / 6',
	'7 * pi / 6',
	'4 * pi / 3',
	'3 * pi / 2',
	'5 * pi / 3',
	'11 * pi / 6',
	'2 * pi',
	#'3 * pi',
	#'4 * pi',

	'1 / pi', # math.h (M_1_PI)
	'2 / pi', # math.h (M_2_PI)
	#'3 / pi',
	#'4 / pi',
	'1 / (2 * pi)',
	#'1 / (3 * pi)',
	#'1 / (4 * pi)',

	'sqrt(2)', # math.h (M_SQRT2)
	'sqrt(e)',
	'sqrt(3)',
	'sqrt(pi)',
	'sqrt(5)',
	'sqrt(10)',

	'cbrt(2)',
	'cbrt(e)',
	'cbrt(3)',
	'cbrt(pi)',
	#'cbrt(4)',
	'cbrt(5)',
	'cbrt(10)',

	'1 / sqrt(2)', # math.h (M_SQRT1_2)
	'1 / sqrt(e)',
	'1 / sqrt(3)',
	'1 / sqrt(pi)',
	'1 / sqrt(5)',
	'1 / sqrt(10)',

	'2 / sqrt(pi)', # math.h (M_2_SQRTPI)

	'1 / cbrt(2)',
	'1 / cbrt(e)',
	'1 / cbrt(3)',
	'1 / cbrt(pi)',
	#'1 / cbrt(4)',
	'1 / cbrt(5)',
	'1 / cbrt(10)',

	'log2(e)', # math.h (M_LOG2E)
	'log2(pi)',
	'log2(10)',

	'log(2)', # math.h (M_LN2)
	'log(pi)',
	'log(10)', # math.h (M_LN10)

	'log10(2)',
	'log10(e)', # math.h (M_LOG10E)
	'log10(pi)',

	'1 / log2(e)',
	'1 / log2(pi)',
	'1 / log2(10)',

	'1 / log(2)',
	'1 / log(pi)',
	'1 / log(10)',

	'1 / log10(2)',
	'1 / log10(e)',
	'1 / log10(pi)',

	'gamma(1 / 3)',
	'gamma(2 / 3)',

	'180 / pi',
	'pi / 180',
	#'200 / pi',
	#'pi / 200',

	'_1 / 12',
	'_1 / 9',
	'_1 / 6',
	'_2 / 9',
	'_1 / 3',
	'_5 / 12',
	'_4 / 9',
	'_5 / 9',
	'_7 / 12',
	'_2 / 3',
	'_7 / 9',
	'_5 / 6',
	'_8 / 9',
	'_11 / 12',

	'feigenbaum_1',
	'feigenbaum_2',
	'apery',
	'phi',
	'1 - phi',
	'egamma',
	'conway',
	'khinchin',
	'glaisher',
	'catalan',
	'P',

)

'''
The standard C/C++ math constants are "#define"s, not data constants.
So making data constants in their own namespace with the same name as
the C/C++ defines won't work.  The constants must have different names.
'''

def math_expr_to_c_identifier(s):
	'''Convert a math expression to a valid C/C++ identifier'''

	pattern_replacement_map = (
		(r'\(-', '(negative_'),
		# This is only meant for simple replacement of function calls,
		# not parenthetical groupings.
		#(r'(\w)\s*\(', r'\1_of_'),
		(r'\s*\*{2}\s*2\b', '_squared_'),
		(r'\s*\*{2}\s*3\b', '_cubed_'),
		(r'\s*\*{2}\s*', '_to_the_'),
		#(r'\*', '_times_'),
		(r'\*', '_'),
		(r'\/', '_over_'),
		(r'\+', '_plus_'),
		(r'\-', '_minus_'),
		('[() ]', '_'),
		('_+', '_'),
	)

	for p_r in pattern_replacement_map:
		s = regex.sub(p_r[0], p_r[1], s)

	return 'M_' + s.strip('_')

# TODO: maybe generalize this to support more types
'''
mpz integer
mpq rational => std::ratio
mpfr real
mpc complex => std::complex
'''

'''
def mpfr_to_cpp_literal(x):
	pass
'''

'''
def mpc_to_cpp_literal(x):
	pass
'''

log10_of_2 = gmpy2.log10(2)

binary256_digits10 = int(gmpy2.ceil(log10_of_2 * gmpy2.ieee(256).precision))
# 72
binary192_digits10 = int(gmpy2.ceil(log10_of_2 * gmpy2.ieee(192).precision))
# 53
binary128_digits10 = int(gmpy2.ceil(log10_of_2 * gmpy2.ieee(128).precision))
# 35
binary64_digits10 = int(gmpy2.ceil(log10_of_2 * gmpy2.ieee(64).precision))
# 16

def generate_math_const(x):
	'''Generate a C/C++ declaration of a math constant'''
	name_in_comment = False
	if isinstance(x, dict):
		name_in_comment = True
		name = x['name']
		val = x['val']
		desc = x['desc']
		expr = x['expr']
	elif isinstance(x, str):
		name = math_expr_to_c_identifier(x)
		val = None
		desc = None
		expr = x
		try:
			val = eval(expr)
		except (NameError, SyntaxError):
			print(f'# x={x}')
			print(f'# name={name}')
			print(f'# expr={expr}')
			raise
	else:
		raise Warning('The list must contain dicts or strings')

	#if type(val) is gmpy2.mpc:
	if isinstance(val, gmpy2.mpc().__class__):
		if gmpy2.is_zero(val.imag):
			val = val.real
		else:
			# TODO: add support for complex numbers
			pass

	#val64 = gmpy2.mpfr(val, precision=gmpy2.ieee(64).precision)
	#val128 = gmpy2.mpfr(val, precision=gmpy2.ieee(128).precision)
	#val256 = gmpy2.mpfr(val, binary256_precision)

	try:
		#dec_str = ('{:.' + str(binary192_digits10) + 'NG}').format(val)
		dec_str = f'{val:.{binary192_digits10}NG}'
	except ValueError:
		print(f'# val={val} ({type(val)})')
		print(f'# binary192_digits10={binary192_digits10}')
		print(f'# dec_str={dec_str}')
		print('Error: The value must be a gmpy2 type')
		raise

	hex_str = f'{val:NA}'

	expr_replaced = expr.replace('_', '')
	if name_in_comment:
		print(f'/// {name} = {expr_replaced} = {dec_str}')
	else:
		print(f'/// {expr_replaced} = {dec_str}')
	if desc:
		print(f'/** {desc} */')
	print(f'''template <std::floating_point T>
inline constexpr T {name}{{
    {hex_str}L}};''')

now = dt.datetime.now(dt.timezone.utc)
author = 'Steven Ward'
this_license = 'OSL-3.0'
brief_description = 'math constants'
generated_by_file_name = os.path.basename(__file__)
generated_datetime = now.isoformat(timespec='seconds')
system_info = platform.platform()

print(fr'''// SPDX-FileCopyrightText: {author}
// SPDX-License-Identifier: {this_license}

/// {brief_description}
/**
\file
\author {author}
\sa https://en.wikipedia.org/wiki/List_of_mathematical_constants
\sa https://en.wikipedia.org/wiki/Mathematical_constant#Basic_mathematical_constants
*/

// Generated by "{generated_by_file_name}" on {generated_datetime}
// system information: {system_info}

#pragma once

#include <concepts>''')

for math_expr in math_expr_list:
	print()
	generate_math_const(math_expr)
