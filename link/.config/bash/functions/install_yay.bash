# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function install_yay
{
	cd ~/.local/src/

	if [ ! -d yay-bin ] ; then
		git clone https://aur.archlinux.org/yay-bin.git
		cd yay-bin
	else
		cd yay-bin
		git pull --ff-only || return
	fi

	# Must enter sudo password
	makepkg --install --syncdeps --noconfirm --needed || return
	# Do not run yay as root

	cd - > /dev/null
}

