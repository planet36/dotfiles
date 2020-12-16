# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function split_seconds --argument-names seconds --description 'split the given number of seconds into time elements'

    set print_zero_seconds 0

    set seconds (math --scale=max -- "abs($seconds)") || return

    # seconds/day == 60 * 60 * 24 == 86400
    # seconds/hour == 60 * 60 == 3600
    # seconds/minute == 60

    set days    (math --scale=0   -- "$seconds / 86400") || return
    set seconds (math --scale=max -- "$seconds % 86400") || return

    set hours   (math --scale=0   -- "$seconds / 3600") || return
    set seconds (math --scale=max -- "$seconds % 3600") || return

    set minutes (math --scale=0 -- "$seconds / 60") || return
    set seconds (math --scale=2 -- "$seconds % 60") || return

    set result

    if test "$days" -ne 0
        set --append result "$days"d || return
    end

    if test "$hours" -ne 0
        set --append result "$hours"h || return
    end

    if test "$minutes" -ne 0
        set --append result "$minutes"m || return
    end

    if test "$seconds" -ne 0 -o \( $print_zero_seconds -ne 0 -a (count $result) -eq 0 \)
        set --append result "$seconds"s || return
    end

    echo -n $result
end
