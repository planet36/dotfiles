# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function tfp --description 'tar format patch'

    set DST $argv[1]

    set PATCHES_DIR $(basename $(git rev-parse --show-toplevel)) || return

    # XXX: string replace returns 1 (failure) if no replacement was performed
    set PATCHES_DIR patches-$(string replace --regex --all '\W' '' $PATCHES_DIR)

    mkdir --verbose -- "$PATCHES_DIR" || return

    # NOTE: If git format-patch gives this error
    # "fatal: base commit should be the ancestor of revision list"
    # Then remove "--base=auto" from the command.
    if not git format-patch -o "$PATCHES_DIR" --keep-subject --base=auto --progress $(git rev-parse --abbrev-ref HEAD@{upstream})..HEAD
        rmdir --verbose -- "$PATCHES_DIR" || return
        return 1
    end

    if dir_is_empty "$PATCHES_DIR"
        rmdir --verbose -- "$PATCHES_DIR" || return
    else
        t "$PATCHES_DIR" && del "$PATCHES_DIR" || return

        if test -d "$DST"
            mv --verbose -- "$PATCHES_DIR".tar "$DST"
        end
    end
end
