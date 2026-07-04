# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# pylint: disable=invalid-name

'''
Bidirectional dictionary
Adapted from <https://stackoverflow.com/a/21894086>.
'''

__author__ = 'Steven Ward'
__license__ = 'MPL-2.0'

from collections import UserDict

# pylint: disable=missing-class-docstring
class bidict(UserDict):

    def __init__(self, *args, **kwargs):
        self.inverse = {}
        super().__init__(*args, **kwargs)

    def __setitem__(self, key, value):
        if key in self and self[key] in self.inverse:
            self.inverse[self[key]].remove(key)
            # If the last value was removed
            if not self.inverse[self[key]]: # empty
                del self.inverse[self[key]]
        super().__setitem__(key, value)
        self.inverse.setdefault(value, set()).add(key)

    def __delitem__(self, key):
        if key in self and self[key] in self.inverse:
            self.inverse[self[key]].remove(key)
            # If the last value was removed
            if not self.inverse[self[key]]: # empty
                del self.inverse[self[key]]
        super().__delitem__(key)

    def __ior__(self, other): # type: ignore[misc]
        # UserDict.__ior__ mutates self.data directly, bypassing __setitem__.
        self.update(other)
        return self
