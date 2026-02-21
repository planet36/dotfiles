# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# vim: set foldmethod=marker foldlevel=1:

# {{{ interactive shell

if status is-interactive

# {{{ Turn off fish greeting
set --global fish_greeting
# }}}

# {{{ Erase fish_command_not_found function
functions -e fish_command_not_found
# }}}

# {{{ Change ctrl-c key binding from clear-commandline to cancel-commandline

bind --user ctrl-c cancel-commandline

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

# {{{ Install fisher plugins

# To install fisher:
# curl -sL https://raw.githubusercontent.com/jorgebucaran/fisher/main/functions/fisher.fish | source && fisher install jorgebucaran/fisher
# https://github.com/jorgebucaran/fisher#installation

if functions --query fisher

    # {{{ Install z
    if not functions --query __z
        # https://github.com/jethrokuan/z#installation
        fisher install jethrokuan/z
    end
    # }}}

    # To remove all fisher plugins, run `fisher list | fisher remove`.

end # functions --query fisher

# }}}

# {{{ Configure z

# https://github.com/jethrokuan/z/blob/master/man/man1/z.md#configuration
set Z_CMD "j"
#set ZO_CMD "$Z_CMD"o

# }}}

# {{{ Choose theme

fish_config theme choose 'Dracula'

# }}}

# {{{ Choose prompt

fish_config prompt choose informative_vcs

# {{{ Configure git prompt
# https://fishshell.com/docs/current/cmds/fish_git_prompt.html
set __fish_git_prompt_showcolorhints 1
set __fish_git_prompt_showdirtystate 1
set __fish_git_prompt_showstashstate 1
set __fish_git_prompt_showuntrackedfiles 1
# }}}

# {{{ Change prompt chars
# https://github.com/fish-shell/fish-shell/blob/master/share/functions/fish_git_prompt.fish
# https://raw.githubusercontent.com/fish-shell/fish-shell/refs/heads/master/share/functions/fish_git_prompt.fish
set __fish_git_prompt_char_dirtystate '*'   # was U+271A HEAVY GREEK CROSS
set __fish_git_prompt_char_invalidstate '#' # was U+2716 HEAVY MULTIPLICATION X
set __fish_git_prompt_char_stagedstate '+'  # was U+25CF BLACK CIRCLE
set __fish_git_prompt_char_stashstate '$'   # was U+2691 BLACK FLAG
# }}}

# }}}

# {{{ Append every command into a separate history file
# https://fishshell.com/docs/current/language.html#:~:text=the%20first%20parameter.-,fish_postexec,-is%20emitted%20right
#function log_cmd_postexec --on-event fish_postexec --argument cmd
#  echo $(echo $cmd | string join '\\n') >> ~/.fish_history
#end
# }}}

# {{{ env_parallel

if command --quiet env_parallel
    source $(which env_parallel.fish)
end

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

end # status is-interactive

# }}}
