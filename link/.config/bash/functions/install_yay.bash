# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function install_yay
{
	pushd . &> /dev/null

	cd ~/.local/src/ || return

	if [ ! -d yay-bin ] ; then
		git clone https://aur.archlinux.org/yay-bin.git
		cd yay-bin || return
	else
		cd yay-bin || return
		git pull --ff-only || return
	fi

	# Must enter sudo password
	makepkg --install --syncdeps --noconfirm --needed || return
	# Do not run yay as root

	#cd - > /dev/null || return

	# https://github.com/koalaman/shellcheck/issues/613
	# shellcheck disable=SC2164
	popd &> /dev/null
}

