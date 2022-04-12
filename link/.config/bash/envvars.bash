# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# {{{ env vars

export ACKRC="$XDG_CONFIG_HOME"/ack/ackrc

export CC=gcc
export CXX=g++

export EDITOR=nvim
export VISUAL=nvim

export DIFFPROG="$VISUAL -d"

export DOTNET_CLI_TELEMETRY_OPTOUT=1

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

#export LESS='--RAW-CONTROL-CHARS --quit-if-one-screen --no-init'
export LESS='--RAW-CONTROL-CHARS --no-init'
export LESSHISTFILE=/dev/null

# Inhibit these dbind warnings: Couldn't register with accessibility bus
# https://wiki.archlinux.de/title/GNOME#Tipps_und_Tricks
# https://askubuntu.com/a/318997
# This affects meld.
export NO_AT_BRIDGE=1

# https://www.reddit.com/r/linux/comments/12wxsl/whats_in_your_bashrc/c6z0y5g/
#export JAVA_HOME="$(readlink -f -- "$(which javac)" | sed 's|bin/javac||')"

export PARALLEL_HOME="$XDG_CONFIG_HOME"/parallel

export PASSWORD_STORE_DIR="$XDG_DATA_HOME"/pass

export PREFIX="$HOME"/.local

#export PS_FORMAT='pid,nice,pri,user,stime,etime,sz,pmem,pcpu,command'
export PS_FORMAT='pid,nice,pri,user,stime,etime,cputimes,%cpu,%mem,rss,args'

export PYLINTHOME="$XDG_CACHE_HOME"/pylint.d

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH
export PYTHONPATH="$HOME"/.local/lib/python

# https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPYCACHEPREFIX
export PYTHONPYCACHEPREFIX="$XDG_CACHE_HOME"/__pycache__

export RIPGREP_CONFIG_PATH="$XDG_CONFIG_HOME"/ripgrep/ripgreprc

export SCREENRC="$XDG_CONFIG_HOME"/screen/screenrc

# /usr/bin/time format similar to bash's time
export TIME="real\t%E\nuser\t%U\nsys\t%S\n"

export TRASH_DIR="$XDG_DATA_HOME"/Trash

# https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html#tag_08_03
# https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
#export TZ=':America/New_York'
export TZ='EST+5'

#export VCS_REPOS_MATCH='( -type d -and ( -name CVS -or -name .svn -or -name .git -or -name .hg ) )'
#export VCS_REPOS_PRUNE="( $VCS_REPOS_MATCH -prune , -not $VCS_REPOS_MATCH )"

export XAUTHORITY="$XDG_CACHE_HOME"/xorg/Xauthority

# {{{ pager colors

# https://unix.stackexchange.com/a/147

# man 5 terminfo
# http://man7.org/linux/man-pages/man5/terminfo.5.html

# man terminfo | grep -A 1 -E '\<(mb|md|me|so|se|us|ue|mr|mh|ZN|ZV|ZO|ZW)\>'

# enter_blink_mode            blink     mb     turn on blinking
# enter_bold_mode             bold      md     turn on bold (extra bright) mode
# enter_dim_mode              dim       mh     turn on half-bright mode
# enter_reverse_mode          rev       mr     turn on reverse video mode
# enter_standout_mode         smso      so     begin standout mode
# enter_subscript_mode        ssubm     ZN     Enter subscript mode
# enter_superscript_mode      ssupm     ZO     Enter superscript mode
# enter_underline_mode        smul      us     begin underline mode
# exit_attribute_mode         sgr0      me     turn off all attributes
# exit_standout_mode          rmso      se     exit standout mode
# exit_subscript_mode         rsubm     ZV     End subscript mode
# exit_superscript_mode       rsupm     ZW     End superscript mode
# exit_underline_mode         rmul      ue     exit underline mode

# 0 = black
# 1 = red
# 2 = green
# 3 = yellow
# 4 = blue
# 5 = magenta
# 6 = cyan
# 7 = white

