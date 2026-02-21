# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function del --wraps mv --description 'delete (move to trash folder)'

    if not test -d "$TRASH_DIR"
        mkdir --verbose --mode=0700 -- "$TRASH_DIR" || return
    end

    #set -x SIMPLE_BACKUP_SUFFIX $(date -u +.%Y%m%dT%H%M%SS%3N)

    command mv --verbose --backup=simple --suffix=$(date -u +.%Y%m%dT%H%M%SS%3N) --target-directory "$TRASH_DIR" $argv
end
