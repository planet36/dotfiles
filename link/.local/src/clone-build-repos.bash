#!/usr/bin/bash

declare -a REPOS=(
https://github.com/planet36/arch-install.git
https://github.com/planet36/dwm.git
#git@github.com:planet36/dwm.git
https://github.com/planet36/slstatus.git
#git@github.com:planet36/slstatus.git
https://github.com/planet36/st.git
#git@github.com:planet36/st.git
https://git.suckless.org/dwm
https://git.suckless.org/slstatus
https://git.suckless.org/st
https://github.com/sineemore/stw.git
)

for REPO in "${REPOS[@]}"
do
	DIR="$(basename -s .git -- "$REPO")" || exit

	if [[ ! -d "$DIR" ]]
	then
		if [[ ! "$REPO" =~ https://git.suckless.org/* ]]
		then
			git clone "$REPO" || exit
		else
			git clone "$REPO" "$DIR"-suckless || exit
		fi

		# My repos
		if [[ "$REPO" =~ https://github.com/planet36/* ]]
		then
			case "$DIR" in
				# These repos were forked from suckless
				dwm|slstatus|st)
					# Add remotes to the suckless repos
					cd "$DIR" || exit
					git remote add suckless https://git.suckless.org/"$DIR"
					git remote set-url --push suckless DISABLE
					git fetch suckless
					cd - > /dev/null || exit
					;;
				*)
					;;
			esac
		fi
	fi

	# Do not install suckless programs
	if [[ ! "$REPO" =~ https://git.suckless.org/* ]]
	then
		cd "$DIR" || exit
		make PREFIX="$HOME"/.local install || exit
		cd - > /dev/null || exit
	fi
done
