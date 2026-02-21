# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function cdd --argument-names path --wraps dirname --description 'If $path is not a directory, assign it the dirname of $path.  Then cd to $path'

    if ! test -d "$path"
        set path $(dirname $path)
    end

    cd $path
end
