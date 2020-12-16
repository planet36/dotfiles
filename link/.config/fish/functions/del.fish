
function del --wraps mv --description 'delete (move to trash folder)'

    set -x SIMPLE_BACKUP_SUFFIX (date -u +.%Y%m%dT%H%M%SS%3N)

    command mv --verbose --backup=simple --target-directory $TRASH_DIR $argv
end
