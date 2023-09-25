# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# {{{ env vars

export ACKRC="$XDG_CONFIG_HOME"/ack/ackrc

export CARGO_HOME="$XDG_DATA_HOME"/cargo

export CC=gcc
export CXX=g++

export EDITOR=nvim
export VISUAL=nvim

export DIFFPROG="$VISUAL -d"

export DOTNET_CLI_TELEMETRY_OPTOUT=1

# man 5 eza_colors
# https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters

EZA_COLORS_ARR=(
ur=32
uw=33
ux=31
ue=31
gr=32
gw=33
gx=31
tr=32
tw=33
tx=31
uu=37
gu=37
da=38\;5\;208
)

printf -v EZA_COLORS '%s:' "${EZA_COLORS_ARR[@]}"
export EZA_COLORS

export FZF_DEFAULT_OPTS='--multi --inline-info --ansi --tabstop=4 --color=bg+:25,fg+:220,gutter:-1 --preview-window=right'

if command -v highlight > /dev/null
then
    #FZF_DEFAULT_OPTS+=' --preview "highlight -- {} | head -n $FZF_PREVIEW_LINES"'
    # --line-range option added in highlight 3.43 (2018-04-30)
    # shellcheck disable=SC2016
    FZF_DEFAULT_OPTS+=' --preview "highlight --line-range=1-$FZF_PREVIEW_LINES -- {}"'
else
    # shellcheck disable=SC2016
    FZF_DEFAULT_OPTS+=' --preview "head -n $FZF_PREVIEW_LINES -- {}"'
fi

export GIT_EDITOR="$EDITOR"

export GNUPGHOME="$XDG_DATA_HOME"/gnupg

export HIGHLIGHT_OPTIONS='--force -t 4 --out-format=ansi'

export IPYTHONDIR="$XDG_DATA_HOME"/ipython

#export LANG=en_US.UTF-8
#export LC_ALL=en_US.UTF-8

#export LESS='--RAW-CONTROL-CHARS --quit-if-one-screen --no-init --use-color'
export LESS='--RAW-CONTROL-CHARS --no-init --use-color'
export LESSHISTFILE=/dev/null

# Inhibit these dbind warnings: Couldn't register with accessibility bus
# https://wiki.archlinux.de/title/GNOME#Tipps_und_Tricks
# https://askubuntu.com/a/318997
# This affects meld.
export NO_AT_BRIDGE=1

export NPM_CONFIG_USERCONFIG="$XDG_CONFIG_HOME"/npm/npmrc

# https://www.reddit.com/r/linux/comments/12wxsl/whats_in_your_bashrc/c6z0y5g/
#export JAVA_HOME="$(readlink -f -- "$(which javac)" | sed 's|bin/javac||')"

export PARALLEL_HOME="$XDG_CONFIG_HOME"/parallel

export PASSWORD_STORE_DIR="$XDG_DATA_HOME"/pass

export PREFIX="$HOME"/.local

#export PS_FORMAT='pid,nice,pri,user,stime,etime,sz,pmem,pcpu,command'
export PS_FORMAT='pid,nice,pri,user,stime,etime,cputimes,%cpu,%mem,rss,args'

export PYENV_ROOT="$XDG_DATA_HOME"/pyenv

export PYLINTHOME="$XDG_CACHE_HOME"/pylint.d

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH
export PYTHONPATH="$HOME"/.local/lib/python

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPYCACHEPREFIX
export PYTHONPYCACHEPREFIX="$XDG_CACHE_HOME"/__pycache__

export RIPGREP_CONFIG_PATH="$XDG_CONFIG_HOME"/ripgrep/ripgreprc

export SCREENRC="$XDG_CONFIG_HOME"/screen/screenrc

export TERMINFO="$XDG_DATA_HOME"/terminfo
export TERMINFO_DIRS="$XDG_DATA_HOME"/terminfo:/usr/share/terminfo

# /usr/bin/time format similar to bash's time
export TIME="real\t%E\nuser\t%U\nsys\t%S\n"

export TRASH_DIR="$XDG_DATA_HOME"/Trash

# https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html#tag_08_03
# https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
export TZ=':America/New_York'
#export TZ='EST+5'
#export TZ='UTC+5'

export VCS_REPOS_MATCH='( -type d -and ( -name CVS -or -name .svn -or -name .git -or -name .hg ) )'
printf -v VCS_REPOS_PRUNE '( %s -prune , -not %s )' "$VCS_REPOS_MATCH" "$VCS_REPOS_MATCH"
export VCS_REPOS_PRUNE

export W3M_DIR="$XDG_DATA_HOME"/w3m

export XAUTHORITY="$XDG_CACHE_HOME"/xorg/Xauthority

export XINITRC="$XDG_CONFIG_HOME"/X11/xinit/xinitrc

# {{{ pager colors

# https://unix.stackexchange.com/a/147

# man 5 terminfo
# https://man7.org/linux/man-pages/man5/terminfo.5.html

# man terminfo | grep -A 1 -E '\<(mb|md|me|so|se|us|ue|mr|mh|ZN|ZV|ZO|ZW)\>'

# enter_blink_mode            blink     mb     turn on blinking
# enter_bold_mode             bold      md     turn on bold (extra bright) mode
# enter_dim_mode              dim       mh     turn on half-bright mode
# enter_reverse_mode          rev       mr     turn on reverse video mode
# enter_standout_mode         smso      so     begin standout mode
# enter_underline_mode        smul      us     begin underline mode
# exit_attribute_mode         sgr0      me     turn off all attributes
# exit_standout_mode          rmso      se     exit standout mode
# exit_underline_mode         rmul      ue     exit underline mode

# 0 = black
# 1 = red
# 2 = green
# 3 = yellow
# 4 = blue
# 5 = magenta
# 6 = cyan
# 7 = white

