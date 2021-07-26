# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function put

    if test (count $argv) -eq 0
        echo 'Error: Must give at least one folder name' 1>&2
        echo 'Usage: '(status function)' DIR...' 1>&2
        return 1
    end

    set RSYNC_OPTIONS -v -c -u -p -t -r -z -h
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

    for DIR in $argv
        set SRC "$HOME/$DIR/"
        set DST "$MY_WEBSITE:$DIR"
        rsync $RSYNC_OPTIONS -e ssh "$SRC" "$DST"
        echo
    end
end
