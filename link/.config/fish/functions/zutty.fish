# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function zutty --wraps zutty --description 'zutty with fontpath given'
    command zutty -fontpath "$XDG_DATA_HOME"/fonts $argv
end
