# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# vim: set foldmethod=marker foldlevel=0:

if test -f (status dirname)/envvars.fish
    source (status dirname)/envvars.fish
end

if test -f (status dirname)/private-envvars.fish
    source (status dirname)/private-envvars.fish
end

# {{{ interactive shell

if status is-interactive

# {{{ prevent st unknown escape sequence

# https://github.com/fish-shell/fish-shell/issues/3425
if string match --quiet "st-*" "$TERM"
    set --erase VTE_VERSION
    # fixed by (2021-10-14)
    # https://github.com/fish-shell/fish-shell/commit/6606dfbeb5e65e1f9d1b900248e02dea6690d48c
    bind \e\[P delete-char
end

# }}}

# {{{ env_parallel

if command --quiet env_parallel
    source (which env_parallel.fish)
end

# }}}

# {{{ z

set Z_CMD "j"
#set ZO_CMD "$Z_CMD"o

# }}}

# {{{ source other config files

if test -f (status dirname)/abbrs.fish
    source (status dirname)/abbrs.fish
end

if test -f (status dirname)/aliases.fish
    source (status dirname)/aliases.fish
end

# }}}

end # status is-interactive

# }}}
