# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function tfp --description 'tar format patch'

    set PATCHES_DIR (basename (git rev-parse --show-toplevel)) || return

    # XXX: string replace returns 1 (failure) if no replacement was performed
    set PATCHES_DIR patches-(string replace --regex --all '\W' '' $PATCHES_DIR)

    mkdir --verbose -- "$PATCHES_DIR" || return

    git format-patch -o "$PATCHES_DIR" --keep-subject --base=auto --progress (git rev-parse --abbrev-ref HEAD@{upstream})..HEAD || return

    if dir_is_empty "$PATCHES_DIR"
        rmdir --verbose -- "$PATCHES_DIR" || return
    else
        t "$PATCHES_DIR" && del "$PATCHES_DIR" || return
    end
end
