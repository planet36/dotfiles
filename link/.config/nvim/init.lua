-- SPDX-FileCopyrightText: Steven Ward
-- SPDX-License-Identifier: OSL-3.0

-- vim: set foldmethod=marker:

-- {{{ Turn off provider warnings

vim.g.loaded_ruby_provider = 0
vim.g.loaded_node_provider = 0
vim.g.loaded_perl_provider = 0

-- }}}

-- {{{ Clipboard

-- This option is a list of comma separated names.
vim.opt.clipboard:append { "unnamedplus" }

-- }}}

-- {{{ Backup files & directory, swap directory, undo files & directory

vim.o.backup = true

vim.o.undofile = true

vim.opt.backupdir:remove { "." }

vim.api.nvim_create_autocmd("BufWritePre", {
	group = vim.api.nvim_create_augroup("backup_extension_timestamp", {}),
	pattern = { "*" },
	callback = function()
		-- String which is appended to a file name to make the name of the backup file.
		vim.o.backupext = "~" .. os.date("%Y%m%dT%H%M%S") .. "~"
	end
})

-- }}}

-- {{{ Include path

vim.opt.path:append { vim.fs.normalize("~/.local/include") }

-- }}}

-- {{{ ignore case when completing file names and directories

vim.o.fileignorecase = true
vim.o.wildignorecase = true

-- }}}

-- {{{ Line numbers

vim.o.number = true

-- }}}

-- {{{ File type

vim.api.nvim_create_autocmd({"BufRead","BufNewFile"}, {
	pattern = {"*.cal"},
	callback = function() vim.o.filetype = "c" end
})

vim.api.nvim_create_autocmd({"BufRead","BufNewFile"}, {
	pattern = {"*.fish"},
	callback = function() vim.o.filetype = "sh" end
})

-- }}}

-- {{{ Syntax highlighting

-- :help syn-sync
vim.cmd.syntax("sync", "fromstart")

vim.o.termguicolors = true

vim.g.c_comment_strings = 1
vim.g.c_space_errors = 1
vim.g.c_curly_error = 1
vim.g.c_minlines = 200

-- :help doxygen-syntax
vim.g.load_doxygen_syntax = 1

-- WARNING: Uses italic fonts
--let g:doxygen_enhanced_color=1

vim.o.list = true

vim.opt.listchars:append { trail = [[\u2423]]}

-- }}}

-- {{{ Indentation

vim.o.shiftwidth=4
vim.o.softtabstop=4
vim.o.tabstop=4

-- }}}

-- {{{ Formatting

-- :help cinoptions-values
vim.o.cinoptions = ":0,g0,N-s,E-s,t0,c0,C1"

-- :help fo-/
vim.opt.formatoptions:append { "/" }

-- :help fo-p
vim.opt.formatoptions:append { "p" }

-- }}}

-- {{{ C/C++ block comments

vim.api.nvim_create_autocmd("FileType", {
	group = vim.api.nvim_create_augroup("c_cpp_block_comments", {}),
	pattern = { "c,cpp" }, -- matched against filetype
	callback = function()
		-- :help format-comments
		vim.o.comments = string.gsub(vim.o.comments, "s1:", "s:")
	end
})

-- }}}

-- {{{ Searching

vim.o.wrapscan = false
vim.o.ignorecase = true
vim.o.smartcase = true

-- }}}

-- {{{ Disable mouse support if inside tmux

if vim.env.TMUX ~= nil then vim.o.mouse = "" end

-- }}}

-- {{{ UI

vim.o.whichwrap = "<,>,[,]"
vim.opt.matchpairs:append { "<:>" }
vim.o.scrolloff = 6

-- }}}

-- {{{ Splitting

vim.o.splitbelow = true
vim.o.splitright = true

-- }}}

-- {{{ Windows

-- Open help window in a vertical split to the right.
vim.api.nvim_create_autocmd("BufWinEnter", {
	group = vim.api.nvim_create_augroup("help_window_right", {}),
	pattern = { "*.txt" },
	callback = function()
		if vim.o.filetype == "help" then vim.cmd.wincmd("L") end
	end
})

-- }}}

