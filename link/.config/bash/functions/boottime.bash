# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# sed -r -n -e 's/^btime ([0-9]+)$/\1/p' /proc/stat
# sed '/^btime /!d; s///;q' /proc/stat
function boottime
{
    date --date=@"$(awk '/^btime/{print $2}' /proc/stat)" +'%a, %F %T'
}