LESS_TERMCAP_mb=$(tput bold; tput setaf 6) # turn on blinking
LESS_TERMCAP_md=$(tput bold; tput setaf 2) # turn on bold (extra bright) mode
LESS_TERMCAP_mh=$(tput dim) # turn on half-bright mode
LESS_TERMCAP_mr=$(tput rev) # turn on reverse video mode
LESS_TERMCAP_so=$(tput bold; tput rev; tput setaf 4) # begin standout mode
LESS_TERMCAP_ZN=$(tput ssubm) # Enter subscript mode
LESS_TERMCAP_ZO=$(tput ssupm) # Enter superscript mode
LESS_TERMCAP_us=$(tput smul; tput bold; tput setaf 3) # begin underline mode
LESS_TERMCAP_me=$(tput sgr0) # turn off all attributes
LESS_TERMCAP_se=$(tput rmso; tput sgr0) # exit standout mode
LESS_TERMCAP_ZV=$(tput rsubm) # End subscript mode
LESS_TERMCAP_ZW=$(tput rsupm) # End superscript mode
LESS_TERMCAP_ue=$(tput rmul; tput sgr0) # exit underline mode

export LESS_TERMCAP_mb
export LESS_TERMCAP_md
export LESS_TERMCAP_mh
export LESS_TERMCAP_mr
export LESS_TERMCAP_so
export LESS_TERMCAP_ZN
export LESS_TERMCAP_ZO
export LESS_TERMCAP_us
export LESS_TERMCAP_me
export LESS_TERMCAP_se
export LESS_TERMCAP_ZV
export LESS_TERMCAP_ZW
export LESS_TERMCAP_ue

# For Konsole and Gnome-terminal
#export GROFF_NO_SGR=1

# https://stackoverflow.com/a/19871578
export MANPAGER='less -s -M +Gg'

# }}}

# {{{ compile options

# Too many benign warnings:
# -Wpadded
# -Wfloat-equal
GCC_COMMON_OPTIONS='-O2 -pipe -Wall -Wextra -Wpedantic -Wfatal-errors -Wcast-align -Wcast-qual -Wduplicated-branches -Wduplicated-cond -Wformat-overflow=2 -Wformat=2 -Wlogical-op -Wmissing-include-dirs -Wno-format-nonliteral -Wno-unused-function -Wshadow -Wswitch-default -Wswitch-enum -Wuninitialized -Wunsafe-loop-optimizations'
# https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
GCC_COMMON_OPTIONS+=' -D__STDC_WANT_IEC_60559_BFP_EXT__ -D__STDC_WANT_IEC_60559_FUNCS_EXT__ -D__STDC_WANT_IEC_60559_TYPES_EXT__ -D__STDC_WANT_IEC_60559_EXT__'
GCC_COMMON_OPTIONS+=' -D_GNU_SOURCE -D_FORTIFY_SOURCE=2'
# https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html
GCC_COMMON_OPTIONS+=' -fstack-protector -fstack-clash-protection'

# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#OPTIMIZE_OPTIONS='-O3 -march=native -fassociative-math -fno-math-errno -freciprocal-math -fno-signed-zeros -fno-trapping-math'
# Using -fsigned-zeros disables associative-math
#OPTIMIZE_OPTIONS='-O3 -march=native -fno-math-errno -freciprocal-math -fno-trapping-math'
export OPTIMIZE_OPTIONS='-O3 -flto -march=native'
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

export CFLAGS="$GCC_COMMON_OPTIONS -std=gnu2x"
export CXXFLAGS="$GCC_COMMON_OPTIONS -std=gnu++23 -fchar8_t -fdiagnostics-show-template-tree -Wctor-dtor-privacy -Wextra-semi -Wmismatched-tags -Wmultiple-inheritance -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-tags -Wsign-promo -Wstrict-null-sentinel -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wuseless-cast -Wzero-as-null-pointer-constant"

# }}}

# }}}
