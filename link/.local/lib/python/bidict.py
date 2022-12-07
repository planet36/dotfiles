# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=invalid-name

'''
Bidirectional dictionary
Adapted from <https://stackoverflow.com/a/21894086>.
'''

__author__ = 'Steven Ward'
__license__ = 'OSL-3.0'

# pylint: disable=missing-class-docstring
class bidict(dict):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.inverse = {}
        for key, value in self.items():
            self.inverse.setdefault(value, set()).add(key)

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
