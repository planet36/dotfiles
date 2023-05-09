# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# XXX: can be replaced with dateseq
# <https://www.fresse.org/dateutils/>

function date_range
{
    local D1
    local D2

    D1=$(date --date="${1}" +'%F') || return
    D2=$(date --date="${2}" +'%F') || return

    local -a SORTED_DATES

    readarray -t SORTED_DATES < <(printf '%q\n%q\n' "${D1}" "${D2}" | sort)

    D1="${SORTED_DATES[0]}"
    D2="${SORTED_DATES[1]}"

    while true
    do
        printf '%q\n' "${D1}"

        [[ "${D1}" == "${D2}" ]] && break

        D1=$(date --date="${D1} +1 day" +'%F')
    done
}
