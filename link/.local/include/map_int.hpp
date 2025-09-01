// SPDX-FileCopyrightText: Steven Ward
// SPDX-License-Identifier: OSL-3.0

/// Map an unsigned integer to an interval
/**
* \file
* \author Steven Ward
* \sa https://github.com/lemire/fastrange/blob/master/fastrange.h
* \sa https://www.pcg-random.org/posts/bounded-rands.html
* \sa https://arxiv.org/abs/1805.10941
* \sa https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/
* \sa https://stackoverflow.com/a/29811247/1892784
*
* There is a possibility of modulo bias.  See the links above for an explanation.
* The portion of random values which should be discarded is <code>discard / (2**L)</code>.
*
* Where
* <code>discard = 2**L mod s</code> is the number of discarded values in the random pool
* \c L is the bit space of the random pool (typically \c 32 or \c 64)
* \c s is the interval range (<code>b - a + 1</code>)
*
* When <code>2**L mod s</code> is \c 0, there is no modulo bias.
*
* Python script that shows how many discarded values:
*
* Python snippet
* \code{.py}
for L in (3, 4, 5, 8, 16, 32, 64):
    print(f'{L=}')
    for s in range(1, 8+1):
        discard = (2**L) % s
        print(f'  {s=}  {discard=}', end='')
        if discard == 0:
            print("  (No bias)")
            continue
        else:
            discarded_portion = discard / (2**L)
            print(f'  {discarded_portion=}')
    print()
\endcode
*
* Output:
* \verbatim
L=3
  s=1  discard=0  (No bias)
  s=2  discard=0  (No bias)
  s=3  discard=2  discarded_portion=0.25
  s=4  discard=0  (No bias)
  s=5  discard=3  discarded_portion=0.375
  s=6  discard=2  discarded_portion=0.25
  s=7  discard=1  discarded_portion=0.125
  s=8  discard=0  (No bias)

L=4
  s=1  discard=0  (No bias)
  s=2  discard=0  (No bias)
  s=3  discard=1  discarded_portion=0.0625
  s=4  discard=0  (No bias)
  s=5  discard=1  discarded_portion=0.0625
  s=6  discard=4  discarded_portion=0.25
  s=7  discard=2  discarded_portion=0.125
  s=8  discard=0  (No bias)

L=5
  s=1  discard=0  (No bias)
  s=2  discard=0  (No bias)
  s=3  discard=2  discarded_portion=0.0625
  s=4  discard=0  (No bias)
  s=5  discard=2  discarded_portion=0.0625
  s=6  discard=2  discarded_portion=0.0625
  s=7  discard=4  discarded_portion=0.125
  s=8  discard=0  (No bias)

L=8
  s=1  discard=0  (No bias)
  s=2  discard=0  (No bias)
  s=3  discard=1  discarded_portion=0.00390625
  s=4  discard=0  (No bias)
  s=5  discard=1  discarded_portion=0.00390625
  s=6  discard=4  discarded_portion=0.015625
  s=7  discard=4  discarded_portion=0.015625
  s=8  discard=0  (No bias)

L=16
  s=1  discard=0  (No bias)
  s=2  discard=0  (No bias)
  s=3  discard=1  discarded_portion=1.52587890625e-05
  s=4  discard=0  (No bias)
  s=5  discard=1  discarded_portion=1.52587890625e-05
  s=6  discard=4  discarded_portion=6.103515625e-05
  s=7  discard=2  discarded_portion=3.0517578125e-05
  s=8  discard=0  (No bias)

L=32
  s=1  discard=0  (No bias)
  s=2  discard=0  (No bias)
  s=3  discard=1  discarded_portion=2.3283064365386963e-10
  s=4  discard=0  (No bias)
  s=5  discard=1  discarded_portion=2.3283064365386963e-10
  s=6  discard=4  discarded_portion=9.313225746154785e-10
  s=7  discard=4  discarded_portion=9.313225746154785e-10
  s=8  discard=0  (No bias)

L=64
  s=1  discard=0  (No bias)
  s=2  discard=0  (No bias)
  s=3  discard=1  discarded_portion=5.421010862427522e-20
  s=4  discard=0  (No bias)
  s=5  discard=1  discarded_portion=5.421010862427522e-20
  s=6  discard=4  discarded_portion=2.168404344971009e-19
  s=7  discard=2  discarded_portion=1.0842021724855044e-19
  s=8  discard=0  (No bias)
\endverbatim
*
*/

#pragma once

#include "int_bytes.hpp"

#include <concepts>
#include <limits>

/// map \a x to the inverval <code>[0, s)</code>
/**
* \retval x if <code>s == 0</code>
*/
template <std::unsigned_integral T>
constexpr T
map_int(const T x, const T s)
{
    if (s == 0) [[unlikely]]
        // no mapping needed
        return x;

    const auto product = widen(x) * widen(s);
    return static_cast<T>(product >> std::numeric_limits<T>::digits);
}

/// map \a x to the inverval <code>[a, b]</code>
/**
* \pre \a a <= \a b
* \retval x if <code>a == MIN</code> and <code>b == MAX</code>
*/
template <std::unsigned_integral T>
constexpr T
map_int(const T x, const T a, const T b)
{
    /*
    if ((a == std::numeric_limits<T>::min()) && (b == std::numeric_limits<T>::max())) [[unlikely]]
        // no mapping needed
        return x;
    */

    const T s = b - a + 1;
    return map_int(x, s) + a;
}
