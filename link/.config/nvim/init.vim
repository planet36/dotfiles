" vim: set foldmethod=marker foldlevel=0:

" {{{ Nvim defaults for Vim
" These are defaults in nvim but not vim

if ! has('nvim')

" "If you set this option in your vimrc file, you should probably put it at the very start."
set nocompatible

" https://raw.githubusercontent.com/neovim/neovim/master/runtime/doc/vim_diff.txt
" https://github.com/neovim/neovim/blob/master/runtime/doc/vim_diff.txt

" nvim-defaults

" Syntax highlighting is enabled by default
syntax on

" ":filetype plugin indent on" is enabled by default
filetype plugin indent on

" 'autoindent' is enabled
set autoindent

" 'autoread' is enabled
set autoread

" 'background' defaults to "dark" (unless set automatically by the terminal/UI)
set background=dark

" 'backspace' defaults to "indent,eol,start"
set backspace=indent,eol,start

" 'backupdir' defaults to .,~/.local/share/nvim/backup (|xdg|)
" NOTE: different from nvim
set backupdir=~/.local/share/vim/backup

" 'belloff' defaults to "all"
set belloff=all

" 'compatible' is always disabled
" See the top of the file

" 'complete' excludes "i"
set complete-=i

" 'cscopeverbose' is enabled
set cscopeverbose

" 'directory' defaults to ~/.local/share/nvim/swap// (|xdg|), auto-created
" NOTE: different from nvim
set directory=~/.local/share/vim/swap//

" 'display' defaults to "lastline,msgsep"
" NOTE: different from nvim
set display=lastline

" 'encoding' is UTF-8 (cf. 'fileencoding' for file-content encoding)
set encoding=utf-8

" 'fillchars' defaults (in effect) to "vert:│,fold:·,sep:│"
" NOTE: different from nvim
set fillchars=vert:│,fold:·

" 'formatoptions' defaults to "tcqj"
set formatoptions=tcqj

" 'fsync' is disabled
set nofsync

" 'history' defaults to 10000 (the maximum)
set history=10000

" 'hlsearch' is enabled
set hlsearch

" 'incsearch' is enabled
set incsearch

" 'langnoremap' is enabled
set langnoremap

" 'langremap' is disabled
set nolangremap

" 'laststatus' defaults to 2 (statusline is always shown)
set laststatus=2

" 'listchars' defaults to "tab:> ,trail:-,nbsp:+"
" NOTE: must escape space
set listchars=tab:>\ ,trail:-,nbsp:+

" 'nrformats' defaults to "bin,hex"
set nrformats=bin,hex

" 'ruler' is enabled
set ruler

" 'sessionoptions' includes "unix,slash", excludes "options"
set sessionoptions+=unix,slash
set sessionoptions-=options

" 'shortmess' includes "F", excludes "S"
set shortmess+=F
set shortmess-=S

" 'showcmd' is enabled
set showcmd

" 'sidescroll' defaults to 1
set sidescroll=1

" 'smarttab' is enabled
set smarttab

" 'startofline' is disabled
set nostartofline

" 'tabpagemax' defaults to 50
set tabpagemax=50

" 'tags' defaults to "./tags;,tags"
set tags=./tags;,tags

" 'ttimeoutlen' defaults to 50
set ttimeoutlen=50

" 'ttyfast' is always set
set ttyfast

" 'viewoptions' includes "unix,slash"
set viewoptions+=unix,slash

" 'undodir' defaults to ~/.local/share/nvim/undo (|xdg|), auto-created
" NOTE: different from nvim
set undodir=~/.local/share/nvim/undo

" 'viminfo' includes "!"
set viminfo+=!

" 'wildmenu' is enabled
set wildmenu

" 'wildoptions' defaults to "pum,tagfile"
" NOTE: different from nvim
set wildoptions=tagfile

" The |man.vim| plugin is enabled, to provide the |:Man| command.
runtime ftplugin/man.vim

" The |matchit| plugin is enabled. To disable it in your config: >
"   :let loaded_matchit = 1
try
packadd! matchit
catch /^Vim\%((\a\+)\)\=:E492/ " catch error E492
endtry

set runtimepath+=~/.local/share/vim
set viminfofile=~/.local/share/vim/viminfo

endif

" }}}

" {{{ Clipboard

