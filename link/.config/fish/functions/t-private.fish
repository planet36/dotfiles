# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function t-private --description 'tar private config files and folders'

    pushd . || return

    cd || return

    set TGT_DIR private.$(date +%s)

    mkdir --verbose -- "$TGT_DIR" || return

    #find .config -type f -not -empty -name 'private.*' | xargs cp --verbose --target-directory $TGT_DIR || return
    #for FILE in $(find .config -type f -not -empty -name 'private.*')
    #for FILE in $(find .config -type f -name 'private.*')
    #    rsync -avR "$FILE" "$TGT_DIR" || return
    #end

    find .config -type f -name 'private.*' | rsync -avR --files-from=- . "$TGT_DIR" || return

    if test -d "$GNUPGHOME"
        #cp --verbose --target-directory "$TGT_DIR" -- "$GNUPGHOME" || return
        rsync -avR $(realpath --relative-base="$HOME" "$GNUPGHOME") "$TGT_DIR" || return
    end

    if test -d "$PASSWORD_STORE_DIR"
        #cp --verbose --target-directory "$TGT_DIR" -- "$PASSWORD_STORE_DIR" || return
        rsync -avR $(realpath --relative-base="$HOME" "$PASSWORD_STORE_DIR") "$TGT_DIR" || return
    end

    if test -d .ssh/
        #cp --verbose --target-directory "$TGT_DIR" -- .ssh || return
        rsync -avR .ssh "$TGT_DIR" || return
    end

    if dir_is_empty "$TGT_DIR"
        rmdir --verbose -- "$TGT_DIR" || return
    else
        t "$TGT_DIR" && xz -9 -e "$TGT_DIR".tar && del "$TGT_DIR" || return
    end

    popd || return
end
