# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash

# shellcheck disable=SC1090
# shellcheck disable=SC1091
# shellcheck disable=SC2034

BOLD=$(tput bold)
DIM=$(tput dim)
ITALIC=$(tput sitm)
RESET=$(tput sgr0)
REV=$(tput rev)
STANDOUT=$(tput smso)
UL=$(tput smul)

FG_BLACK=$(tput setaf 0)
FG_RED=$(tput setaf 1)
FG_GREEN=$(tput setaf 2)
FG_YELLOW=$(tput setaf 3)
FG_BLUE=$(tput setaf 4)
FG_MAGENTA=$(tput setaf 5)
FG_CYAN=$(tput setaf 6)
FG_WHITE=$(tput setaf 7)

BG_BLACK=$(tput setab 0)
BG_RED=$(tput setab 1)
BG_GREEN=$(tput setab 2)
BG_YELLOW=$(tput setab 3)
BG_BLUE=$(tput setab 4)
BG_MAGENTA=$(tput setab 5)
BG_CYAN=$(tput setab 6)
BG_WHITE=$(tput setab 7)

:<<EOT

S='O|'
clear
echo -e "BOLD     ${S}${BOLD}${S}${RESET}"; \
echo -e "DIM      ${S}${DIM}${S}${RESET}"; \
echo -e "ITALIC   ${S}${ITALIC}${S}${RESET}"; \
echo -e "RESET    ${S}${RESET}${S}${RESET}"; \
echo -e "REV      ${S}${REV}${S}${RESET}"; \
echo -e "STANDOUT ${S}${STANDOUT}${S}${RESET}"; \
echo -e "UL       ${S}${UL}${S}${RESET}"; \
echo -e "BOLD        UL ${S}${BOLD}${UL}${S}${RESET}"; \
echo -e "BOLD ITALIC    ${S}${BOLD}${ITALIC}${S}${RESET}"; \
echo -e "     ITALIC UL ${S}${ITALIC}${UL}${S}${RESET}"; \
echo -e "BOLD ITALIC UL ${S}${BOLD}${ITALIC}${UL}${S}${RESET}"; \
echo

S='XXX'

for COLOR in  \
"$FG_BLACK" \
"$FG_RED" \
"$FG_GREEN" \
"$FG_YELLOW" \
"$FG_BLUE" \
"$FG_MAGENTA" \
"$FG_CYAN" \
"$FG_WHITE" \
"$BG_BLACK" \
"$BG_RED" \
"$BG_GREEN" \
"$BG_YELLOW" \
"$BG_BLUE" \
"$BG_MAGENTA" \
"$BG_CYAN" \
"$BG_WHITE"
do
echo -e "BOLD     ${COLOR}${S}${BOLD}${S}${RESET}"; \
echo -e "DIM      ${COLOR}${S}${DIM}${S}${RESET}"; \
echo -e "ITALIC   ${COLOR}${S}${ITALIC}${S}${RESET}"; \
echo -e "RESET    ${COLOR}${S}${RESET}${S}${RESET}"; \
echo -e "REV      ${COLOR}${S}${REV}${S}${RESET}"; \
echo -e "STANDOUT ${COLOR}${S}${STANDOUT}${S}${RESET}"; \
echo -e "UL       ${COLOR}${S}${UL}${S}${RESET}"; \
echo -e "BOLD        UL ${COLOR}${S}${BOLD}${UL}${S}${RESET}"; \
echo -e "BOLD ITALIC    ${COLOR}${S}${BOLD}${ITALIC}${S}${RESET}"; \
echo -e "     ITALIC UL ${COLOR}${S}${ITALIC}${UL}${S}${RESET}"; \
echo -e "BOLD ITALIC UL ${COLOR}${S}${BOLD}${ITALIC}${UL}${S}${RESET}"; \
echo
done

EOT

#export CMD_TIMER=1

# https://wiki.archlinux.org/index.php/Bash/Prompt_customization#Embedding_commands

function preexec_timer_begin
{
    if [[ ! -v CMD_TIMER ]]
    then
        return
    fi

    if [[ ! -v XDG_RUNTIME_DIR ]]
    then
        return
    fi

    local -r CMD_TIME_FILE="$XDG_RUNTIME_DIR/bash-prompt-time.$$"

    printf -- '%s' "$EPOCHREALTIME" > "$CMD_TIME_FILE"
}

