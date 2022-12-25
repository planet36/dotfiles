" SPDX-FileCopyrightText: Steven Ward
" SPDX-License-Identifier: OSL-3.0

" vim: set foldmethod=marker:

" {{{ Turn off provider warnings

lua vim.g.loaded_ruby_provider = 0
lua vim.g.loaded_node_provider = 0
lua vim.g.loaded_perl_provider = 0

" }}}

" {{{ Clipboard

" This option is a list of comma separated names.
lua vim.opt.clipboard:append { 'unnamedplus' }

" }}}

" {{{ Backup files & directory, swap directory, undo files & directory

lua vim.o.backup = true

lua vim.o.undofile = true

lua vim.opt.backupdir:remove { '.' }

lua << EOT
vim.api.nvim_create_autocmd("BufWritePre", {
	group = vim.api.nvim_create_augroup("backup_extension_timestamp", { clear = true }),
	pattern = { "*" },
	callback = function()
		-- String which is appended to a file name to make the name of the backup file.
		vim.o.backupext = '~' .. os.date('%Y%m%dT%H%M%S') .. '~'
	end
})
EOT

" }}}

" {{{ Include path

lua vim.opt.path:append { vim.fs.normalize('~/.local/include') }

" }}}

" {{{ ignore case when completing file names and directories

lua vim.o.fileignorecase = true
lua vim.o.wildignorecase = true

" }}}

" {{{ Line numbers

lua vim.o.number = true

" }}}

" {{{ File type

lua << EOT
vim.api.nvim_create_autocmd({"BufRead","BufNewFile"}, {
	pattern = {"*.cal"},
	callback = function()
		vim.o.filetype = 'c'
	end
})
EOT

lua << EOT
vim.api.nvim_create_autocmd({"BufRead","BufNewFile"}, {
	pattern = {"*.fish"},
	callback = function()
		vim.o.filetype = 'sh'
	end
})
EOT

" }}}

" {{{ Syntax highlighting

" :help syn-sync
lua vim.cmd.syntax('sync', 'fromstart')

lua vim.o.termguicolors = true

lua vim.g.c_comment_strings = 1
lua vim.g.c_space_errors = 1
lua vim.g.c_curly_error = 1
lua vim.g.c_minlines = 200

" :help doxygen-syntax
lua vim.g.load_doxygen_syntax = 1

" WARNING: Uses italic fonts
"let g:doxygen_enhanced_color=1

lua vim.o.list = true

lua vim.opt.listchars:append { trail = [[\u2423]]}

" }}}

" {{{ Syntax debugging

" https://vim.fandom.com/wiki/Identify_the_syntax_highlighting_group_used_at_the_cursor

"nmap <F3> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<' . synIDattr(synID(line("."),col("."),0),"name") . "> lo<" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">"<NL>
nmap <F3> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<' . synIDattr(synID(line("."),col("."),0),"name") . "> lo<" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">" . " FG:" . synIDattr(synIDtrans(synID(line("."),col("."),1)),"fg#")<NL>

" https://jordanelver.co.uk/blog/2015/05/27/working-with-vim-colorschemes/
" https://stackoverflow.com/questions/1467438/find-out-to-which-highlight-group-a-particular-keyword-symbol-belongs-in-vim/1467830#1467830
" Show syntax highlighting groups for word under cursor
nmap <F4> :call <SID>SynStack()<NL>
function! <SID>SynStack()
	if !exists("*synstack")
		return
	endif
	echo map(synstack(line('.'), col('.')), 'synIDattr(v:val, "name")')
endfunc

" }}}

" {{{ Indentation

lua vim.o.shiftwidth=4
lua vim.o.softtabstop=4
lua vim.o.tabstop=4

" :help cinoptions-values
lua vim.o.cinoptions = ':0,g0,N-s,t0,c0,C1'

" }}}

" {{{ C/C++ block comments

lua << EOT
vim.api.nvim_create_autocmd("FileType", {
	group = vim.api.nvim_create_augroup("c_cpp_block_comments", { clear = true }),
	pattern = { "c,cpp" }, -- matched against filetype
	callback = function()
		-- :help format-comments
		vim.o.comments = string.gsub(vim.o.comments, "s1:", "s:")
	end
})
EOT

" }}}

" {{{ Searching

lua vim.o.wrapscan = false
lua vim.o.ignorecase = true
lua vim.o.smartcase = true

