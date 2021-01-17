#!/bin/sh

# shellcheck shell=sh disable=SC1090

# {{{ Copied from [Arch] /etc/X11/xinit/xinitrc

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

: <<EOT
twm &
xclock -geometry 50x50-1+1 &
xterm -geometry 80x50+494+51 &
xterm -geometry 80x20+494-0 &
exec xterm -geometry 80x66+0+0 -name login
EOT

# }}}

# {{{ My additions

# No bashisms allowed

if command -v xrdb > /dev/null && [ -f "$XDG_CONFIG_HOME"/xorg/Xresources ]
then
    xrdb -I"$XDG_CONFIG_HOME"/xorg -merge "$XDG_CONFIG_HOME"/xorg/Xresources
fi

# {{{ keyboard

if command -v xset > /dev/null
then
    xset r rate 400 40  # autorepeat delay (ms), repeat rate (#/s)
fi

if command -v setxkbmap > /dev/null
then
    # grep 'ctrl:nocaps' /usr/share/X11/xkb/rules/base.lst
    setxkbmap -option ctrl:nocaps
fi

if command -v xcape > /dev/null
then
    # https://wiki.archlinux.org/index.php/Xorg/Keyboard_configuration#One-click_key_functions
    #killall --quiet xcape
    #xcape -e 'Caps_Lock=Escape'
    xcape -e 'Shift_L=Escape'
fi

# Must do xmodmap after setxkbmap

if command -v xmodmap > /dev/null
then
    # Swap Grave Accent and Tilde
    xmodmap -e 'keycode 49 = asciitilde grave'
fi

if command -v numlockx > /dev/null
then
    numlockx on
fi

# }}}


# {{{ background

BGCOLOR='#004466'

# NOTE: if xcompmgr will be run, use hsetroot
# https://wiki.archlinux.org/index.php/Xcompmgr#Background_turns_light_gray_briefly_after_logging_in_(e.g._in_Openbox)
if command -v hsetroot > /dev/null
then
    hsetroot -solid "$BGCOLOR"

elif command -v xsetroot > /dev/null
then
    #xsetroot -solid DodgerBlue4
    xsetroot -solid "$BGCOLOR"
fi

#if command -v xcompmgr > /dev/null
#then
#    xcompmgr &
#    #(sleep 1 && xcompmgr) &
#fi

if command -v stw > /dev/null
then
    # alpha only works when xcompmgr is running
    #stw -x +50 -y +50 -B 20 -f '#dddddd' -A 0 --
    #stw -x +50 -y +50 -B 20 -f '#dddddd' -b '#003355' --
    stw -x +50 -y +50 -B 20 -f '#dddddd' -b "$BGCOLOR" -F "monospace:size=12" -- \
        sh -c 'top -b -n 1 -o %CPU | head -n 12 ; echo ; echo ; free -h ; echo ; echo ; df -h -T -x squashfs -x tmpfs -x devtmpfs -x vboxsf' &
        # -u $USER
fi

# }}}

# {{{ status bar / root window name

#if command -v python3 > /dev/null && [ -f ~/.local/bin/perf-mon ]
if command -v python3 > /dev/null && command -v perf-mon > /dev/null
then
    perf-mon -q -x --sep=' ┆ ' --sleep=2 \
        cpu_usage_pct \
        mem_used_bytes \
        rx_rate_bytes_per_sec \
        tx_rate_bytes_per_sec \
        local_time &

elif command -v xsetroot > /dev/null
then
    # https://wiki.archlinux.org/index.php/Dwm#Statusbar_configuration
    while true
    do
        #xsetroot -name "$(date +'%F %R')"
        xsetroot -name "$(date +'%a %b %d %R')"
        sleep 30s
    done &

else
    xsetroot -name "$(date +'%a %b %d')"
fi

# }}}

exec dwm

# }}}
