# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function untar --wraps tar --description 'untar a file and delete it'

    for INFILE in $argv

        if not test -f "$INFILE"
            echo "Error: No such file: $INFILE" 1>&2
            return 1
        end

        tar --extract --keep-old-files --one-top-level --file "$INFILE" || return

        del -- "$INFILE" || return
    end
end
