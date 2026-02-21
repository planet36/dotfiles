# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function bc --wraps bc --description 'bc that uses mathlib and my config'
    command bc --mathlib --quiet "$XDG_CONFIG_HOME"/bc/config.bc $argv
end
