# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function gbc --argument-names DST --description 'git bundle create'

    set BUNDLE_FILE $(basename $(git rev-parse --show-toplevel)) || return

    # XXX: string replace returns 1 (failure) if no replacement was performed
    set BUNDLE_FILE $(string replace --regex --all '\W' '' $BUNDLE_FILE).bundle

    git bundle create --progress "$BUNDLE_FILE" HEAD@{upstream}..HEAD --branches --tags || return

    if test -d "$DST"
        mv --verbose -- "$BUNDLE_FILE" "$DST"
    end
end