" This option is a list of comma separated names.
if has('clipboard')
    if has('unnamedplus')
        set clipboard^=unnamedplus
    else
        set clipboard^=unnamed
    endif
endif

" }}}

" {{{ Backup files & directory, swap directory, undo files & directory

set backup

set undofile

if has('nvim')
    set backupdir-=.
endif

augroup backup_extension_timestamp
    autocmd!
    if exists('*strftime')
        " String which is appended to a file name to make the name of the backup file.
        autocmd BufWritePre * let &backupext = '~' . strftime('%Y%m%dT%H%M%S') . '~'
    else
        set backupext&
    endif
augroup END

" }}}

" {{{ Line numbers

set number

" }}}

" {{{ File type

autocmd BufRead,BufNewFile *.cal setfiletype c
autocmd BufRead,BufNewFile *.fish setfiletype sh

" }}}

" {{{ Syntax highlighting

" :help syn-sync
syntax sync fromstart
"syntax sync minlines=300

if has('termguicolors')
    set termguicolors
endif

let c_comment_strings=1
let c_space_errors=1
let c_curly_error=1
let c_minlines=200

" :help doxygen-syntax
let g:load_doxygen_syntax=1

" WARNING: Uses italic fonts
"let g:doxygen_enhanced_color=1

set list

" https://vi.stackexchange.com/a/4304
" Space character must be escaped with a backslash
"set listchars+=tab:\ \ ,trail:␣
set listchars+=trail:␣

" }}}

" {{{ Syntax debugging

" http://vim.wikia.com/wiki/Identify_the_syntax_highlighting_group_used_at_the_cursor

"nmap <F3> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<' . synIDattr(synID(line("."),col("."),0),"name") . "> lo<" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">"<CR>
nmap <F3> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<' . synIDattr(synID(line("."),col("."),0),"name") . "> lo<" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">" . " FG:" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"fg#")<CR>

" https://jordanelver.co.uk/blog/2015/05/27/working-with-vim-colorschemes/
" http://stackoverflow.com/a/1467830
" Show syntax highlighting groups for word under cursor
nmap <F4> :call <SID>SynStack()<CR>
function! <SID>SynStack()
    if !exists("*synstack")
        return
    endif
    echo map(synstack(line('.'), col('.')), 'synIDattr(v:val, "name")')
endfunc

" }}}

" {{{ Indentation

"set smartindent
"set noexpandtab
set shiftwidth=4
set softtabstop=4
set tabstop=4

" Disable indentation settings in $VIMRUNTIME/ftplugin/python.vim
let g:python_recommended_style=0

" :help cinoptions-values
set cinoptions=:0,g0,N-s,t0,c0,C1

" }}}

" {{{ C/C++ block comments

augroup c_cpp_block_comments
    autocmd!
    " A comma separated list of strings that can start a comment line.  See |format-comments|.  See |option-backslash| about using backslashes to insert a space.
    autocmd FileType c,cpp setlocal comments^=s:/*,mb:*,ex:*/
augroup END

" }}}

" {{{ Searching

set nowrapscan
set ignorecase
set smartcase

" Stop the highlighting for the 'hlsearch' option.
nnoremap <silent> <Leader><space> :nohlsearch<CR>

" Find selected text
"vnoremap // y/<C-r>"
" TODO: need to escape regex special characters
vnoremap // y/<C-r>=escape(@", '/.~^$*\[]')<CR>

