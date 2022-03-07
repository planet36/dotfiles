# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# XXX: can be replaced with datediff
# <https://www.fresse.org/dateutils/>

# days between dates
function dbd
{
    local D1
    local D2

    if (( $# == 1 ))
    then
        D1=$(date               +'%F') || return
        D2=$(date --date="${1}" +'%F') || return
    elif (( $# == 2 ))
    then
        D1=$(date --date="${1}" +'%F') || return
        D2=$(date --date="${2}" +'%F') || return
    else
        printf 'Error: Must give 1 or 2 dates\n' 1>&2
        printf 'Usage: %q DATE1 [DATE2]\n' "${FUNCNAME[0]}" 1>&2
        printf 'If 1 date is given, the other defaults to today.\n' 1>&2
        return 1
    fi

    D1=$(date --date="${D1}" +'%s') || return
    D2=$(date --date="${D2}" +'%s') || return

    local -r SECONDS_PER_DAY=86400

    echo $(( (D2 - D1) / SECONDS_PER_DAY ))

    local SECONDS_PER_HALF_DAY=$((SECONDS_PER_DAY/2))

    if ((D1 > D2))
    then
        SECONDS_PER_HALF_DAY=$((-HALF_DAY))
    fi

    echo $(( ((D2 - D1) + SECONDS_PER_HALF_DAY) / SECONDS_PER_DAY ))
}
