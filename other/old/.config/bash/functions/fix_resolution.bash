# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

##### TODO: test this
function fix_resolution
{
    local OUTPUT
    #local MODE
    OUTPUT=$(xrandr | awk '$2 == "connected"{print $1; exit}')
    #xrandr --output VGA-1 --mode 1920x1200
    xrandr --output "${OUTPUT}" --auto
}
