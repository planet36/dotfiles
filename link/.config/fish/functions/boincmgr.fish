
function boincmgr --description 'boincmgr with datadir specified' --wraps boincmgr

	mkdir --verbose --parents -- /media/sf_shared/boinc-data || return

	cd /media/sf_shared/boinc-data || return

	command boincmgr --datadir=/media/sf_shared/boinc-data $argv
end

