# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function trash --description 'empty the trash'
    printf 'Num. items removed: '
    time find "$TRASH_DIR" -mindepth 1 -print -delete | wc --lines
end

