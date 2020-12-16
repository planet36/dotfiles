
# https://github.com/chubin/wttr.in/blob/master/share/help.txt
# https://wttr.in/:bash.function
function wttr

    set request wttr.in/"$argv[1]"
    [ (tput cols) -lt 125 ] && set --append request '?n'
    curl -H "Accept-Language: (string replace --regex '_.*' '' $LANG)" --compressed "$request"
end

