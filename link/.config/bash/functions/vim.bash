# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function vim
{
    # shellcheck disable=SC2016
    MYVIMRC='$XDG_CONFIG_HOME/vim/init.vim' VIMINIT='source $MYVIMRC' command vim "${@}"
}
