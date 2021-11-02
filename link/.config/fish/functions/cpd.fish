# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function cpd --wraps cp
    command cp $argv && cd $argv[-1]
end
