# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function mkd --wraps mkdir
    mkdir $argv && cd $argv[-1]
end