#LESS_TERMCAP_mb=$(tput bold; tput setaf 6) # turn on blinking
#LESS_TERMCAP_md=$(tput bold; tput setaf 2) # turn on bold (extra bright) mode
#LESS_TERMCAP_mh=$(tput dim) # turn on half-bright mode
#LESS_TERMCAP_mr=$(tput rev) # turn on reverse video mode
#LESS_TERMCAP_so=$(tput bold; tput rev; tput setaf 4) # begin standout mode
#LESS_TERMCAP_us=$(tput smul; tput bold; tput setaf 3) # begin underline mode
#LESS_TERMCAP_me=$(tput sgr0) # turn off all attributes
#LESS_TERMCAP_se=$(tput rmso; tput sgr0) # exit standout mode
#LESS_TERMCAP_ue=$(tput rmul; tput sgr0) # exit underline mode

#export LESS_TERMCAP_mb
#export LESS_TERMCAP_md
#export LESS_TERMCAP_mh
#export LESS_TERMCAP_mr
#export LESS_TERMCAP_so
#export LESS_TERMCAP_us
#export LESS_TERMCAP_me
#export LESS_TERMCAP_se
#export LESS_TERMCAP_ue

# For Konsole and Gnome-terminal
#export GROFF_NO_SGR=1

# https://stackoverflow.com/a/19871578
export MANPAGER='less -s -M +Gg --color=d+B --color=u+y'

# }}}

# {{{ compile options

# Too many benign warnings:
# -Wpadded
# -Wfloat-equal
GCC_COMMON_OPTIONS='-O2 -pipe -Wall -Wextra -Wpedantic -Wfatal-errors -Wcast-align=strict -Wcast-qual -Wduplicated-branches -Wduplicated-cond -Werror=return-type -Wformat-overflow=2 -Wformat=2 -Wlogical-op -Wmissing-include-dirs -Wno-error -Wno-format-nonliteral -Wno-unused-function -Wshadow -Wswitch-default -Wswitch-enum -Wuninitialized -Wunsafe-loop-optimizations'
# https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
GCC_COMMON_OPTIONS+=' -D__STDC_WANT_IEC_60559_BFP_EXT__ -D__STDC_WANT_IEC_60559_FUNCS_EXT__ -D__STDC_WANT_IEC_60559_TYPES_EXT__ -D__STDC_WANT_IEC_60559_EXT__'
GCC_COMMON_OPTIONS+=' -D_GNU_SOURCE -D_FORTIFY_SOURCE=2'
# https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
GCC_COMMON_OPTIONS+=' -fstack-protector -fstack-clash-protection'
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#GCC_COMMON_OPTIONS+=' -ftrivial-auto-var-init=zero'

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#OPTIMIZE_OPTIONS='-O3 -march=native -fassociative-math -fno-math-errno -freciprocal-math -fno-signed-zeros -fno-trapping-math'
# Using -fsigned-zeros disables associative-math
#OPTIMIZE_OPTIONS='-O3 -march=native -fno-math-errno -freciprocal-math -fno-trapping-math'
export OPTIMIZE_OPTIONS='-O3 -flto=auto -march=native'
#OPTIMIZE_OPTIONS+=' -fno-math-errno'
#OPTIMIZE_OPTIONS+=' -funsafe-math-optimizations'

export DEBUG_OPTIONS='-Og -g3'
# https://www.gnu.org/software/libc/manual/html_node/Consistency-Checking.html
DEBUG_OPTIONS+=' -UNDEBUG'
# https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html
DEBUG_OPTIONS+=' -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG -D_GLIBCXX_SANITIZE_VECTOR'

export PERF_TEST_OPTIONS="$OPTIMIZE_OPTIONS -fno-allocation-dce -fno-dce -fno-dse -fno-gcse -fno-split-paths -fno-tree-builtin-call-dce -fno-tree-copy-prop -fno-tree-dce -fno-tree-dse -fno-tree-fre -fno-tree-partial-pre -fno-tree-pre"

export PROFILE_OPTIONS="$PERF_TEST_OPTIONS -pg"

# https://gcc.gnu.org/onlinedocs/cpp/Invocation.html
export CPPFLAGS="-iquote $HOME/.local/include"

# shellcheck disable=SC2034
LATEST_C_STD="$(gcc -v --help 2>/dev/null | grep -E -- '^\s*-std=c2' | grep -v -F 'Same as' | tail -n 1 | awk '{print $1}')"
# shellcheck disable=SC2034
LATEST_GNU_STD="$(gcc -v --help 2>/dev/null | grep -E -- '^\s*-std=gnu2' | grep -v -F 'Same as' | tail -n 1 | awk '{print $1}')"

export CFLAGS="$GCC_COMMON_OPTIONS $LATEST_GNU_STD -Wc++-compat"

# shellcheck disable=SC2034
LATEST_CXX_STD="$(gcc -v --help 2>/dev/null | grep -E -- '^\s*-std=c\+\+2' | grep -v -F 'Same as' | tail -n 1 | awk '{print $1}')"
# shellcheck disable=SC2034
LATEST_GNUXX_STD="$(gcc -v --help 2>/dev/null | grep -E -- '^\s*-std=gnu\+\+2' | grep -v -F 'Same as' | tail -n 1 | awk '{print $1}')"

export CXXFLAGS="$GCC_COMMON_OPTIONS $LATEST_GNUXX_STD -fchar8_t -fdiagnostics-show-template-tree -fstrict-enums -Wctor-dtor-privacy -Wextra-semi -Wmismatched-tags -Wmultiple-inheritance -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-tags -Wsign-promo -Wstrict-null-sentinel -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wuseless-cast -Wzero-as-null-pointer-constant"

# }}}

# }}}
