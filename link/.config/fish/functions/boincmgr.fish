# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function boincmgr --description 'boincmgr with datadir specified' --wraps boincmgr

    if not set -q BOINC_DATA_DIR
        set BOINC_DATA_DIR /media/sf_shared/boinc-data
    end

    mkdir --verbose --parents -- "$BOINC_DATA_DIR" || return

    cd "$BOINC_DATA_DIR" || return

    command boincmgr --datadir="$BOINC_DATA_DIR" $argv
end

