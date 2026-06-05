-- SPDX-FileCopyrightText: Steven Ward
-- SPDX-License-Identifier: MPL-2.0

-- vim: set foldmethod=marker:

-- {{{ Turn off provider warnings

vim.g.loaded_ruby_provider = 0
vim.g.loaded_node_provider = 0
vim.g.loaded_perl_provider = 0

-- }}}

-- {{{ Clipboard

-- This option is a list of comma separated names.
vim.opt.clipboard:append({ 'unnamedplus' })

-- }}}

-- {{{ Backup files & directory, swap directory, undo files & directory

vim.o.backup = true

vim.o.undofile = true

vim.opt.backupdir:remove({ '.' })

vim.api.nvim_create_autocmd('BufWritePre', {
  group = vim.api.nvim_create_augroup('backup_extension_timestamp', {}),
  pattern = { '*' },
  callback = function()
    -- String which is appended to a file name to make the name of the backup file.
    vim.o.backupext = '~' .. os.date('%Y%m%dT%H%M%S') .. '~'
  end,
})

-- }}}

-- {{{ Include path

vim.opt.path:append({ vim.fs.normalize('~/.local/include') })

-- }}}

-- {{{ ignore case when completing file names and directories

vim.o.fileignorecase = true
vim.o.wildignorecase = true

-- }}}

-- {{{ Line numbers

vim.o.number = true

-- }}}

-- {{{ File type

vim.api.nvim_create_autocmd({ 'BufRead', 'BufNewFile' }, {
  pattern = { '*.cal' },
  callback = function() vim.o.filetype = 'c' end,
})

vim.api.nvim_create_autocmd({ 'BufRead', 'BufNewFile' }, {
  pattern = { '*.fish' },
  callback = function() vim.o.filetype = 'sh' end,
})

-- }}}

-- {{{ Syntax highlighting

-- :help syn-sync
vim.cmd.syntax('sync', 'fromstart')

vim.o.termguicolors = true

vim.g.c_comment_strings = 1
vim.g.c_space_errors = 1
vim.g.c_curly_error = 1
vim.g.c_minlines = 10000

-- :help doxygen-syntax
vim.g.load_doxygen_syntax = 1

-- WARNING: Uses italic fonts
--let g:doxygen_enhanced_color=1

vim.o.list = true

vim.opt.listchars:append({ trail = [[\u2423]] })

-- }}}

-- {{{ Indentation

vim.o.expandtab = true
vim.o.shiftwidth = 4

-- }}}

-- {{{ Formatting

-- :help cinoptions-values
vim.o.cinoptions = ':0,g0,N-s,E-s,t0,c0,C1'

-- :help fo-table
vim.opt.formatoptions:append('/p')

-- }}}

-- {{{ C/C++ block comments

vim.api.nvim_create_autocmd('FileType', {
  group = vim.api.nvim_create_augroup('c_cpp_block_comments', {}),
  pattern = { 'c,cpp' }, -- matched against filetype
  callback = function()
    -- :help format-comments
    vim.o.comments = string.gsub(vim.o.comments, 's1:', 's:')
  end,
})

-- }}}

-- {{{ Searching

vim.o.wrapscan = false
vim.o.ignorecase = true
vim.o.smartcase = true

-- }}}

-- {{{ Auto-complete

--vim.o.autocomplete = true

-- }}}

-- {{{ Disable mouse support if inside tmux

if vim.env.TMUX ~= nil then vim.o.mouse = '' end

-- }}}

-- {{{ UI

vim.o.whichwrap = '<,>,[,]'
vim.opt.matchpairs:append({ '<:>' })
vim.o.scrolloff = 6

-- }}}

-- {{{ Splitting

vim.o.splitbelow = true
vim.o.splitright = true

-- }}}

-- {{{ Windows

-- Open help window in a vertical split to the right.
vim.api.nvim_create_autocmd('BufWinEnter', {
  group = vim.api.nvim_create_augroup('help_window_right', {}),
  pattern = { '*.txt' },
  callback = function()
    if vim.o.filetype == 'help' then vim.cmd.wincmd('L') end
  end,
})

-- }}}

