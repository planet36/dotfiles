# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# https://github.com/chubin/wttr.in/blob/master/share/help.txt
# https://wttr.in/:bash.function
function wttr
{
    local request="wttr.in/${1}"
    [ "$(tput cols)" -lt 125 ] && request+='?n'
    curl -H "Accept-Language: ${LANG%_*}" --compressed "$request"
}
