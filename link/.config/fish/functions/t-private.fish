
function t-private --description 'tar private config files and .ssh folder'

	pushd . || return

	cd || return

	set TGT_DIR private.(date +%s)

	mkdir --verbose -- "$TGT_DIR" || return

	#find .config -type f -not -empty -name 'private.*' | xargs cp --verbose --target-directory $TGT_DIR || return
	for FILE in (find .config -type f -not -empty -name 'private.*')
		rsync -avR "$FILE" "$TGT_DIR" || return
	end

	if test -d .ssh/
		cp --verbose --target-directory "$TGT_DIR" -- .ssh || return
	end

	if dir_is_empty "$TGT_DIR"
		rmdir --verbose -- "$TGT_DIR" || return
	else
		t "$TGT_DIR" && xz -9 -e "$TGT_DIR".tar && del "$TGT_DIR" || return
	end

	popd || return
end