-- {{{ Automatically enable spell check in git editor

vim.api.nvim_create_autocmd('FileType', {
  pattern = 'gitcommit',
  callback = function() vim.opt_local.spell = true end,
})

-- }}}

-- {{{ Folding

vim.o.foldmethod = 'marker'
vim.o.foldlevelstart = 99

-- }}}

-- {{{ Maps

require('map')

-- }}}

-- {{{ Abbreviations

require('abbrev')

-- }}}

-- {{{ Command to start Python 3

vim.g.python3_host_prog = '/usr/bin/python3'

-- }}}

-- {{{ Plugins

-- https://neovim.io/doc/user/pack/

-- :help vim.pack.add()
-- https://neovim.io/doc/user/pack/#vim.pack.add()
vim.pack.add({
  'https://github.com/AndrewRadev/linediff.vim',
  'https://github.com/chrisbra/unicode.vim',
  'https://github.com/godlygeek/tabular',
  'https://github.com/junegunn/fzf.vim',
  'https://github.com/nvim-lualine/lualine.nvim',
  --'https://github.com/tpope/vim-sensible'
  'https://github.com/tzachar/highlight-undo.nvim',

  -- color schemes
  --'https://github.com/EvitanRelta/vim-colorschemes',
  --'https://github.com/fneu/breezy',
  --'https://github.com/mhartington/oceanic-next', -- OceanicNext
  --'https://github.com/morhetz/gruvbox',
  --'https://github.com/projekt0n/github-nvim-theme', -- github_dark_default
  'https://github.com/srcery-colors/srcery-vim',
  --'https://github.com/vim-scripts/candycode.vim',
})

-- :help vim.pack.update()
-- https://neovim.io/doc/user/pack/#vim.pack.update()

-- Check health ":checkhealth vim.pack"

-- Show plugins ":lua vim.pack.update(nil, { offline = true })"

-- Update plugins ":lua vim.pack.update()"
--   (:quit to discard updates)
--   (:write to apply updates)

-- }}}

-- {{{ Color schemes

vim.o.cursorline = true

local colorscheme_list = {
  'srcery',
  --'candycode',
  --'breezy',
  --'OceanicNext',
  'retrobox',
  'wildcharm',
  'murphy',
}

-- https://www.lua.org/pil/7.3.html
-- https://www.lua.org/pil/8.4.html
-- https://stackoverflow.com/a/55109411/1892784
for i, c in ipairs(colorscheme_list) do
  if pcall(vim.cmd.colorscheme, c) then break end
end

-- https://github.com/srcery-colors/srcery-vim/blob/master/colors/srcery.vim#L37
-- Use yellow instead of bright magenta
local srcery_yellow = '#FBB829'
vim.cmd.highlight('Boolean', 'guifg=' .. srcery_yellow)
vim.cmd.highlight('Constant', 'guifg=' .. srcery_yellow)
vim.cmd.highlight('Float', 'guifg=' .. srcery_yellow)
vim.cmd.highlight('Number', 'guifg=' .. srcery_yellow)

-- }}}

-- {{{ highlight-undo plugin

-- Copied from:
-- https://github.com/tzachar/highlight-undo.nvim#setup

require('highlight-undo').setup({})

-- }}}

-- {{{ Statusline plugin

require('lualine').setup({
  options = {
    theme = 'codedark',
  },
  sections = {
    lualine_a = {
      {
        'mode',
        fmt = function(str) return str:sub(1, 3) end,
      },
    },
    lualine_c = {
      {
        'filename',
        path = 1,
        symbols = {
          readonly = '[RO]',
        },
      },
    },
  },
  inactive_sections = {
    lualine_c = {
      {
        'filename',
        path = 1,
        symbols = {
          readonly = '[RO]',
        },
      },
    },
  },
})

-- }}}
