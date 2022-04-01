# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function cproto --wraps ctags --description 'Generate function prototypes for the given C file(s)'

    if test $(count $argv) -eq 0
        return 1
    end

    ctags --output-format=json --totals=no --extras=-F --fields=nP $argv | jq -sr 'sort_by(.line) | .[].pattern | ltrimstr("/^") | rtrimstr("$/") | . + ";"'
end
