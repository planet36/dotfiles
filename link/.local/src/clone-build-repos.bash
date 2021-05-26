#!/usr/bin/bash

mapfile -t REPOS < git-repos.txt

for REPO in "${REPOS[@]}"
do
	if [[ "$REPO" == #* ]]
	then
		continue
	fi

	DIR="$(basename -s .git -- "$REPO")" || exit

	if [[ ! -d "$DIR" ]]
	then
		if [[ ! "$REPO" == https://git.suckless.org/* ]]
		then
			git clone "$REPO" || exit
		else
			git clone "$REPO" "$DIR"-suckless || exit
		fi

		# My repos
		if [[ "$REPO" == https://github.com/planet36/* ]]
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
	if [[ ! "$REPO" == https://git.suckless.org/* ]]
	then
		cd "$DIR" || exit
		make install || exit
		cd - > /dev/null || exit
	fi
done