-- {{{ Folding

vim.o.foldmethod = "marker"
vim.o.foldlevelstart = 99

-- }}}

-- {{{ Maps

require("map")

-- }}}

-- {{{ Abbreviations

require("abbrev")

-- }}}

-- {{{ Diff

function get_colorscheme()
	-- https://neovim.io/doc/user/api.html#nvim_exec2()
	-- XXX: vim.cmd.colorscheme() prints (not returns) the current colorscheme.
	return vim.api.nvim_exec2("colorscheme", {output = true}).output
end

-- Count the windows in the current tabpage for which diff is true.
function count_tabpage_windows_diffed()
	-- https://neovim.io/doc/user/api.html#nvim_tabpage_list_wins()
	-- https://neovim.io/doc/user/api.html#nvim_win_get_option()

	local windows_diffed = 0

	for i, win_hndl in ipairs(vim.api.nvim_tabpage_list_wins(0)) do
		if vim.api.nvim_win_get_option(win_hndl, "diff") then
			windows_diffed = windows_diffed + 1
		end
	end

	return windows_diffed
end

-- https://vi.stackexchange.com/questions/39637/detect-when-a-diff-begins-and-ends
-- Change colorscheme when diff mode begins/ends.
function handle_diff_change_colorscheme()

	local num_windows_diffed = count_tabpage_windows_diffed()

	if num_windows_diffed > 1 then
		if get_colorscheme() ~= vim.g.diff_colorscheme then
			vim.cmd.colorscheme(vim.g.diff_colorscheme)
		end
	else
		if get_colorscheme() ~= vim.g.orig_colorscheme then
			vim.cmd.colorscheme(vim.g.orig_colorscheme)
		end
	end
end

local change_colors_in_diff = vim.api.nvim_create_augroup("change_colors_in_diff", {})

vim.api.nvim_create_autocmd("ColorScheme", {
	group = change_colors_in_diff,
	pattern = { "*" },
	callback = function() vim.g.orig_colorscheme = get_colorscheme() end
})

-- https://vi.stackexchange.com/a/13395
vim.api.nvim_create_autocmd({"VimEnter",
	"BufWinEnter", "BufWinLeave", "TabEnter", "TabLeave"}, {
	group = change_colors_in_diff,
	pattern = { "*" },
	callback = function() handle_diff_change_colorscheme() end
})

-- https://vi.stackexchange.com/a/12852
vim.api.nvim_create_autocmd("OptionSet", {
	group = change_colors_in_diff,
	pattern = { "diff" },
	callback = function() handle_diff_change_colorscheme() end
})

-- :help DiffOrig
vim.api.nvim_create_user_command("DiffOrig",
"vert new | set buftype=nofile | read ++edit # | 0d_ | diffthis | wincmd p | diffthis", {})

-- }}}

-- {{{ Command to start Python 3

vim.g.python3_host_prog = "/usr/bin/python3"

-- }}}

-- {{{ Color schemes

vim.o.cursorline = true

local colorscheme_list = {
	"srcery",
	"candycode",
	"breezy",
	"OceanicNext",
	"github_dark_default",
	"gruvbox",
	"murphy",
}

-- https://www.lua.org/pil/7.3.html
-- https://www.lua.org/pil/8.4.html
-- https://stackoverflow.com/a/55109411/1892784
for i, c in ipairs(colorscheme_list) do
	if pcall(vim.cmd.colorscheme, c) then break end
end

vim.g.orig_colorscheme = get_colorscheme()
vim.g.diff_colorscheme = "murphy"

-- https://github.com/srcery-colors/srcery-vim/blob/master/autoload/srcery.vim#L17
-- https://github.com/srcery-colors/srcery-vim/blob/master/colors/srcery.vim#L352
-- Use yellow instead of bright magenta
vim.cmd.highlight("Constant", "guifg=#FBB829")
vim.cmd.highlight("Character", "guifg=#FBB829")
vim.cmd.highlight("Boolean", "guifg=#FBB829")
vim.cmd.highlight("Number", "guifg=#FBB829")
vim.cmd.highlight("Float", "guifg=#FBB829")

-- }}}
