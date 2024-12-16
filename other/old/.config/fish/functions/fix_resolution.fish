# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

##### TODO: test this
function fix_resolution
    xrandr --output $(xrandr | awk '$2 == "connected"{print $1; exit}') --auto
end
