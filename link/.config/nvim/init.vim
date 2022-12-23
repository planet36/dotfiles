" SPDX-FileCopyrightText: Steven Ward
" SPDX-License-Identifier: OSL-3.0

" vim: set foldmethod=marker foldlevel=0:

" {{{ Turn off provider warnings

let g:loaded_ruby_provider = 0
let g:loaded_node_provider = 0
let g:loaded_perl_provider = 0

" }}}

" {{{ Clipboard

" This option is a list of comma separated names.
set clipboard+=unnamedplus

" }}}

" {{{ Backup files & directory, swap directory, undo files & directory

set backup

set undofile

set backupdir-=.

augroup backup_extension_timestamp
	autocmd!
	" String which is appended to a file name to make the name of the backup file.
	autocmd BufWritePre * let &backupext = '~' . strftime('%Y%m%dT%H%M%S') . '~'
augroup END

" }}}

" {{{ Include path

set path+=~/.local/include

" }}}

" {{{ ignore case when completing file names and directories

set fileignorecase
set wildignorecase

" }}}

" {{{ Line numbers

set number

" }}}

" {{{ Status line

"set laststatus=2

" }}}

" {{{ File type

autocmd BufRead,BufNewFile *.cal setfiletype c
autocmd BufRead,BufNewFile *.fish setfiletype sh

" }}}

" {{{ Syntax highlighting

" :help syn-sync
syntax sync fromstart
"syntax sync minlines=300

set termguicolors

let c_comment_strings=1
let c_space_errors=1
let c_curly_error=1
let c_minlines=200

" :help doxygen-syntax
let g:load_doxygen_syntax=1

" WARNING: Uses italic fonts
"let g:doxygen_enhanced_color=1

set list

set listchars+=trail:\\u2423

" }}}

" {{{ Syntax debugging

" https://vim.fandom.com/wiki/Identify_the_syntax_highlighting_group_used_at_the_cursor

"nmap <F3> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<' . synIDattr(synID(line("."),col("."),0),"name") . "> lo<" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">"<CR>
nmap <F3> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<' . synIDattr(synID(line("."),col("."),0),"name") . "> lo<" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">" . " FG:" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"fg#")<CR>

" https://jordanelver.co.uk/blog/2015/05/27/working-with-vim-colorschemes/
" https://stackoverflow.com/questions/1467438/find-out-to-which-highlight-group-a-particular-keyword-symbol-belongs-in-vim/1467830#1467830
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

" {{{ Disable mouse support if inside tmux

lua << EOF
if vim.env.TMUX ~= nil then
	-- TMUX is set
	vim.o.mouse = ''
end
EOF

" }}}

" {{{ UI

set whichwrap=<,>,[,]
set matchpairs+=<:>
set scrolloff=6
"set cmdheight=1

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
	" https://vi.stackexchange.com/a/4464
	autocmd BufEnter *.txt if &buftype == 'help' | wincmd L | endif
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

" g; only available with |+jumplist| feature
" Insert newline after cursor
nnoremap K i<CR><esc>g;

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

" {{{ Abbreviations

inoreabbrev amek make
inoreabbrev amke make
inoreabbrev becuase because
inoreabbrev cdl cld
inoreabbrev clena clean
inoreabbrev constepxr constexpr
inoreabbrev csl cls
inoreabbrev daefult default
inoreabbrev dafeult default
inoreabbrev deafult default
inoreabbrev delctype decltype
inoreabbrev dfeualt default
inoreabbrev doen done
inoreabbrev dpritnf dprintf
inoreabbrev ecoh echo
inoreabbrev ehre here
inoreabbrev fpritnf fprintf
inoreabbrev ifle file
inoreabbrev maek make
inoreabbrev medl meld
inoreabbrev onece once
inoreabbrev pramga pragma
inoreabbrev pritn print
inoreabbrev pritnf printf
inoreabbrev reurn return
inoreabbrev reutrn return
inoreabbrev snpritnf snprintf
inoreabbrev soem some
inoreabbrev soemthgin something
inoreabbrev soemthign something
inoreabbrev soemthing something
inoreabbrev somethign something
inoreabbrev spritnf sprintf
inoreabbrev TEh The
inoreabbrev Teh The
inoreabbrev teh the
inoreabbrev THe The
inoreabbrev TODOO TODO
inoreabbrev TOOD TODO
inoreabbrev treu true
inoreabbrev vdpritnf vdprintf
inoreabbrev vfpritnf vfprintf
inoreabbrev vpritnf vprintf
inoreabbrev vsnpritnf vsnprintf
inoreabbrev vspritnf vsprintf
inoreabbrev whcih which
inoreabbrev wiht with
inoreabbrev witht with

" }}}

" {{{ Diff

" :help :set-termcap
" https://vi.stackexchange.com/a/2363
"execute "set <M-j>=\ej"
"execute "set <M-k>=\ek"
nnoremap <M-Up> [c
nnoremap <M-Down> ]c

" Change colorscheme to default when entering diff mode
augroup ChangeColorsInDiff
	autocmd!
	" https://vi.stackexchange.com/a/13395
	autocmd VimEnter,FilterWritePre * if &diff | colorscheme default | endif
	" https://vi.stackexchange.com/a/12852
	autocmd OptionSet diff colorscheme default
augroup END

" }}}

" {{{ Command to start Python 3

let g:python3_host_prog = '/usr/bin/python3'

" }}}

" {{{ Source files

let s:source_these_files = [
			\ ]

for f in s:source_these_files
	execute 'source ' . stdpath('config') . '/' . f
endfor

" }}}

" {{{ Color schemes

set cursorline

"colorscheme default

"set background=dark

let s:colorscheme_list = [
			\ 'srcery',
			\ 'candycode',
			\ 'breezy',
			\ 'OceanicNext',
			\ 'github_dark_default',
			\ 'gruvbox',
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
"highlight Number guifg=#FBB829
"highlight Float guifg=#FBB829

" }}}
