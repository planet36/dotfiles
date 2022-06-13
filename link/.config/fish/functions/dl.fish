# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function dl --wraps dict --description 'dict WORD | less'
    command dict $argv | command less --quit-if-one-screen
end
