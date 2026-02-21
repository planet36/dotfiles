# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name

'''
See also
https://docs.python.org/3/library/configparser.html#configparser.ConfigParser.getboolean
https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Boolean
'''

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'

def as_bool(s: str) -> bool:
    '''Evaluate \a s as a bool.'''

    if s is None:
        return False

    if type(s) is bool: # pylint: disable=unidiomatic-typecheck
        return s

    s = s.strip().lower()

    if s in ("", "0", "no", "n", "false", "off",
             "null", "nil", "none", "nan", "undefined", "-0"):
        return False

    if s in ("1", "yes", "y", "true", "on"):
        return True

    # else: vacuous truth
    return True
