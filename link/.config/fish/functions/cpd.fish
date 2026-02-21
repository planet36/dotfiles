# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function cpd --wraps cp
    command cp $argv && cd $argv[-1]
end
