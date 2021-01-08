
function tfp --description 'tar format patch'

	TGT_DIR=(string replace --regex --all '\W' '' (basename (pwd)))

	mkdir --verbose -- "$TGT_DIR" || return

	git format-patch --keep-subject -o "$TGT_DIR" --progress origin/master..HEAD

	if dir_is_empty "$TGT_DIR"
		rmdir --verbose -- "$TGT_DIR" || return
	else
		t "$TGT_DIR" && xz -9 -e "$TGT_DIR".tar && del "$TGT_DIR" || return
		mv --verbose -- "$TGT_DIR".tar.xz ~/Downloads
		#cd Downloads/
		printf 'del %q\n' ~/Downloads/"$TGT_DIR".tar.xz
	end
end

