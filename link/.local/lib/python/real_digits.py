# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

'''
This module defines a function similar to the Wolfram Mathematica function RealDigits.
https://reference.wolfram.com/language/ref/RealDigits.html
'''

import decimal

D = decimal.Decimal

def real_digits(x: D, *, base: D=D(10), limit: int=100, context=None) -> tuple:
    '''Get 2 lists of the digits of the integral and the fractional parts of the number.'''

    with decimal.localcontext(context) as _:

        x = D(x)
        base = D(base)
        limit = int(limit)

        assert base > 1

        x = abs(x)

        (i_part, f_part) = divmod(x, 1) # split

        i_digits = []
        while True:
            (i_part, digit) = divmod(i_part, base)
            i_digits.insert(0, int(digit)) # insert at front

            if i_part.is_zero():
                break

        f_digits = []
        while limit > 0:
            f_part *= base
            (digit, f_part) = divmod(f_part, 1) # split
            f_digits.append(int(digit))

            if f_part.is_zero():
                break

            limit -= 1

        return (i_digits, f_digits)
