# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# vim: set foldmethod=marker foldlevel=0:

# {{{ interactive shell

if status is-interactive

# {{{ Turn off fish greeting
set --global fish_greeting
# }}}

# {{{ prevent st unknown escape sequence

# https://github.com/fish-shell/fish-shell/issues/3425
if string match --quiet "st-*" "$TERM"
    set --erase VTE_VERSION
end

# }}}

# {{{ Fix environment variables that have to be split when used interactively and unquoted.

# Fish does not split environment variables on whitespace.
# https://stackoverflow.com/a/51731126
# https://stackoverflow.com/a/47971956
set OPTIMIZE_OPTIONS  $(string split ' ' -- $OPTIMIZE_OPTIONS )
set DEBUG_OPTIONS     $(string split ' ' -- $DEBUG_OPTIONS    )
set PERF_TEST_OPTIONS $(string split ' ' -- $PERF_TEST_OPTIONS)
set PROFILE_OPTIONS   $(string split ' ' -- $PROFILE_OPTIONS  )

# }}}

# {{{ env_parallel

# https://bugs.archlinux.org/task/74292
#if command --quiet env_parallel
#    source $(which env_parallel.fish)
#end

# }}}

# {{{ Source other config files

if test -f $(status dirname)/abbrs.fish
    source $(status dirname)/abbrs.fish
end

if test -f $(status dirname)/aliases.fish
    source $(status dirname)/aliases.fish
end

if test -f $(status dirname)/private.fish
    source $(status dirname)/private.fish
end

# }}}

# {{{ Install fisher plugin

if not functions --query fisher
    # https://github.com/jorgebucaran/fisher#installation
    curl -sL https://raw.githubusercontent.com/jorgebucaran/fisher/main/functions/fisher.fish | source && fisher install jorgebucaran/fisher
end

# }}}

# {{{ Install fisher plugins

if functions --query fisher

    # {{{ Install z
    if not functions --query __z
        # https://github.com/jethrokuan/z#installation
        fisher install jethrokuan/z
    end
    # }}}

end # functions --query fisher

# }}}

# {{{ Configure z

# https://github.com/jethrokuan/z/blob/master/man/man1/z.md#configuration
set Z_CMD "j"
#set ZO_CMD "$Z_CMD"o

# }}}

# {{{ Choose theme

fish_config theme choose 'Tomorrow Night Bright'

# }}}

# {{{ Choose prompt

fish_config prompt choose informative_vcs

# }}}

end # status is-interactive

# }}}
