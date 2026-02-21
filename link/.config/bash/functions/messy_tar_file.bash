# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# Determine if the tar file would create files outside of a root folder without the basename of itself.
function messy_tar_file
{
    if (( $# != 1 ))
    then
        printf 'Error: Must give 1 file.\n' 1>&2
        return 1
    fi

    local FILE="${1}"
    local BASENAME

    BASENAME=$(basename -- "${FILE}" | cut --delimiter='.' --fields=1) || return

    tar --list --file "${FILE}" | awk --assign basename="${BASENAME}" 'NR==1 {
    # Store the first record.
    first_rec=$0

    # The base name of the file (without extension) must equal the first record.
    if (first_rec != basename "/") {
        exit 1
    }

    # It must not begin with "/".  In this case, the tar file was created with the --absolute-names (-P) option.
    # It must not have intermediate directories.
    # It must end with "/".

    if (first_rec !~ /^[^\/]+\/$/) {
        exit 1
    }
}

# Every record must begin with the first record.
match($0, first_rec) != 1 {
    exit 1
}'

}
