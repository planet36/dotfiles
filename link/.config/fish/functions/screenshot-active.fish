# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function screenshot-active --description 'Take a screenshot of the active window'

    set --local DATETIME $(date -u +%Y%m%dT%H%M%SS%3N)

    if command --quiet xdotool

        set --local WIN_ID $(xdotool getactivewindow)

    else if command --quiet xprop

        set --local WIN_ID $(xprop -root _NET_ACTIVE_WINDOW | awk '{print $NF}')

    else
        echo "Error: No tool to get active window id" 1>&2
        return 1
    end

    if command --quiet import

        import -window $WIN_ID ~/screenshot-$DATETIME.png

    else if command --quiet maim

        maim --window $WIN_ID ~/screenshot-$DATETIME.png

    else if command --quiet xwd

        xwd -id $WIN_ID -out ~/screenshot-$DATETIME.xwd || return

        magick ~/screenshot-$DATETIME.xwd ~/screenshot-$DATETIME.png || return

        rm --force -- ~/screenshot-$DATETIME.xwd

    else
        echo "Error: No tool to get screenshot" 1>&2
        return 1
    end
end
