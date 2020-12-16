
function dir-files --description 'for every directory, print the number of files'

	python3 -c '
import os
import sys

path = sys.argv[1] if len(sys.argv) > 1 else os.curdir

for (dir_path, dir_names, file_names) in os.walk(path):
	print(f"{len(file_names)}\t{dir_path}")
' $argv

end
