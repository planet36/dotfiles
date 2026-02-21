-- SPDX-FileCopyrightText: Steven Ward
-- SPDX-License-Identifier: MPL-2.0

-- Adapted from
-- https://github.com/neovim/neovim/commit/abd380e28d48dd155b1e29cd2453f13b28bf7e08

--- Gets the content of the visual selection.
---
--- The result is either a string or, if {list} is `true`, a list of strings.
--- If not in any |visual-mode|, `nil` is returned.
---
--- @param list boolean|nil
---        Return a list of strings instead of a string.  See |getreg()|.
---        Defaults to `false`.
--- @param append_empty boolean|nil
---        Append an empty string to the result when in |linewise-visual| mode and {list} is `true`.
---        This will preserve the trailing newline of the selection when the result is concatenated with `"\n"`.
---        Defaults to `false`.
--- @return string|table
function get_visual_selection(list, append_empty)
  list = list or false
  append_empty = append_empty or false

  local mode = vim.api.nvim_get_mode().mode
  if mode ~= 'v' and mode ~= 'V' and mode:byte() ~= 22 then return nil end

  local reg_name_unnamed = '"'
  local reg_name_yank = '0'

  local reg_info_unnamed = vim.fn.getreginfo(reg_name_unnamed)
  local reg_info_yank = vim.fn.getreginfo(reg_name_yank)
  local opt_clipboard = vim.o.clipboard
  local opt_report = vim.o.report

  vim.o.clipboard = ''
  vim.o.report = vim.v.maxcol

  vim.api.nvim_feedkeys('y', 'nx', false)

  local yanked = vim.fn.getreg(reg_name_yank, 1, list)

  vim.fn.setreg(reg_name_unnamed, reg_info_unnamed)
  vim.fn.setreg(reg_name_yank, reg_info_yank)
  vim.o.clipboard = opt_clipboard
  vim.o.report = opt_report

  if list and append_empty and mode == 'V' then table.insert(yanked, '') end

  return yanked
end
