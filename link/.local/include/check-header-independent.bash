#!/usr/bin/bash

# Check that the given C/C++ header is independent (i.e. can be compiled on its own).

for HEADER
do
	printf -v PROGRAM '#include "%s"\nint main(){return 0;}' "$HEADER"

	if [[ "$HEADER" == *'.h' ]]
	then
		command gcc $CPPFLAGS $CFLAGS -x c -o /dev/null - <<<"$PROGRAM" || exit
	elif  [[ "$HEADER" == *'.hpp' ]]
	then
		command g++ $CPPFLAGS $CXXFLAGS -x c++ -o /dev/null - <<<"$PROGRAM" || exit
	else
		echo 'Error: header file must end with ".h" or ".hpp"'
		exit 1
	fi
done
