# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function get
{
    if (( $# == 0 ))
    then
        printf 'Error: Must give at least one folder name\n' 1>&2
        printf 'Usage: %q DIR...\n' "${FUNCNAME[0]}" 1>&2
        return 1
    fi

    local RSYNC_OPTIONS='-v -c -u -p -t -r -z -h'
    #-v, --verbose               increase verbosity
    #-c, --checksum              always checksum
    #-u, --update                update only (don't overwrite newer files)
    #-p, --perms                 preserve permissions
    #-t, --times                 preserve times
    #-n, --dry-run               show what would have been transferred
    #-r, --recursive             recurse into directories
    #-z, --compress              compress file data during the transfer
    #-C, --cvs-exclude           auto ignore files in the same way CVS does
    #-h, --human-readable        output numbers in a human-readable format
    #    --progress              show progress during transfer
    #-i, --itemize-changes       output a change-summary for all updates
    #    --password-file=FILE    read daemon-access password from FILE

    local DIR

    for DIR
    do
        local SRC="$MY_WEBSITE:$DIR/"
        local DST="$HOME/$DIR"
        # shellcheck disable=SC2086
        rsync $RSYNC_OPTIONS -e ssh "$SRC" "$DST"
        echo
    done
}
