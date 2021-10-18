
" https://github.com/junegunn/vim-plug/wiki/tips#automatic-installation

if has('nvim')
    let s:plugdotvim_path = stdpath('data') . '/site'
else
    let s:plugdotvim_path = $XDG_DATA_HOME . '/vim'
endif
let s:plugdotvim_path += '/autoload/plug.vim'

" Install vim-plug if not found
if empty(glob(s:plugdotvim_path))
    silent execute '!curl -fLo ' . s:plugdotvim_path . ' --create-dirs'
                \ 'https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
    autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif
