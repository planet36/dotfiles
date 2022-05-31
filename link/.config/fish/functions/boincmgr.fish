# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function boincmgr --wraps boincmgr --description 'boincmgr with datadir specified'

    if not set --query BOINC_DATA_DIR
        #set BOINC_DATA_DIR /media/sf_shared/boinc-data
        set BOINC_DATA_DIR ~/boinc-data
    end

    mkdir --verbose --parents -- "$BOINC_DATA_DIR" || return

    cd "$BOINC_DATA_DIR" || return

    command boincmgr --datadir="$BOINC_DATA_DIR" $argv
end
