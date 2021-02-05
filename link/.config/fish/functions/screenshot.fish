# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function screenshot --description 'Take a screenshot'

    set --local DATETIME (date -u +%Y%m%dT%H%M%SS%3N)

    if command --quiet import

        import -window root ~/screenshot-$DATETIME.png

    else if command --quiet xwd

        xwd -root -out ~/screenshot-$DATETIME.xwd || return

        convert ~/screenshot-$DATETIME.xwd ~/screenshot-$DATETIME.png || return

        rm --force -- ~/screenshot-$DATETIME.xwd

    end

end