" Replace selected text
vnoremap <C-r> y:%s/<C-r>"//gc<left><left><left>
" also do escaping of regex special chars
"vnoremap <C-e> y:%s/substitute(<C-r>", '[^0-9A-Za-z_]')//gc<left><left><left>
"vnoremap <C-e> y:%s/<C-r>=escape(@", '/\')<CR>//gc<left><left><left>
" TODO: need to escape regex special characters
vnoremap <C-e> y:%s/<C-r>=escape(@", '/.~^$*\[]')<CR>//gc<left><left><left>

" }}}

" {{{ UI

set whichwrap=<,>,[,]
set matchpairs+=<:>
set scrolloff=3
set cmdheight=2

" }}}

" {{{ Splitting

set splitbelow
set splitright

nnoremap <Leader>h :split<CR>
nnoremap <Leader>v :vsplit<CR>

" }}}

" {{{ Windows

" Moving cursor to other windows

nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

" Window resizing

" Decrease current window width by N (default 1).
"nnoremap <Leader><left> :vertical resize -1<CR>
"nnoremap <C-Left> :vertical resize -1<CR>
nnoremap <F6> :vertical resize -1<CR>
" Decrease current window height by N (default 1).
"nnoremap <Leader><down> :resize -1<CR>
"nnoremap <C-Down> :resize -1<CR>
nnoremap <F7> :resize -1<CR>
"nnoremap _ :resize -1<CR>
" Increase current window height by N (default 1).
"nnoremap <Leader><up> :resize +1<CR>
"nnoremap <C-Up> :resize +1<CR>
nnoremap <F8> :resize +1<CR>
"nnoremap + :resize +1<CR>
" Increase current window width by N (default 1).
"nnoremap <Leader><right> :vertical resize +1<CR>
"nnoremap <C-Right> :vertical resize +1<CR>
nnoremap <F9> :vertical resize +1<CR>


" Open help window in a vertical split to the right.
augroup help_window_right
    autocmd!
    " Move the current window to be at the far right
    autocmd FileType help wincmd L
augroup END

" }}}

" {{{ Folding

set foldmethod=marker
set foldlevelstart=99

" }}}

" {{{ Maps

inoremap jj <esc>
"inoremap kkk <esc>
nnoremap H 0
nnoremap L $
vnoremap H 0
vnoremap L $
inoremap <c-d> <esc>ddi
inoremap <c-s> <c-o>:update<CR>

" Complete whole filenames/lines with a quicker shortcut key in insert mode
inoremap <C-f> <C-x><C-f>
inoremap <C-l> <C-x><C-l>


nnoremap <tab> %

if has('jumplist')
    " g; only available with |+jumplist| feature
    " Insert newline after cursor
    nnoremap K i<CR><esc>g;
else
    " Insert newline after cursor
    nnoremap K i<CR><esc>`.
endif

" Yank from the cursor to the end of the line, to be consistent with C and D.
nnoremap Y y$

" save my left pinky
nnoremap <space> :

nnoremap <down> gj
nnoremap <up> gk

function! <SID>RemoveTrailingWhitespace()
    let _s=@/
    let l = line('.')
    let c = col('.')
    %s/\v\s+$//e
    let @/=_s
    call cursor(l, c)
endfunction

" remove trailing whitespace.
" / is the last search pattern register
"nnoremap <Leader>S :%s/\v\s+$//e<CR>:let @/=''<CR>
"nnoremap <Leader>S :%s/\s\+$//e<CR>:let @/=''<CR>
nnoremap <Leader>S :<c-u>call <SID>RemoveTrailingWhitespace()<CR>


" Highlight trailing whitespace.
nnoremap <Leader>w :match ErrorMsg /\v\s+$/<CR>
nnoremap <Leader>W :match none<CR>

" Highlight text beyond 80 columns.
nnoremap <Leader>c :2match ErrorMsg /\v%>80v.+/<CR>
nnoremap <Leader>C :2match none<CR>

augroup filetype_html
    autocmd!
    " create folds for the tag at the cursor
    autocmd FileType html nnoremap <buffer> <localleader>f Vatzf
augroup END

nnoremap <Leader>ev :vsplit $MYVIMRC<CR>
nnoremap <Leader>sv :source $MYVIMRC<CR>

" :help CTRL-^
nnoremap <leader><leader> <c-^>

" double quote a word
" single quote a word
"nnoremap <Leader>" viw<esc>a"<esc>hbi"<esc>lel
"nnoremap <Leader>" viW<esc>a"<esc>Bi"<esc>E
"nnoremap <Leader>' viW<esc>a'<esc>Bi'<esc>E
nnoremap <Leader>" viW<esc>a"<esc>Bi"<esc>
nnoremap <Leader>' viW<esc>a'<esc>Bi'<esc>
"nnoremap <Leader>" viw<esc>bi"<esc>ea"<esc>
"nnoremap <Leader>" viW<esc>Bi"<esc>Ea"<esc>

nnoremap <Leader>g :execute "grep! --recursive " . shellescape(expand("<cWORD>")) . " ."<CR>:copen<CR>


vnoremap <tab> %

" save my left pinky
vnoremap <space> :

vnoremap <down> gj
vnoremap <up> gk

vnoremap <c-s> <esc>:update<CR>gv

" SDW: Their implementation is annoying.  This tries to make visual mode put more usable.

" https://stackoverflow.com/a/5093286
" https://stackoverflow.com/questions/290465/vim-how-to-paste-over-without-overwriting-register#comment71467536_5093286
" https://stackoverflow.com/a/15266864
vnoremap <expr> <silent>p 'pgv"' . v:register . 'y`>'
vnoremap <expr> <silent>P 'Pgv"' . v:register . 'y`>'
"vnoremap <silent>p pgvy`>
"vnoremap <silent>P Pgvy`>
"vnoremap <silent>p pgvygv<Esc>
"vnoremap <silent>x Pgvygv<Esc>

" Don't clobber the clipboard register when pasting over text in visual mode.
"vnoremap <expr> <silent>p 'pgv<Esc>:let @' . v:register . '=@*<CR>'
"vnoremap <expr> <silent>P 'Pgv<Esc>:let @' . v:register . '=@*<CR>'

" Other solutions that aren't as good:
" https://superuser.com/questions/321547/how-do-i-replace-paste-yanked-text-in-vim-without-yanking-the-deleted-lines

function! s:VisualSurround(type, text, ...)

    let l_text = a:text

    if a:0 > 0
        let r_text = a:1
    else
        let r_text = l_text
    endif

    if a:type ==? "v"
        " v or V
        " visual character mode or visual line mode
        execute "normal! \<esc>`>a" . r_text . "\<esc>`<i" . l_text . "\<esc>"
    elseif a:type ==# "\<c-v>"
        " visual block mode
        " ##### XXX: this doesn't work
        "execute "normal! gvA" . r_text . "\<esc>gvI" . l_text . "\<esc>"
        execute "normal! \<esc>gvA" . r_text . "\<esc>gvI" . l_text . "\<esc>"
    else
        return
    endif

endfunction


" this doesn't work in visual mode, only visual block mode
"vnoremap <Leader>' A'<esc>gvI'<esc>
"vnoremap <Leader>" A"<esc>gvI"<esc>

" this works in visual mode, but not in visual block mode
"vnoremap <Leader>' <esc>`>a'<esc>`<i'<esc>
"vnoremap <Leader>" <esc>`>a"<esc>`<i"<esc>
"vnoremap <Leader>( <esc>`>a)<esc>`<i(<esc>
"vnoremap <Leader>[ <esc>`>a]<esc>`<i[<esc>
"vnoremap <Leader>{ <esc>`>a}<esc>`<i{<esc>
"vnoremap <Leader>< <esc>`>a><esc>`<i<<esc>

" this works in visual mode, and in visual block mode, but not visual line
" mode
"vnoremap <Leader>' c''<Esc>P
"vnoremap <Leader>" c""<Esc>P

vnoremap <Leader>` :<c-u>call <SID>VisualSurround(visualmode(), "`")<CR>
vnoremap <Leader>' :<c-u>call <SID>VisualSurround(visualmode(), "'")<CR>
vnoremap <Leader>" :<c-u>call <SID>VisualSurround(visualmode(), '"')<CR>
vnoremap <Leader>( :<c-u>call <SID>VisualSurround(visualmode(), '(', ')')<CR>
vnoremap <Leader>[ :<c-u>call <SID>VisualSurround(visualmode(), '[', ']')<CR>
vnoremap <Leader>{ :<c-u>call <SID>VisualSurround(visualmode(), '{', '}')<CR>
vnoremap <Leader>< :<c-u>call <SID>VisualSurround(visualmode(), '<', '>')<CR>
vnoremap <Leader>* :<c-u>call <SID>VisualSurround(visualmode(), '/*', '*/')<CR>
"vnoremap <Leader>x :call VisualSurround(visualmode(), '_')<CR>

" }}}

" {{{ Insert date/time

command! InsertDate normal! i<c-r>=strftime('%F')<CR>
command! InsertTime normal! i<c-r>=strftime('%T')<CR>
command! InsertDateTime normal! i<c-r>=strftime('%FT%T%z')<CR>

" }}}

" {{{ Abbreviations

iabbrev amek make
iabbrev amke make
iabbrev becuase because
iabbrev cdl cld
iabbrev clena clean
iabbrev csl cls
iabbrev daefult default
iabbrev dafeult default
iabbrev deafult default
iabbrev dfeualt default
iabbrev dpritnf dprintf
iabbrev ehre here
iabbrev fpritnf fprintf
iabbrev maek make
iabbrev medl meld
iabbrev onece once
iabbrev pramga pragma
iabbrev pritn print
iabbrev pritnf printf
iabbrev reurn return
iabbrev reutrn return
iabbrev snpritnf snprintf
iabbrev soem some
iabbrev soemthgin something
iabbrev soemthign something
iabbrev soemthing something
iabbrev somethign something
iabbrev spritnf sprintf
iabbrev TEh The
iabbrev Teh The
iabbrev teh the
iabbrev THe The
iabbrev TODOO TODO
iabbrev TOOD TODO
iabbrev treu true
iabbrev vdpritnf vdprintf
iabbrev vfpritnf vfprintf
iabbrev vpritnf vprintf
iabbrev vsnpritnf vsnprintf
iabbrev vspritnf vsprintf
iabbrev whcih which
iabbrev wiht with
iabbrev witht with

" }}}

" {{{ Diff

" :help :set-termcap
" https://vi.stackexchange.com/a/2363
"execute "set <M-j>=\ej"
"execute "set <M-k>=\ek"
nnoremap <M-Up> [c
nnoremap <M-Down> ]c

" }}}

" {{{ Restore cursor

" *restore-cursor* *last-position-jump*
autocmd BufReadPost *
\ if line("'\"") >= 1 && line("'\"") <= line("$") && &ft !~# 'commit'
\ |   exe "normal! g`\""
\ | endif

" }}}

" {{{ Source files

let s:source_these_files = [
            \ 'plugins.vim',
            \ ]

if has('nvim')
    for f in s:source_these_files
        execute 'source ' . stdpath('config') . '/' . f
    endfor
else
    for f in s:source_these_files
        execute 'source ' . $XDG_CONFIG_HOME . '/vim/' . f
    endfor
endif

" }}}

" {{{ C++ enhanced highlight

" https://github.com/octol/vim-cpp-enhanced-highlight/blob/master/README.md

" Highlighting of class scope is disabled by default. To enable set
" let g:cpp_class_scope_highlight = 1

" Highlighting of member variables is disabled by default. To enable set
" let g:cpp_member_variable_highlight = 1

" Highlighting of class names in declarations is disabled by default. To enable set
" let g:cpp_class_decl_highlight = 1

" Highlighting of POSIX functions is disabled by default. To enable set
" let g:cpp_posix_standard = 1

" There are two ways to highlight template functions. Either
" let g:cpp_experimental_simple_template_highlight = 1

" which works in most cases, but can be a little slow on large files. Alternatively set
" let g:cpp_experimental_template_highlight = 1

" which is a faster implementation but has some corner cases where it doesn't work.

" Note: C++ template syntax is notoriously difficult to parse, so don't expect this feature to be perfect.

" Highlighting of library concepts is enabled by
" let g:cpp_concepts_highlight = 1

" This will highlight the keywords concept and requires as well as all named requirements (like DefaultConstructible) in the standard library.

" Highlighting of user defined functions can be disabled by
" let g:cpp_no_function_highlight = 1

" }}}

" {{{ Color schemes

set cursorline

"colorscheme default

set background=dark

let s:colorscheme_list = [
            \ 'srcery',
            \ 'gruvbox',
            \ 'candycode',
            \ 'breezy',
            \ 'OceanicNext',
            \ 'colorsbox-steighties',
            \ 'murphy',
            \ ]

for c in s:colorscheme_list

    try
        execute 'colorscheme '.c
        break
    catch /^Vim\%((\a\+)\)\=:E185/ " catch error E185
        continue
    endtry

endfor


"highlight clear CursorLine
"highlight LineNr guifg=#FFFFCC
"highlight CursorLineNr guifg=#CC0088
"highlight Constant guifg=#CCCC00

" copied from sonofobsidian.vim
"highlight Number guifg=#FFCD22
"highlight Number guifg=#FFDD00
"highlight Number guifg=#FFCC44
"highlight Number guifg=#FFCC33
"highlight Number guifg=#FFCC22
"highlight Number guifg=#FFCC00

" https://github.com/srcery-colors/srcery-vim/blob/master/colors/srcery.vim#L28
"highlight Constant guifg=#FBB829
"highlight Character guifg=#FBB829
"highlight Boolean guifg=#FBB829
highlight Number guifg=#FBB829
highlight Float guifg=#FBB829

" }}}
