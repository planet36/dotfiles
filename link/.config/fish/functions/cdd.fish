# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function cdd --argument-names DIR --wraps cd
    cd $DIR && d
end
