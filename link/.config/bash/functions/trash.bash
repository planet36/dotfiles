# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function trash
{
	printf 'Num. items removed: '
	#time nice -n 19 find "$TRASH_DIR" -mindepth 1 -print -delete | wc --lines
	time find "$TRASH_DIR" -mindepth 1 -print -delete | wc --lines
}

