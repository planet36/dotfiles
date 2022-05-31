# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function del
{
    if [[ ! -d "$TRASH_DIR" ]]
    then
        mkdir --verbose --mode=0700 -- "$TRASH_DIR" || return
    fi

    #export SIMPLE_BACKUP_SUFFIX=$(date -u +.%Y%m%dT%H%M%SS%3N)

    #mv --verbose --backup=simple --suffix=.$(date -u +"%Y%m%dT%H%M%SS%3N") --target-directory "$TRASH_DIR"
    command mv --verbose --backup=simple --suffix="$(date -u +.%Y%m%dT%H%M%SS%3N)" --target-directory "$TRASH_DIR" "${@}"
}