" Stop the highlighting for the 'hlsearch' option.
nnoremap <silent> <Leader><space> :nohlsearch<NL>

" Find selected text
"xnoremap // y/<C-r>"
" TODO: need to escape regex special characters
xnoremap // y/<C-r>=escape(@", '/.~^$*\[]')<NL>

" Replace selected text
xnoremap <C-r> y:%s/<C-r>"//gc<left><left><left>
" also do escaping of regex special chars
"xnoremap <C-e> y:%s/substitute(<C-r>", '[^0-9A-Za-z_]')//gc<left><left><left>
"xnoremap <C-e> y:%s/<C-r>=escape(@", '/\')<NL>//gc<left><left><left>
" TODO: need to escape regex special characters
xnoremap <C-e> y:%s/<C-r>=escape(@", '/.~^$*\[]')<NL>//gc<left><left><left>

" }}}

" {{{ Disable mouse support if inside tmux

lua << EOT
if vim.env.TMUX ~= nil then
	-- TMUX is set
	vim.o.mouse = ''
end
EOT

" }}}

" {{{ UI

lua vim.o.whichwrap = '<,>,[,]'
lua vim.opt.matchpairs:append { '<:>' }
lua vim.o.scrolloff = 6

" }}}

" {{{ Splitting

lua vim.o.splitbelow = true
lua vim.o.splitright = true

nnoremap <Leader>h :split<NL>
nnoremap <Leader>v :vsplit<NL>

" }}}

" {{{ Windows

" Moving cursor to other windows

nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

" Window resizing

" Decrease current window width by N (default 1).
"nnoremap <Leader><left> :vertical resize -1<NL>
"nnoremap <C-Left> :vertical resize -1<NL>
nnoremap <F6> :vertical resize -1<NL>
" Decrease current window height by N (default 1).
"nnoremap <Leader><down> :resize -1<NL>
"nnoremap <C-Down> :resize -1<NL>
nnoremap <F7> :resize -1<NL>
"nnoremap _ :resize -1<NL>
" Increase current window height by N (default 1).
"nnoremap <Leader><up> :resize +1<NL>
"nnoremap <C-Up> :resize +1<NL>
nnoremap <F8> :resize +1<NL>
"nnoremap + :resize +1<NL>
" Increase current window width by N (default 1).
"nnoremap <Leader><right> :vertical resize +1<NL>
"nnoremap <C-Right> :vertical resize +1<NL>
nnoremap <F9> :vertical resize +1<NL>


lua << EOT
-- Open help window in a vertical split to the right.
vim.api.nvim_create_autocmd("BufEnter", {
	group = vim.api.nvim_create_augroup("help_window_right", { clear = true }),
	pattern = { "*.txt" },
	callback = function()
		if vim.o.buftype == 'help' then
			-- Move the current window to be at the far right
			-- https://vi.stackexchange.com/a/4464
			vim.cmd.wincmd("L")
		end
	end
})
EOT

" }}}

" {{{ Folding

lua vim.o.foldmethod = 'marker'
lua vim.o.foldlevelstart = 99

" }}}

" {{{ Maps

inoremap jj <esc>
"inoremap kkk <esc>
nnoremap H 0
nnoremap L $
xnoremap H 0
xnoremap L $
inoremap <c-d> <esc>ddi
inoremap <c-s> <c-o>:update<NL>

" Complete whole filenames/lines with a quicker shortcut key in insert mode
inoremap <C-f> <C-x><C-f>
inoremap <C-l> <C-x><C-l>


nnoremap <tab> %

" g; only available with |+jumplist| feature
" Insert newline after cursor
nnoremap K i<NL><esc>g;

" save my left pinky
nnoremap <space> :

nnoremap <down> gj
nnoremap <up> gk

lua <<EOT
function remove_trailing_whitespace()
	-- https://neovim.io/doc/user/api.html#nvim_win_get_cursor()
	-- https://neovim.io/doc/user/builtin.html#getreginfo()
	-- https://neovim.io/doc/user/builtin.html#setreg()
	-- https://neovim.io/doc/user/api.html#nvim_win_set_cursor()
	local cursor_pos = vim.api.nvim_win_get_cursor(0)
	local reg_info = vim.fn.getreginfo('/')
	vim.cmd([[%s/\v\s+$//e]])
	vim.fn.setreg('/', reg_info)
	vim.api.nvim_win_set_cursor(0, cursor_pos)
end
EOT

" remove trailing whitespace.
" / is the last search pattern register
"nnoremap <Leader>S :%s/\v\s+$//e<NL>:let @/=''<NL>
"nnoremap <Leader>S :%s/\s\+$//e<NL>:let @/=''<NL>

lua vim.keymap.set("n", "<Leader>S", function() remove_trailing_whitespace() end)


" Highlight trailing whitespace.
nnoremap <Leader>w :match ErrorMsg /\v\s+$/<NL>
nnoremap <Leader>W :match none<NL>

" Highlight text beyond 80 columns.
nnoremap <Leader>c :2match ErrorMsg /\v%>80v.+/<NL>
nnoremap <Leader>C :2match none<NL>

nnoremap <Leader>ev :vsplit $MYVIMRC<NL>
nnoremap <Leader>sv :source $MYVIMRC<NL>

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

nnoremap <Leader>g :execute "grep! --recursive " . shellescape(expand("<cWORD>")) . " ."<NL>:copen<NL>


xnoremap <tab> %

" save my left pinky
xnoremap <space> :

xnoremap <down> gj
xnoremap <up> gk

xnoremap <c-s> <esc>:update<NL>gv

" SDW: Their implementation is annoying.  This tries to make visual mode put more usable.

" https://stackoverflow.com/a/5093286
" https://stackoverflow.com/questions/290465/vim-how-to-paste-over-without-overwriting-register#comment71467536_5093286
" https://stackoverflow.com/a/15266864
xnoremap <expr> <silent>p 'pgv"' . v:register . 'y`>'
xnoremap <expr> <silent>P 'Pgv"' . v:register . 'y`>'
"xnoremap <silent>p pgvy`>
"xnoremap <silent>P Pgvy`>
"xnoremap <silent>p pgvygv<Esc>
"xnoremap <silent>x Pgvygv<Esc>

" Don't clobber the clipboard register when pasting over text in visual mode.
"xnoremap <expr> <silent>p 'pgv<Esc>:let @' . v:register . '=@*<NL>'
"xnoremap <expr> <silent>P 'Pgv<Esc>:let @' . v:register . '=@*<NL>'

" Other solutions that aren't as good:
" https://superuser.com/questions/321547/how-do-i-replace-paste-yanked-text-in-vim-without-yanking-the-deleted-lines

lua <<EOT
function visual_surround(l_text, r_text)

	-- https://neovim.io/doc/user/api.html#nvim_replace_termcodes()
	-- https://neovim.io/doc/user/builtin.html#feedkeys()
	local esc = vim.api.nvim_replace_termcodes('<Esc>', true, false, true)
	local cntrl_v = vim.api.nvim_replace_termcodes('<C-v>', true, false, true)
	local mode = vim.fn.mode()

	if mode == 'v' or mode == 'V' then -- visual or visual line
		vim.api.nvim_feedkeys(esc .. '`>a' .. r_text .. esc .. '`<i' .. l_text, 'x', false)
	elseif mode == cntrl_v then -- visual block
		vim.api.nvim_feedkeys('A' .. r_text .. esc .. 'gvI' .. l_text, 'x', false)
	end
end
EOT

" this doesn't work in visual mode, only visual block mode
"xnoremap <Leader>' A'<esc>gvI'<esc>
"xnoremap <Leader>" A"<esc>gvI"<esc>

" this works in visual mode, but not in visual block mode
"xnoremap <Leader>' <esc>`>a'<esc>`<i'<esc>
"xnoremap <Leader>" <esc>`>a"<esc>`<i"<esc>
"xnoremap <Leader>( <esc>`>a)<esc>`<i(<esc>
"xnoremap <Leader>[ <esc>`>a]<esc>`<i[<esc>
"xnoremap <Leader>{ <esc>`>a}<esc>`<i{<esc>
"xnoremap <Leader>< <esc>`>a><esc>`<i<<esc>

" this works in visual mode, and in visual block mode, but not visual line
" mode
"xnoremap <Leader>' c''<Esc>P
"xnoremap <Leader>" c""<Esc>P

lua vim.keymap.set("x", "<Leader>`", function() visual_surround("`", "`") end)
lua vim.keymap.set("x", "<Leader>'", function() visual_surround("'", "'") end)
lua vim.keymap.set("x", '<Leader>"', function() visual_surround('"', '"') end)
lua vim.keymap.set("x", "<Leader>(", function() visual_surround('(', ')') end)
lua vim.keymap.set("x", "<Leader>[", function() visual_surround('[', ']') end)
lua vim.keymap.set("x", "<Leader>{", function() visual_surround('{', '}') end)
lua vim.keymap.set("x", "<Leader><", function() visual_surround('<', '>') end)
lua vim.keymap.set("x", "<Leader>*", function() visual_surround('/*', '*/') end)

" }}}

" {{{ Abbreviations

lua vim.cmd.inoreabbrev('amek', 'make')
lua vim.cmd.inoreabbrev('amke', 'make')
lua vim.cmd.inoreabbrev('becuase', 'because')
lua vim.cmd.inoreabbrev('cdl', 'cld')
lua vim.cmd.inoreabbrev('clena', 'clean')
lua vim.cmd.inoreabbrev('constepxr', 'constexpr')
lua vim.cmd.inoreabbrev('csl', 'cls')
lua vim.cmd.inoreabbrev('daefult', 'default')
lua vim.cmd.inoreabbrev('dafeult', 'default')
lua vim.cmd.inoreabbrev('deafult', 'default')
lua vim.cmd.inoreabbrev('delctype', 'decltype')
lua vim.cmd.inoreabbrev('dfeualt', 'default')
lua vim.cmd.inoreabbrev('doen', 'done')
lua vim.cmd.inoreabbrev('dpritnf', 'dprintf')
lua vim.cmd.inoreabbrev('ecoh', 'echo')
lua vim.cmd.inoreabbrev('ehre', 'here')
lua vim.cmd.inoreabbrev('fpritnf', 'fprintf')
lua vim.cmd.inoreabbrev('ifle', 'file')
lua vim.cmd.inoreabbrev('maek', 'make')
lua vim.cmd.inoreabbrev('medl', 'meld')
lua vim.cmd.inoreabbrev('onece', 'once')
lua vim.cmd.inoreabbrev('pramga', 'pragma')
lua vim.cmd.inoreabbrev('pritn', 'print')
lua vim.cmd.inoreabbrev('pritnf', 'printf')
lua vim.cmd.inoreabbrev('reurn', 'return')
lua vim.cmd.inoreabbrev('reutrn', 'return')
lua vim.cmd.inoreabbrev('snpritnf', 'snprintf')
lua vim.cmd.inoreabbrev('soem', 'some')
lua vim.cmd.inoreabbrev('soemthgin', 'something')
lua vim.cmd.inoreabbrev('soemthign', 'something')
lua vim.cmd.inoreabbrev('soemthing', 'something')
lua vim.cmd.inoreabbrev('somethign', 'something')
lua vim.cmd.inoreabbrev('spritnf', 'sprintf')
lua vim.cmd.inoreabbrev('TEh', 'The')
lua vim.cmd.inoreabbrev('Teh', 'The')
lua vim.cmd.inoreabbrev('teh', 'the')
lua vim.cmd.inoreabbrev('THe', 'The')
lua vim.cmd.inoreabbrev('TODOO', 'TODO')
lua vim.cmd.inoreabbrev('TOOD', 'TODO')
lua vim.cmd.inoreabbrev('treu', 'true')
lua vim.cmd.inoreabbrev('vdpritnf', 'vdprintf')
lua vim.cmd.inoreabbrev('vfpritnf', 'vfprintf')
lua vim.cmd.inoreabbrev('vpritnf', 'vprintf')
lua vim.cmd.inoreabbrev('vsnpritnf', 'vsnprintf')
lua vim.cmd.inoreabbrev('vspritnf', 'vsprintf')
lua vim.cmd.inoreabbrev('whcih', 'which')
lua vim.cmd.inoreabbrev('wiht', 'with')
lua vim.cmd.inoreabbrev('witht', 'with')

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
	autocmd OptionSet diff if &diff | colorscheme default | endif
augroup END

" }}}

" {{{ Command to start Python 3

lua vim.g.python3_host_prog = '/usr/bin/python3'

" }}}

" {{{ Color schemes

lua vim.o.cursorline = true

lua << EOT
local colorscheme_list = {
	'srcery',
	'candycode',
	'breezy',
	'OceanicNext',
	'github_dark_default',
	'gruvbox',
	'murphy',
}

-- https://www.lua.org/pil/7.3.html
-- https://stackoverflow.com/a/55109411/1892784
for i, c in ipairs(colorscheme_list) do
	local ok, result = pcall(vim.cmd, 'colorscheme ' .. c)
	if ok then break end
end
EOT


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
