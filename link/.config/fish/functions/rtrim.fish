# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function rtrim --description 'trim trailing whitespace'

    # \s matches newline
    #perl -p -i~ -e 's/\s+$//' -- $argv
    perl -p -i~ -e 's/[ \t]+$//' -- $argv
end
