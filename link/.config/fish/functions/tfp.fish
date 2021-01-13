
function tfp --description 'tar format patch'

	set TGT_DIR patches-(string replace --regex --all '\W' '' (basename (pwd))) || return

	mkdir --verbose -- "$TGT_DIR" || return

	git format-patch -o "$TGT_DIR" --keep-subject --base=auto --progress (git rev-parse --abbrev-ref HEAD@{upstream})..HEAD || return

	if dir_is_empty "$TGT_DIR"
		rmdir --verbose -- "$TGT_DIR" || return
	else
		t "$TGT_DIR" && xz -9 -e "$TGT_DIR".tar && del "$TGT_DIR" || return
		mv --verbose -- "$TGT_DIR".tar.xz ~/Downloads || return
		printf 'del %s\n' ~/Downloads/"$TGT_DIR".tar.xz
	end
end

