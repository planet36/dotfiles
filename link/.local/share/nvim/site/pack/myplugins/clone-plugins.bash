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
PLUGINS_START+=('https://github.com/chrisbra/unicode.vim.git')
PLUGINS_START+=('https://github.com/ethanholz/nvim-lastplace.git')

declare -a PLUGINS_OPT

# color schemes
PLUGINS_OPT+=('https://github.com/srcery-colors/srcery-vim.git') # srcery
PLUGINS_OPT+=('https://github.com/vim-scripts/candycode.vim.git')
PLUGINS_OPT+=('https://github.com/fneu/breezy.git')
PLUGINS_OPT+=('https://github.com/mhartington/oceanic-next.git') # OceanicNext
PLUGINS_OPT+=('https://github.com/projekt0n/github-nvim-theme.git') # github_dark_default
PLUGINS_OPT+=('https://github.com/morhetz/gruvbox.git')
#PLUGINS_OPT+=('https://github.com/EvitanRelta/vim-colorschemes.git')

mkdir --verbose --parents -- start
cd start || exit
echo "# in start/"
echo

for PLUGIN in "${PLUGINS_START[@]}"
do
	declare -l DIR="$(basename --suffix .git -- "$PLUGIN")"
	echo "# cloning $DIR"

	if [[ ! -d "$DIR" ]]
	then
		git clone --quiet -- "$PLUGIN" || break
	else
		echo "(already exists)"
	fi

	echo
done

cd - > /dev/null || exit

mkdir --verbose --parents -- opt
cd opt || exit
echo "# in opt/"
echo

for PLUGIN in "${PLUGINS_OPT[@]}"
do
	declare -l DIR="$(basename --suffix .git -- "$PLUGIN")"
	echo "# cloning $DIR"

	if [[ ! -d "$DIR" ]]
	then
		git clone --quiet -- "$PLUGIN" || break
	else
		echo "(already exists)"
	fi

	echo
done

cd - > /dev/null || exit
