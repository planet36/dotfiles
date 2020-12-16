
" https://github.com/junegunn/vim-plug

" https://github.com/junegunn/vim-plug/wiki/tutorial#installing-plugins
"
" Commands:
" :PlugInstall
" :PlugUpdate
" :PlugClean
" :PlugUpgrade
" :PlugStatus
" :PlugDiff
" :PlugSnapshot

if has('nvim')
    "call plug#begin(stdpath('data') . '/plugged')
    let s:plugged_dir = stdpath('data') . '/plugged'
else
    "call plug#begin('~/.local/share/vim/plugged')
    let s:plugged_dir = $XDG_DATA_HOME . '/vim/plugged'
endif

call plug#begin(s:plugged_dir)

call plug#end()
