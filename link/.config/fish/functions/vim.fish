# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function vim --wraps vim --description 'vim that uses XDG vars'
    MYVIMRC='$XDG_CONFIG_HOME/vim/init.vim' VIMINIT='source $MYVIMRC' command vim $argv
end

