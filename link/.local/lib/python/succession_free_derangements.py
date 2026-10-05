# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

"""Generate succession-free derangements and matrices built from them.

A succession is a position where the next value is one greater than the current value, as in
``[.., 3, 4, ..]``.  A succession-free derangement has no fixed point and no succession, so it
shares no contiguous run of two or more values with the identity permutation.

For even ``n``, a succession-free derangement matrix is an ``n`` by ``n`` matrix where:

- every row is a permutation of ``0..n-1``,
- row 0 is the identity,
- row ``n-1-k`` is row ``k`` reversed, which this module calls the mirror rule,
- the matrix is symmetric, and
- no ordered pair of adjacent values appears in more than one row.

Symmetry makes every column a permutation, so any two rows are derangements of each other.
Symmetry with the first and last rows also makes row ``k`` start with ``k`` and end with
``n-1-k``.  The last condition keeps every row succession-free with respect to every other row.
The ``n`` rows hold ``n(n-1)`` adjacent pairs, which is exactly the number of ordered pairs of
distinct values, so each such pair appears exactly once.

The mirror rule is part of the intended definition, but it does not follow from the other
rules.  Dropping it allows more matrices from n = 8 on, with 8 instead of 4 for n = 8 and 76
instead of 16 for n = 10.

No such matrix exists for odd ``n``, because the middle row would have to equal its own
reversal.

Run this file, or ``python3 -m succession_free_derangements``, for the command-line interface.
"""

__author__ = 'Steven Ward'
__version__ = '2026-10-02'
__license__ = 'MPL-2.0'

import argparse
import itertools
import math
import re
import sys
from collections.abc import Iterator, Sequence

# Single permutations


def is_derangement(p: Sequence[int], q: Sequence[int] | None = None) -> bool:
    """Return whether ``p`` and ``q`` differ at every position.

    ``q`` defaults to the identity permutation.
    """
    if q is None:
        q = range(len(p))
    return all(a != b for a, b in zip(p, q, strict=True))


def has_succession(p: Sequence[int]) -> bool:
    """Return whether some value in ``p`` is followed by the value one greater."""
    return any(b == a + 1 for a, b in itertools.pairwise(p))


def is_succession_free_derangement(p: Sequence[int]) -> bool:
    """Return whether ``p`` is a derangement of the identity with no succession.

    ``p`` must be a permutation of ``0..len(p)-1``.  Nothing checks this, so a sequence that is
    not one, such as ``[5, 5, 5]``, can return True.
    """
    return is_derangement(p) and not has_succession(p)


def succession_free_derangements(n: int) -> Iterator[tuple[int, ...]]:
    """Yield every succession-free derangement of ``0..n-1`` in lexicographic order."""
    if n < 0:
        raise ValueError(f'n must be nonnegative, not {n}')

    if n == 0:
        yield ()
        return

    perm: list[int] = []
    unused = set(range(n))

    # Each entry holds the untried values for one position, starting with every value but 0 for
    # position 0.  Keeping them on a list instead of the call stack means that n is not bounded
    # by the recursion limit.
    stack = [iter(range(1, n))]
    while stack:
        v = next(stack[-1], None)
        if v is None:
            stack.pop()
            if perm:
                unused.add(perm.pop())
            continue
        perm.append(v)
        if len(perm) == n:
            yield tuple(perm)
            perm.pop()
            continue
        unused.remove(v)
        i = len(perm)
        # pylint: disable-next=consider-using-in
        stack.append(iter([u for u in sorted(unused) if u != i and u != v + 1]))


def circular_distance(p: Sequence[int]) -> int:
    """Return how far the values of ``p`` moved in total, counting around a circle.

    Positions ``0..n-1`` sit on a circle, so the first and last are neighbors.  Each value adds
    the shorter way around from its position to the position it holds in the identity.  ``p``
    must be a permutation of ``0..len(p)-1``.
    """
    n = len(p)
    return sum(min(abs(i - v), n - abs(i - v)) for i, v in enumerate(p))


# Matrices


Matrix = list[list[int]]


def _check_even(n: int) -> None:
    if n < 2 or n % 2:
        raise ValueError(f'n must be an even integer of at least 2, not {n}')


def is_succession_free_matrix(m: Sequence[Sequence[int]]) -> bool:
    """Return whether ``m`` is a succession-free derangement matrix."""
    n = len(m)
    if n < 2 or n % 2 or any(len(row) != n for row in m):
        return False
    identity = list(range(n))
    if list(m[0]) != identity:
        return False
    if any(sorted(row) != identity for row in m):
        return False
    if any(list(m[n - 1 - k]) != list(reversed(m[k])) for k in range(n)):
        return False
    if any(m[i][j] != m[j][i] for i in range(n) for j in range(i)):
        return False
    pairs = [pair for row in m for pair in itertools.pairwise(row)]
    return len(pairs) == len(set(pairs))


