
function install_yay

	cd ~/.local/src/

	if not test -d yay-bin
		git clone https://aur.archlinux.org/yay-bin.git
		cd yay-bin
	else
		cd yay-bin
		git pull --ff-only || return
	end

	# Must enter sudo password
	makepkg --install --syncdeps --noconfirm --needed || return
	# Do not run yay as root

	cd -
end
