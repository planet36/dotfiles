# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function gbc --description 'git bundle create'

    set DST $argv[1]

    set BUNDLE_FILE $(basename $(git rev-parse --show-toplevel)) || return

    # XXX: string replace returns 1 (failure) if no replacement was performed
    set BUNDLE_FILE $(string replace --regex --all '\W' '' $BUNDLE_FILE).bundle

    git bundle create --progress "$BUNDLE_FILE" HEAD@{upstream}..HEAD --branches --tags

    if test -d "$DST"
        mv --verbose -- "$BUNDLE_FILE" "$DST"
    end
end
