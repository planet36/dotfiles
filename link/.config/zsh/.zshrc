
# {{{ XDG vars

setup_xdg_vars() {

    # https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html

    : "${XDG_CACHE_HOME:=$HOME/.cache}"
    : "${XDG_CONFIG_DIRS:=/etc/xdg}"
    : "${XDG_CONFIG_HOME:=$HOME/.config}"
    : "${XDG_DATA_DIRS:=/usr/local/share/:/usr/share/}"
    : "${XDG_DATA_HOME:=$HOME/.local/share}"

    export XDG_CACHE_HOME
    export XDG_CONFIG_DIRS
    export XDG_CONFIG_HOME
    export XDG_DATA_DIRS
    export XDG_DATA_HOME

    mkdir --verbose --parents -- "$XDG_CACHE_HOME"
    mkdir --verbose --parents -- "$XDG_CONFIG_HOME"
    mkdir --verbose --parents -- "$XDG_DATA_HOME"
}

setup_xdg_vars

# }}}

if [[ ! -d "$XDG_DATA_HOME"/zsh ]]
then
    mkdir --verbose --parents -- "$XDG_DATA_HOME"/zsh
fi


# Lines configured by zsh-newuser-install
HISTFILE="$XDG_DATA_HOME"/zsh/history
HISTSIZE=9999
SAVEHIST=9999
setopt autocd extendedglob
unsetopt beep notify
bindkey -e
# End of lines configured by zsh-newuser-install

# {{{ man zshoptions

# Changing Directories
setopt AUTO_CD

# Completion
setopt ALWAYS_TO_END
setopt AUTO_LIST
setopt AUTO_MENU
setopt MENU_COMPLETE

# Expansion and Globbing
setopt BAD_PATTERN
setopt NO_CASE_GLOB
setopt GLOB_DOTS
setopt MARK_DIRS
setopt NOMATCH
setopt NUMERIC_GLOB_SORT
setopt RC_EXPAND_PARAM
setopt WARN_CREATE_GLOBAL
#setopt WARN_NESTED_VAR

# History
setopt APPEND_HISTORY
setopt EXTENDED_HISTORY
setopt HIST_EXPIRE_DUPS_FIRST
setopt HIST_FCNTL_LOCK
setopt HIST_FIND_NO_DUPS
setopt HIST_IGNORE_ALL_DUPS
setopt HIST_NO_FUNCTIONS
setopt HIST_NO_STORE
setopt HIST_REDUCE_BLANKS
setopt HIST_SAVE_NO_DUPS
setopt HIST_VERIFY
setopt SHARE_HISTORY

# Input/Output
setopt NO_CLOBBER
setopt CORRECT
setopt CORRECT_ALL
setopt INTERACTIVE_COMMENTS
setopt PRINT_EXIT_VALUE
setopt RC_QUOTES
setopt RM_STAR_WAIT

# Prompting
setopt PROMPT_SUBST

# }}}



# {{{ man zshparam


# double precision float, fixed notation
typeset -F SECONDS





# }}}










# {{{ key bindings

# https://wiki.archlinux.org/index.php/Zsh#Key_bindings

# create a zkbd compatible hash;
# to add other keys to this hash, see: man 5 terminfo
typeset -g -A key

key[Home]="${terminfo[khome]}"
key[End]="${terminfo[kend]}"
key[Insert]="${terminfo[kich1]}"
key[Backspace]="${terminfo[kbs]}"
key[Delete]="${terminfo[kdch1]}"
key[Up]="${terminfo[kcuu1]}"
key[Down]="${terminfo[kcud1]}"
key[Left]="${terminfo[kcub1]}"
key[Right]="${terminfo[kcuf1]}"
key[PageUp]="${terminfo[kpp]}"
key[PageDown]="${terminfo[knp]}"
key[Shift-Tab]="${terminfo[kcbt]}"

# setup key accordingly
[[ -n "${key[Home]}"      ]] && bindkey -- "${key[Home]}"      beginning-of-line
[[ -n "${key[End]}"       ]] && bindkey -- "${key[End]}"       end-of-line
[[ -n "${key[Insert]}"    ]] && bindkey -- "${key[Insert]}"    overwrite-mode
[[ -n "${key[Backspace]}" ]] && bindkey -- "${key[Backspace]}" backward-delete-char
[[ -n "${key[Delete]}"    ]] && bindkey -- "${key[Delete]}"    delete-char
[[ -n "${key[Up]}"        ]] && bindkey -- "${key[Up]}"        up-line-or-history
[[ -n "${key[Down]}"      ]] && bindkey -- "${key[Down]}"      down-line-or-history
[[ -n "${key[Left]}"      ]] && bindkey -- "${key[Left]}"      backward-char
[[ -n "${key[Right]}"     ]] && bindkey -- "${key[Right]}"     forward-char
[[ -n "${key[PageUp]}"    ]] && bindkey -- "${key[PageUp]}"    beginning-of-buffer-or-history
[[ -n "${key[PageDown]}"  ]] && bindkey -- "${key[PageDown]}"  end-of-buffer-or-history
[[ -n "${key[Shift-Tab]}" ]] && bindkey -- "${key[Shift-Tab]}" reverse-menu-complete

# Finally, make sure the terminal is in application mode, when zle is
# active. Only then are the values from $terminfo valid.
if (( ${+terminfo[smkx]} && ${+terminfo[rmkx]} )); then
    autoload -Uz add-zle-hook-widget
    function zle_application_mode_start { echoti smkx }
    function zle_application_mode_stop { echoti rmkx }
    add-zle-hook-widget -Uz zle-line-init zle_application_mode_start
    add-zle-hook-widget -Uz zle-line-finish zle_application_mode_stop
fi

key[Control-Left]="${terminfo[kLFT5]}"
key[Control-Right]="${terminfo[kRIT5]}"

[[ -n "${key[Control-Left]}"  ]] && bindkey -- "${key[Control-Left]}"  backward-word
[[ -n "${key[Control-Right]}" ]] && bindkey -- "${key[Control-Right]}" forward-word

# }}}






# {{{ z

export _Z_CMD=j
export _Z_DATA="${XDG_CACHE_HOME}"/z-data
[[ -r "/usr/share/z/z.sh" ]] && source /usr/share/z/z.sh

# }}}

# {{{ command correction

if command -v zoxide > /dev/null
then
    # https://github.com/nvbn/thefuck/wiki/Shell-aliases
    eval "$(thefuck --alias)"
fi

# }}}


# zsh -f /usr/share/zsh/functions/Misc/zkbd

if [[ -f ${ZDOTDIR}/.zkbd/$TERM-${${DISPLAY:t}:-$VENDOR-$OSTYPE} ]] ; then
    source ${ZDOTDIR}/.zkbd/$TERM-${${DISPLAY:t}:-$VENDOR-$OSTYPE}
fi

#if   [[ -f ~/.zkbd/${TERM}-${VENDOR}-${OSTYPE} ]] ; then
#    source ~/.zkbd/${TERM}-${VENDOR}-${OSTYPE}
#
#elif [[ -f ~/.zkbd/${TERM}-${DISPLAY} ]] ; then
#    source ~/.zkbd/${TERM}-${DISPLAY}
#fi

if [[ -f   /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh ]] ; then
    source /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh
fi

# This must be last
if [[ -f   /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh ]] ; then
    source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh
fi

