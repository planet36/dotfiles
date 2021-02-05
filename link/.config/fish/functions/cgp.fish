# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function cgp --description 'clean, get, and put code'

    pushd . || return
    cd || return
    clean code || return
    get code || return
    put code || return
    popd || return
end

