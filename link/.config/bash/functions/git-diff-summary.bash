# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Example: git-diff-summary v180000.20181004
function git-diff-summary
{

    if (( $# < 1 ))
    then
        printf 'Error: Must give "commit1"\n' 1>&2
        return 1
    fi

    local -r COMMIT1="${1}"

    local -r COMMIT2="${2:-HEAD}"

    printf 'h2. Commit messages for files that changed between %s and %s\n\n' "${COMMIT1}" "${COMMIT2}"

    local FILE
    for FILE in $(git diff --name-only "${COMMIT1}" "${COMMIT2}")
    do
        printf '*%q*\n' "${FILE}"
        if [[ ! -f "${FILE}" ]]
        then
            printf "Error: %q does not exist\n" "${FILE}"
            return 1
        fi
        printf '{noformat}\n'

        #git log --format='%s' ${COMMIT1}.."${COMMIT2}" -- "${FILE}" || return
        git log --decorate --color=never "${COMMIT1}".."${COMMIT2}" -- "${FILE}" | grep '^    ' || return

        printf '{noformat}\n'
        printf '\n'
    done
}