function precmd_timer_end
{
    # If this is called before opt_ex_st, need to preserve the exit status of the previous command.
    local -r -i EXIT_STATUS=$?

    local TIME0
    local -r TIME1="$EPOCHREALTIME"

    local -r CMD_TIME_FILE="$XDG_RUNTIME_DIR/bash-prompt-time.$$"

    if [[ -r "$CMD_TIME_FILE" ]]
    then
        read -r TIME0 < "$CMD_TIME_FILE"
        rm --force -- "$CMD_TIME_FILE"

        #if [[ ! -v CMD_TIMER ]]
        #then
        #    return
        #fi

        local -r CMD_TIMER_RESULT="$(bc -l <<< "$TIME1 - $TIME0")"

        if [[ -n "$CMD_TIMER_RESULT" ]]
        then
            printf -- 'took %s ' "$CMD_TIMER_RESULT"
        fi
    fi

    return $EXIT_STATUS
}

function opt_ex_st
{
    local -r -i EXIT_STATUS=$?

    ((EXIT_STATUS != 0)) && printf -- '?%d ' "$EXIT_STATUS"
}

function opt_jobs
{
    # If this is called before opt_ex_st, need to preserve the exit status of the previous command.
    local -r -i EXIT_STATUS=$?

    #local -r -a JOBS=($(jobs -p))
    local -a JOBS
    readarray -t JOBS < <(jobs -p)

    #local -r -i NUM_JOBS=${#JOBS[@]}
    local -i NUM_JOBS
    NUM_JOBS=${#JOBS[@]}

    ((NUM_JOBS > 0)) && printf -- '[%d] ' "$NUM_JOBS"

    return $EXIT_STATUS
}

function opt_shlvl
{
    # If this is called before opt_ex_st, need to preserve the exit status of the previous command.
    local -r -i EXIT_STATUS=$?

    ((SHLVL > 1)) && printf -- '(%d) ' "$SHLVL"

    return $EXIT_STATUS
}


# PS0    The value of this parameter is expanded (see PROMPTING below) and displayed by interactive shells after reading a command and before the command is executed.
# shellcheck disable=SC2016
PS0='$(preexec_timer_begin)'

# PS1    The value of this parameter is expanded (see PROMPTING below) and used as the primary prompt string.  The default value is ``\s-\v\$ ''.
# https://stackoverflow.com/a/24716445/1892784
PS1=''
PS1+='$(precmd_timer_end)'
PS1+='\[${BOLD}${FG_RED}\]$(opt_ex_st)\[${RESET}\]'
PS1+='\[${BOLD}${FG_MAGENTA}\]$(opt_jobs)\[${RESET}\]'
PS1+='\[${BOLD}${FG_YELLOW}\]$(opt_shlvl)\[${RESET}\]'
# shellcheck disable=SC2154
#PS1+='${debian_chroot:+($debian_chroot)}'
PS1+='\[${BOLD}${FG_GREEN}\]\u@\h\[${RESET}\]'
PS1+=':'
PS1+='\[${BOLD}${FG_BLUE}\]\w\[${RESET}\]'

if [[ -r /usr/lib/git-core/git-sh-prompt ]]
then
    source /usr/lib/git-core/git-sh-prompt

elif [[ -r /usr/share/git-core/contrib/completion/git-prompt.sh ]]
then
    source /usr/share/git-core/contrib/completion/git-prompt.sh

elif [[ -r /usr/share/git/completion/git-prompt.sh ]]
then
    source /usr/share/git/completion/git-prompt.sh

elif [[ -r /usr/share/git/git-prompt.sh ]]
then
    source /usr/share/git/git-prompt.sh

elif [[ -r "$XDG_CONFIG_HOME"/git/git-prompt.sh ]]
then
    source "$XDG_CONFIG_HOME"/git/git-prompt.sh

elif [[ -r ~/git-prompt.sh ]]
then
    source ~/git-prompt.sh
fi

GIT_PS1_DESCRIBE_STYLE=default
#GIT_PS1_HIDE_IF_PWD_IGNORED=1 # doesn't work with git 1.7.1
GIT_PS1_SHOWCOLORHINTS=1
#GIT_PS1_SHOWDIRTYSTATE=1 # slow
GIT_PS1_SHOWSTASHSTATE=1
#GIT_PS1_SHOWUNTRACKEDFILES=1 # slow
GIT_PS1_SHOWUPSTREAM=verbose

type -p __git_ps1 && PS1+='$(__git_ps1)'
PS1+=' \$ '

# https://en.wikipedia.org/wiki/ANSI_escape_code#Escape_sequences
# set the title

# https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h3-Operating-System-Commands
# Operating System Commands
# OSC Ps ; Pt BEL
# Ps = 0  ⇒  Change Icon Name and Window Title to Pt.
#PROMPT_COMMAND='printf "\e]0;${PWD/$HOME/\~}\a"'


# https://askubuntu.com/a/610238
# set the cursor color

# https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h3-Operating-System-Commands
# Operating System Commands
# OSC Ps ; Pt BEL
# Ps = 1 2  ⇒  Change text cursor color to Pt.
#printf '\e]12;orangered\a'

