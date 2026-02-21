# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

function git-remote-https-to-ssh --description 'change remote url from https to ssh'

    echo "# Before"
    git remote --verbose

    git remote set-url origin $(git remote get-url --all origin | sed -E -e 's|https://([^/]+)/|git@\1:|')
    echo

    echo "# After"
    git remote --verbose
end
