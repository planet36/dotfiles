
function psgrep --argument-names NAME
    set PROCESSES (pgrep -- "$NAME")

    if test (count $PROCESSES) -eq 0
        return
    end

    ps --sort pid --pid "$PROCESSES"
end

