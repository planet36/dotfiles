# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function get

    if test $(count $argv) -eq 0
        echo 'Error: Must give at least one folder name' 1>&2
        echo 'Usage: '$(status function)' DIR...' 1>&2
        return 1
    end

    # --verbose, -v            increase verbosity
    # --checksum, -c           skip based on checksum, not mod-time & size
    # --recursive, -r          recurse into directories
    # --update, -u             skip files that are newer on the receiver
    # --perms, -p              preserve permissions
    # --times, -t              preserve modification times
    # --dry-run, -n            perform a trial run with no changes made
    # --compress, -z           compress file data during the transfer
    # --cvs-exclude, -C        auto-ignore files in the same way CVS does
    # --human-readable, -h     output numbers in a human-readable format
    # --progress               show progress during transfer
    # --itemize-changes, -i    output a change-summary for all updates
    # --password-file=FILE     read daemon-access password from FILE
    set RSYNC_OPTIONS -v -c -u -p -t -r -z -h

    for DIR in $argv
        set SRC "$MY_WEBSITE:$DIR/"
        set DST "$HOME/$DIR"
        rsync $RSYNC_OPTIONS -e ssh "$SRC" "$DST"
        echo
    end
end
