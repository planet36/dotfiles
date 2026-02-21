# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function mvd --wraps mv
    command mv $argv && cd $argv[-1]
end
