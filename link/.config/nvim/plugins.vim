
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

" Make sure you use single quotes
"Plug 'junegunn/vim-plug'
"Plug 'junegunn/fzf', { 'do': { -> fzf#install() } } " optional
Plug 'junegunn/fzf.vim'
Plug 'tpope/vim-sensible/'
"Plug 'farmergreg/vim-lastplace'
Plug 'godlygeek/tabular'
Plug 'AndrewRadev/linediff.vim'
Plug 'chrisbra/unicode.vim'
Plug 'octol/vim-cpp-enhanced-highlight'

" color schemes
Plug 'srcery-colors/srcery-vim'
Plug 'morhetz/gruvbox'
Plug 'mkarmona/colorsbox'
Plug 'vim-scripts/candycode.vim'
Plug 'fneu/breezy'
Plug 'mhartington/oceanic-next'
Plug 'tekannor/ayu-vim'
"Plug 'flazz/vim-colorschemes'

call plug#end()
