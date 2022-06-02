
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

"call plug#begin(stdpath('data') . '/plugged')
let s:plugged_dir = stdpath('data') . '/plugged'

call plug#begin(s:plugged_dir)

call plug#end()
