-- SPDX-FileCopyrightText: Steven Ward
-- SPDX-License-Identifier: OSL-3.0

-- Stop the highlighting for the 'hlsearch' option.
vim.keymap.set("n", "<Leader><space>", function() vim.cmd.nohlsearch() end)

-- Replace selected text.
vim.keymap.set("x", "<C-r>", [[y:%s/<C-r>"//gc<left><left><left>]])

-- Use \V, and escape slashes in the selected text before replacing.
vim.keymap.set("x", "<C-e>", [[y:%s/\V<C-r>=escape(@", '/\')<NL>//gc<left><left><left>]])

vim.keymap.set("n", "<Leader>h", function() vim.cmd.split() end)
vim.keymap.set("n", "<Leader>v", function() vim.cmd.vsplit() end)

-- Go to next/previous buffer
vim.keymap.set("n", "<C-n>", function() vim.cmd.bnext() end)
vim.keymap.set("n", "<C-p>", function() vim.cmd.bprevious() end)

-- Moving cursor to other windows

vim.keymap.set("n", "<C-h>", "<C-w>h")
vim.keymap.set("n", "<C-j>", "<C-w>j")
vim.keymap.set("n", "<C-k>", "<C-w>k")
vim.keymap.set("n", "<C-l>", "<C-w>l")

-- Window resizing

-- window width -1
vim.keymap.set("n", "<F6>", function() vim.cmd("vertical resize -1") end)

-- window height -1
vim.keymap.set("n", "<F7>", function() vim.cmd.resize("-1") end)

-- window height +1
vim.keymap.set("n", "<F8>", function() vim.cmd.resize("+1") end)

-- window width +1
vim.keymap.set("n", "<F9>", function() vim.cmd("vertical resize +1") end)

vim.keymap.set("i", "jj", "<esc>")
vim.keymap.set({"n", "x"}, "H", "0")
vim.keymap.set({"n", "x"}, "L", "$")

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
	local reg_info = vim.fn.getreginfo("/")
	vim.cmd([[%s/\v\s+$//e]])
	-- / is the last search pattern register
	vim.fn.setreg("/", reg_info)
	vim.api.nvim_win_set_cursor(0, cursor_pos)
end

-- remove trailing whitespace.
vim.keymap.set("n", "<Leader>S", function() remove_trailing_whitespace() end)

-- Highlight trailing whitespace.
vim.keymap.set("n", "<Leader>w", function() vim.cmd.match("ErrorMsg", [[/\v\s+$/]]) end)
vim.keymap.set("n", "<Leader>W", function() vim.cmd.match("none") end)

-- Highlight text beyond 80 columns.
vim.keymap.set("n", "<Leader>c", function() vim.cmd([[2match ErrorMsg /\v%>80v.+/]]) end)
vim.keymap.set("n", "<Leader>C", function() vim.cmd("2match none") end)

vim.keymap.set("n", "<Leader>ev", function() vim.cmd.vsplit(vim.env.MYVIMRC) end)
vim.keymap.set("n", "<Leader>sv", function() vim.cmd.source(vim.env.MYVIMRC) end)

vim.keymap.set("x", "p", "P")

function visual_surround(l_text, r_text)

	-- https://neovim.io/doc/user/api.html#nvim_replace_termcodes()
	-- https://neovim.io/doc/user/api.html#nvim_feedkeys()
	local esc = vim.api.nvim_replace_termcodes("<Esc>", true, false, true)
	local cntrl_v = vim.api.nvim_replace_termcodes("<C-v>", true, false, true)
	local mode = vim.fn.mode()

	if mode == "v" or mode == "V" then -- visual or visual line
		vim.api.nvim_feedkeys(esc .. "'>a" .. r_text .. esc .. "'<i" .. l_text, "x", false)
	elseif mode == cntrl_v then -- visual block
		vim.api.nvim_feedkeys("A" .. r_text .. esc .. "gvI" .. l_text, "x", false)
	end
end

vim.keymap.set("x", "<Leader>`", function() visual_surround("`", "`") end)
vim.keymap.set("x", "<Leader>'", function() visual_surround("'", "'") end)
vim.keymap.set("x", '<Leader>"', function() visual_surround('"', '"') end)
vim.keymap.set("x", "<Leader>(", function() visual_surround("(", ")") end)
vim.keymap.set("x", "<Leader>[", function() visual_surround("[", "]") end)
vim.keymap.set("x", "<Leader>{", function() visual_surround("{", "}") end)
vim.keymap.set("x", "<Leader><", function() visual_surround("<", ">") end)
vim.keymap.set("x", "<Leader>*", function() visual_surround("/*", "*/") end)

vim.keymap.set("n", "<M-Up>", "[c")
vim.keymap.set("n", "<M-Down>", "]c")