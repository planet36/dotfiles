# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name
# pylint: disable=line-too-long

'''
See also:
https://stackoverflow.com/questions/2158395/flatten-an-irregular-arbitrarily-nested-list-of-lists/2158532#2158532
https://stackoverflow.com/questions/10823877/what-is-the-fastest-way-to-flatten-arbitrarily-nested-lists-in-python/10824420#10824420
https://stackoverflow.com/questions/952914/how-do-i-make-a-flat-list-out-of-a-list-of-lists/40857703#40857703
'''
def flatten(iterable):
    '''Flatten the iterable'''
    if isinstance(iterable, dict):
        yield from flatten(iterable.values())
    else:
        for x in iterable:
            if isinstance(x, (list, tuple, range, set, frozenset, dict)):
                yield from flatten(x)
            else:
                yield x
