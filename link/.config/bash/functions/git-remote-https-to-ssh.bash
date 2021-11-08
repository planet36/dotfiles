# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function git-remote-https-to-ssh
{
    echo "# Before"
    git remote --verbose

    git remote set-url origin "$(git remote get-url --all origin | sed -e 's|https://([^/]+)/|git@\1.com:|')"
    echo

    echo "# After"
    git remote --verbose
}
