# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function psgrep
{
    if [[ -z "${1}" ]]
    then
        return 1
    fi

    local -a PROCESSES
    readarray -t PROCESSES < <(pgrep -- "${1}")

    ((${#PROCESSES[@]} == 0)) && return

    ps --sort pid --pid "${PROCESSES[@]}"
}
