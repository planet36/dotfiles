# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function cpd --wraps cp
    cp $argv && cd $argv[-1]
end