def search_matrices(n: int) -> Iterator[Matrix]:
    """Yield every succession-free derangement matrix of order ``n``.

    Matrices come out in lexicographic order of their rows.  The count grows quickly with
    ``n``.  Every matrix for n = 10 takes under a second, and the first one for n = 12 takes
    several seconds.
    """
    _check_even(n)
    half = n // 2
    identity = list(range(n))
    top = [identity]

    # Placing the pair (a, b) in row k also places (b, a) in row n-1-k, its reversal.  So the
    # search tracks unordered pairs across the top half, and each one may appear only once.
    used = {frozenset(pair) for pair in itertools.pairwise(identity)}

    def next_rows(k: int) -> Iterator[list[int]]:
        # Symmetry fixes each entry of row k that faces an earlier row or that row's
        # reversal.  Only the middle positions k..n-1-k are left to choose, and -1 marks them
        # until they are.
        row = [-1] * n
        for j, earlier in enumerate(top):
            row[j] = earlier[k]
            row[n - 1 - j] = earlier[n - 1 - k]
        fixed = [v for v in row if v >= 0]
        if len(set(fixed)) != len(fixed):
            return
        unused = set(identity) - set(fixed)

        def extend(i: int) -> Iterator[list[int]]:
            if i == n:
                yield list(row)
                return
            is_free = k <= i <= n - 1 - k
            for v in (sorted(unused) if is_free else [row[i]]):
                # The row holds each value once, so a pair can only repeat one from another row.
                if i and frozenset((row[i - 1], v)) in used:
                    continue
                if is_free:
                    row[i] = v
                    unused.remove(v)
                yield from extend(i + 1)
                if is_free:
                    unused.add(v)
                    row[i] = -1

        yield from extend(0)

    def add_rows(k: int) -> Iterator[Matrix]:
        if k == half:
            yield [list(row) for row in top] + [list(reversed(row)) for row in reversed(top)]
            return
        for row in next_rows(k):
            pairs = {frozenset(pair) for pair in itertools.pairwise(row)}
            used.update(pairs)
            top.append(row)
            yield from add_rows(k + 1)
            top.pop()
            used.difference_update(pairs)

    yield from add_rows(1)


# Trial division takes about sqrt(n) steps, and the matrix it guards has n*n entries, so it is
# never the slow part.  A library primality test would only add a runtime dependency.
def _is_prime(p: int) -> bool:
    return p >= 2 and all(p % d for d in range(2, math.isqrt(p) + 1))


def modular_matrix(n: int) -> Matrix:
    """Return the succession-free derangement matrix built by multiplication modulo ``n+1``.

    Entry ``(k, i)`` is ``((k+1)(i+1) mod (n+1)) - 1``.  This requires ``n+1`` to be prime.
    Row ``k`` then steps through the nonzero residues by adding ``k+1``, so every row has a
    different step and no two rows share an adjacent pair.
    """
    _check_even(n)
    if not _is_prime(n + 1):
        raise ValueError(f'n+1 must be prime, and {n + 1} is not')
    return [[(k + 1) * (i + 1) % (n + 1) - 1 for i in range(n)] for k in range(n)]


def format_matrix(m: Sequence[Sequence[int]]) -> str:
    """Format ``m`` as one bracketed row per line, the way numpy prints an integer array.

    Every value is right-aligned to the width of the widest one.  Unlike numpy, this never
    wraps a row, so the output differs from numpy's once a row is wider than numpy's
    75-column line width.
    """
    width = max((len(str(v)) for row in m for v in row), default=0)
    lines = ['[' + ' '.join(f'{v:>{width}}' for v in row) + ']' for row in m]
    return '[' + '\n '.join(lines) + ']'


_BRACKETS = str.maketrans('[]', '  ')


def parse_matrices(text: str) -> list[Matrix]:
    """Parse the matrices in ``text``, which are separated by blank lines.

    Each line is read as one row, as ``format_matrix`` writes it.  A row that numpy wrapped onto
    several lines comes back as several rows.
    """
    matrices = []
    for block in re.split(r'\n\s*\n', text.strip()):
        lines = (line.translate(_BRACKETS).split() for line in block.splitlines())
        if rows := [[int(v) for v in line] for line in lines if line]:
            matrices.append(rows)
    return matrices


# Command-line interface


def _nonnegative(s: str) -> int:
    try:
        if (v := int(s)) >= 0:
            return v
    except ValueError:
        pass
    raise argparse.ArgumentTypeError(f'must be a nonnegative integer, not {s!r}')


def main(argv: list[str] | None = None) -> int:
    """Run the command-line interface and return the exit status."""
    parser = argparse.ArgumentParser(
        description='Generate succession-free derangements of 0..N-1.\n'
                    '\n'
                    'commands:\n'
                    '  permutations  print each succession-free derangement on its own line\n'
                    '  matrices      print succession-free derangement matrices, separated by '
                    'blank lines',
        epilog='examples:\n'
               '  %(prog)s permutations 6\n'
               '  %(prog)s matrices 4\n'
               '  %(prog)s matrices 6\n'
               '  %(prog)s matrices 8\n'
               '  %(prog)s matrices 10\n'
               '  %(prog)s matrices 12 --limit 1\n'
               '  %(prog)s matrices 16 --modular',
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        'command', choices=['permutations', 'matrices'], metavar='COMMAND',
        help='"permutations" or "matrices"')
    parser.add_argument(
        'n', type=int, metavar='N',
        help='a nonnegative integer, or for "matrices", an even integer of at least 2')
    parser.add_argument('-l', '--limit', type=_nonnegative, help='stop after this many')
    parser.add_argument(
        '-m', '--modular', action='store_true',
        help='for "matrices", skip the search and print one matrix whose entry (k, i) is '
             '((k+1)(i+1) mod (N+1)) - 1, which requires N+1 to be prime')

    args = parser.parse_args(argv)
    if args.modular and args.command != 'matrices':
        parser.error('--modular applies only to "matrices"')

    try:
        if args.command == 'permutations':
            for p in itertools.islice(succession_free_derangements(args.n), args.limit):
                print(*p)
        elif args.modular:
            print(format_matrix(modular_matrix(args.n)))
        else:
            found = itertools.islice(search_matrices(args.n), args.limit)
            for i, m in enumerate(found):
                if i:
                    print()
                print(format_matrix(m), flush=True)
    except ValueError as e:
        parser.error(str(e))

    return 0


if __name__ == '__main__':
    sys.exit(main())
