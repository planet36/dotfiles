
" https://github.com/junegunn/vim-plug

if has('nvim')
    let s:plugdotvim_path = stdpath('data') . '/site/autoload/plug.vim'
else
    let s:plugdotvim_path = $XDG_DATA_HOME . '/vim/autoload/plug.vim'
endif

" https://github.com/junegunn/vim-plug/wiki/tips#automatic-installation

" Install vim-plug if not found
if empty(glob(s:plugdotvim_path))
    silent execute '!curl -fLo ' . s:plugdotvim_path . ' --create-dirs'
                \ 'https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
    autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif
