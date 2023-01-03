-- Stop the highlighting for the 'hlsearch' option.
vim.keymap.set("n", "<Leader><space>", ":nohlsearch<NL>")

-- Replace selected text.
vim.keymap.set("x", "<C-r>", [[y:%s/<C-r>"//gc<left><left><left>]])

-- Use \V, and escape slashes in the selected text before replacing.
vim.keymap.set("x", "<C-e>", [[y:%s/\V<C-r>=escape(@", '/\')<NL>//gc<left><left><left>]])

vim.keymap.set("n", "<Leader>h", ":split<NL>")
vim.keymap.set("n", "<Leader>v", ":vsplit<NL>")

-- Moving cursor to other windows

vim.keymap.set("n", "<C-h>", "<C-w>h")
vim.keymap.set("n", "<C-j>", "<C-w>j")
vim.keymap.set("n", "<C-k>", "<C-w>k")
vim.keymap.set("n", "<C-l>", "<C-w>l")

-- Window resizing

-- window width -1
vim.keymap.set("n", "<F6>", ":vertical resize -1<NL>")

-- window height -1
vim.keymap.set("n", "<F7>", ":resize -1<NL>")

-- window height +1
vim.keymap.set("n", "<F8>", ":resize +1<NL>")

-- window width +1
vim.keymap.set("n", "<F9>", ":vertical resize +1<NL>")

vim.keymap.set("i", "jj", "<esc>")
vim.keymap.set({"n", "x"}, "H", "0")
vim.keymap.set({"n", "x"}, "L", "$")
vim.keymap.set("i", "<c-d>", "<esc>ddi")
vim.keymap.set("i", "<c-s>", "<c-o>:update<NL>")

-- Complete whole filenames/lines with a quicker shortcut key in insert mode
vim.keymap.set("i", "<C-f>", "<C-x><C-f>")
vim.keymap.set("i", "<C-l>", "<C-x><C-l>")

vim.keymap.set({"n", "x"}, "<tab>", "%")

-- g; only available with |+jumplist| feature
-- Insert newline after cursor
vim.keymap.set("n", "K", "i<NL><esc>g")

-- save my left pinky
vim.keymap.set({"n", "x"}, "<space>", ":")

vim.keymap.set({"n", "x"}, "<down>", "gj")
vim.keymap.set({"n", "x"}, "<up>", "gk")

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

-- remove trailing whitespace.
vim.keymap.set("n", "<Leader>S", function() remove_trailing_whitespace() end)

-- Highlight trailing whitespace.
vim.keymap.set("n", "<Leader>w", [[:match ErrorMsg /\v\s+$/<NL>]])
vim.keymap.set("n", "<Leader>W", ":match none<NL>")

-- Highlight text beyond 80 columns.
vim.keymap.set("n", "<Leader>c", [[:2match ErrorMsg /\v%>80v.+/<NL>]])
vim.keymap.set("n", "<Leader>C", ":2match none<NL>")

vim.keymap.set("n", "<Leader>ev", ":vsplit $MYVIMRC<NL>")
vim.keymap.set("n", "<Leader>sv", ":source $MYVIMRC<NL>")

-- :help CTRL-^
vim.keymap.set("n", "<leader><leader>", "<c-^>")

-- double quote a word
-- single quote a word
vim.keymap.set("n", [[<Leader>"]], [[viW<esc>a"<esc>Bi"<esc>]])
vim.keymap.set("n", [[<Leader>']], [[viW<esc>a'<esc>Bi'<esc>]])

vim.keymap.set("n", "<Leader>g", [[:execute "grep! --recursive " . shellescape(expand("<cWORD>")) . " ."<NL>:copen<NL>]])

vim.keymap.set("x", "<c-s>", "<esc>:update<NL>gv")

vim.keymap.set("x", "p", "P")

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

vim.keymap.set("x", "<Leader>`", function() visual_surround("`", "`") end)
vim.keymap.set("x", "<Leader>'", function() visual_surround("'", "'") end)
vim.keymap.set("x", '<Leader>"', function() visual_surround('"', '"') end)
vim.keymap.set("x", "<Leader>(", function() visual_surround('(', ')') end)
vim.keymap.set("x", "<Leader>[", function() visual_surround('[', ']') end)
vim.keymap.set("x", "<Leader>{", function() visual_surround('{', '}') end)
vim.keymap.set("x", "<Leader><", function() visual_surround('<', '>') end)
vim.keymap.set("x", "<Leader>*", function() visual_surround('/*', '*/') end)

vim.keymap.set("n", "<M-Up>", "[c")
vim.keymap.set("n", "<M-Down>", "]c")
