# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function ut --wraps tar --description 'untar a file and delete it'

    for INFILE in $argv

        if not test -f "$INFILE"
            echo "Error: No such file: $INFILE" 1>&2
            return 1
        end

        tar --extract --keep-old-files --one-top-level --file "$INFILE" || return

        del -- "$INFILE" || return
    end
end
