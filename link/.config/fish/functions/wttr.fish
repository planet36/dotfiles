# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# https://github.com/chubin/wttr.in/blob/master/share/help.txt
# https://wttr.in/:bash.function
function wttr --argument-names LOC

    set request wttr.in/"$LOC"
    [ $(tput cols) -lt 125 ] && set --append request '?n'
    curl -H "Accept-Language: $(string replace --regex '_.*' '' $LANG)" --compressed "$request"
end
