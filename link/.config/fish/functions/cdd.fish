# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function cdd --wraps cd
    cd $argv[1] && d
end
