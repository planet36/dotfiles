# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function rtrim --wraps perl --description 'trim trailing whitespace'

    # \s matches newline
    #perl -p -i~ -e 's/\s+$//' -- $argv
    perl -p -i~ -e 's/[ \t]+$//' -- $argv
end
