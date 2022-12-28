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
lua vim.keymap.set("n", "<Leader><space>", ":nohlsearch<NL>")

" Find selected text
" TODO: need to escape regex special characters
lua vim.keymap.set("x", "//", [[y/<C-r>=escape(@", '/.~^$*\[]')<NL>]])

" Replace selected text
lua vim.keymap.set("x", "<C-r>", [[y:%s/<C-r>"//gc<left><left><left>]])
" also do escaping of regex special chars
" TODO: need to escape regex special characters
lua vim.keymap.set("x", "<C-e>", [[y:%s/<C-r>=escape(@", '/.~^$*\[]')<NL>//gc<left><left><left>]])

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

lua vim.keymap.set("n", "<Leader>h", ":split<NL>")
lua vim.keymap.set("n", "<Leader>v", ":vsplit<NL>")

" }}}

" {{{ Windows

" Moving cursor to other windows

lua vim.keymap.set("n", "<C-h>", "<C-w>h")
lua vim.keymap.set("n", "<C-j>", "<C-w>j")
lua vim.keymap.set("n", "<C-k>", "<C-w>k")
lua vim.keymap.set("n", "<C-l>", "<C-w>l")

" Window resizing

" Decrease current window width by N (default 1).
lua vim.keymap.set("n", "<F6>", ":vertical resize -1<NL>")
" Decrease current window height by N (default 1).
lua vim.keymap.set("n", "<F7>", ":resize -1<NL>")
" Increase current window height by N (default 1).
lua vim.keymap.set("n", "<F8>", ":resize +1<NL>")
" Increase current window width by N (default 1).
lua vim.keymap.set("n", "<F9>", ":vertical resize +1<NL>")


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

lua vim.keymap.set("i", "jj", "<esc>")
lua vim.keymap.set("n", "H", "0")
lua vim.keymap.set("n", "L", "$")
lua vim.keymap.set("x", "H", "0")
lua vim.keymap.set("x", "L", "$")
lua vim.keymap.set("i", "<c-d>", "<esc>ddi")
lua vim.keymap.set("i", "<c-s>", "<c-o>:update<NL>")

" Complete whole filenames/lines with a quicker shortcut key in insert mode
lua vim.keymap.set("i", "<C-f>", "<C-x><C-f>")
lua vim.keymap.set("i", "<C-l>", "<C-x><C-l>")


lua vim.keymap.set("n", "<tab>", "%")

" g; only available with |+jumplist| feature
" Insert newline after cursor
lua vim.keymap.set("n", "K", "i<NL><esc>g")

" save my left pinky
lua vim.keymap.set("n", "<space>", ":")

lua vim.keymap.set("n", "<down>", "gj")
lua vim.keymap.set("n", "<up>", "gk")

lua <<EOT
function remove_trailing_whitespace()
	-- https://neovim.io/doc/user/api.html#nvim_win_get_cursor()
	-- https://neovim.io/doc/user/builtin.html#getreginfo()
	-- https://neovim.io/doc/user/builtin.html#setreg()
	-- https://neovim.io/doc/user/api.html#nvim_win_set_cursor()
	local cursor_pos = vim.api.nvim_win_get_cursor(0)
	local reg_info = vim.fn.getreginfo('/')
	vim.cmd([[%s/\v\s+$//e]])
	-- / is the last search pattern register
	vim.fn.setreg('/', reg_info)
	vim.api.nvim_win_set_cursor(0, cursor_pos)
end
EOT

" remove trailing whitespace.
lua vim.keymap.set("n", "<Leader>S", function() remove_trailing_whitespace() end)


" Highlight trailing whitespace.
lua vim.keymap.set("n", "<Leader>w", [[:match ErrorMsg /\v\s+$/<NL>]])
lua vim.keymap.set("n", "<Leader>W", ":match none<NL>")

" Highlight text beyond 80 columns.
lua vim.keymap.set("n", "<Leader>c", [[:2match ErrorMsg /\v%>80v.+/<NL>]])
lua vim.keymap.set("n", "<Leader>C", ":2match none<NL>")

lua vim.keymap.set("n", "<Leader>ev", ":vsplit $MYVIMRC<NL>")
lua vim.keymap.set("n", "<Leader>sv", ":source $MYVIMRC<NL>")

" :help CTRL-^
lua vim.keymap.set("n", "<leader><leader>", "<c-^>")

" double quote a word
" single quote a word
lua vim.keymap.set("n", [[<Leader>"]], [[viW<esc>a"<esc>Bi"<esc>]])
lua vim.keymap.set("n", [[<Leader>']], [[viW<esc>a'<esc>Bi'<esc>]])

lua vim.keymap.set("n", "<Leader>g", [[:execute "grep! --recursive " . shellescape(expand("<cWORD>")) . " ."<NL>:copen<NL>]])


lua vim.keymap.set("x", "<tab>", "%")

" save my left pinky
lua vim.keymap.set("x", "<space>", ":")

lua vim.keymap.set("x", "<down>", "gj")
lua vim.keymap.set("x", "<up>", "gk")

lua vim.keymap.set("x", "<c-s>", "<esc>:update<NL>gv")

lua vim.keymap.set("x", "p", "P")

lua <<EOT
function visual_surround(l_text, r_text)

	-- https://neovim.io/doc/user/api.html#nvim_replace_termcodes()
	-- https://neovim.io/doc/user/api.html#nvim_feedkeys()
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

lua require('abbrev')

" }}}

" {{{ Diff

" :help :set-termcap
" https://vi.stackexchange.com/a/2363
"execute "set <M-j>=\ej"
"execute "set <M-k>=\ek"
lua vim.keymap.set("n", "<M-Up>", "[c")
lua vim.keymap.set("n", "<M-Down>", "]c")

lua <<EOT
-- Change colorscheme to default when entering diff mode
local change_colors_in_diff = vim.api.nvim_create_augroup("change_colors_in_diff", { clear = true })

-- https://vi.stackexchange.com/a/13395
vim.api.nvim_create_autocmd({"VimEnter", "FilterWritePre"}, {
	group = change_colors_in_diff,
	pattern = { "*" },
	callback = function()
		if vim.o.diff and vim.cmd.colorscheme() ~= 'default' then
			vim.cmd.colorscheme('default')
		end
	end
})

-- https://vi.stackexchange.com/a/12852
vim.api.nvim_create_autocmd("OptionSet", {
	group = change_colors_in_diff,
	pattern = { "diff" },
	callback = function()
		if vim.o.diff and vim.cmd.colorscheme() ~= 'default' then
			vim.cmd.colorscheme('default')
		end
	end
})
EOT

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
-- https://www.lua.org/pil/8.4.html
-- https://stackoverflow.com/a/55109411/1892784
for i, c in ipairs(colorscheme_list) do
	if pcall(vim.cmd.colorscheme, c) then break end
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
