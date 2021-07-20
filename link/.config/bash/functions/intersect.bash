# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function intersect
{
    if (( $# != 2 ))
    then
        printf 'Error: Must give 2 paths\n' 1>&2
        printf 'Usage: %q FILE1 FILE2\n' "${FUNCNAME[0]}" 1>&2
        printf 'Print the intersection of FILE1 and FILE2.\n' 1>&2
        return 1
    fi

    local FILE1="${1}"
    local FILE2="${2}"

    if [[ ! -f "${FILE1}" ]]
    then
        printf 'Error: %q is not a file.\n' "${FILE1}" 1>&2
        return 1
    fi

    if [[ ! -f "${FILE2}" ]]
    then
        printf 'Error: %q is not a file.\n' "${FILE2}" 1>&2
        return 1
    fi

    sort <(sort --uniq -- "${FILE1}") <(sort --uniq -- "${FILE2}") | uniq --repeated
}
