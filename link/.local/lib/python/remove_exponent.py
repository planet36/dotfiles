# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

from decimal import Decimal

# copied from
# https://docs.python.org/3/library/decimal.html#decimal-faq
def remove_exponent(d):
	return d.quantize(Decimal(1)) if d == d.to_integral() else d.normalize()
