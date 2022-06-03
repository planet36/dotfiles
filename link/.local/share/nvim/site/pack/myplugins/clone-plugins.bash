#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck disable=SC2034

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

cd "$SCRIPT_DIR" || exit

declare -a PLUGINS_START

PLUGINS_START+=('https://github.com/junegunn/fzf.vim.git')
#PLUGINS_START+=('https://github.com/tpope/vim-sensible.git')
PLUGINS_START+=('https://github.com/godlygeek/tabular.git')
PLUGINS_START+=('https://github.com/AndrewRadev/linediff.vim.git')

declare -a PLUGINS_OPT

PLUGINS_OPT+=('https://github.com/chrisbra/unicode.vim.git')

# color schemes
PLUGINS_OPT+=('https://github.com/srcery-colors/srcery-vim.git') # srcery
PLUGINS_OPT+=('https://github.com/vim-scripts/candycode.vim.git')
PLUGINS_OPT+=('https://github.com/fneu/breezy.git')
#PLUGINS_OPT+=('https://github.com/mhartington/oceanic-next.git') # OceanicNext
#PLUGINS_OPT+=('https://github.com/projekt0n/github-nvim-theme.git') # github_dark_default
#PLUGINS_OPT+=('https://github.com/morhetz/gruvbox.git')
#PLUGINS_OPT+=('https://github.com/flazz/vim-colorschemes.git')

mkdir --verbose --parents -- start
cd start || exit

for PLUGIN in "${PLUGINS_START[@]}"
do
	echo "$PLUGIN"
	git clone --quiet -- "$PLUGIN"
done

cd - > /dev/null

mkdir --verbose --parents -- opt
cd opt || exit

for PLUGIN in "${PLUGINS_OPT[@]}"
do
	echo "$PLUGIN"
	git clone --quiet -- "$PLUGIN"
done

cd - > /dev/null
