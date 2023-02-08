# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function t-code
{
	cd || return
	clean code || return
	find code -type f \( -name '*.out' -o -name core -o -regex '.*/core\.[0-9]+' \) -delete || return
	t code || return
	command xz --verbose -9 -e code.tar || return
	mv code.tar.xz Downloads/ || return
	cd Downloads/ || return
	printf 'del code.tar.xz && exit\n'
}
