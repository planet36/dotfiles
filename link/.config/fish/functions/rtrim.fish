
function rtrim --description 'trim trailing whitespace'

	# \s matches newline
	#perl -p -i~ -e 's/\s+$//' -- $argv
	perl -p -i~ -e 's/[ \t]+$//' -- $argv
end
