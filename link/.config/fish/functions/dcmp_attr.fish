
function dcmp_attr --description 'meld compare file attributes of 2 directories' --argument-names A B

    if test (count $argv) -ne 2
        echo 'Usage: '(status function)' DIR1 DIR2' 1>&2
        echo 'meld compare file attributes of DIR1 and DIR2.' 1>&2
        return 1
    end

    if not test -d "$A"
        echo "Error: No such directory: $A" 1>&2
        return 1
    end

    if not test -d "$B"
        echo "Error: No such directory: $B" 1>&2
        return 1
    end

    set FIND_PRINTF_FMT '%P\t%s\t%u\t%g\t%M\n'

    meld (find "$A" -type f -printf "$FIND_PRINTF_FMT" | sort | psub) (find "$B" -type f -printf "$FIND_PRINTF_FMT" | sort | psub)
end

