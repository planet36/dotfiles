# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function mvd --wraps mv
    mv $argv && cd $argv[-1]
end

