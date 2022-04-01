# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function boottime --description 'Print the boot time'
    set BTIME $(awk '/^btime/{print $2}' /proc/stat)
    date --date=@"$BTIME" +'%a %F %T %Z'
end
