
# Inspired by
# https://github.com/LuRsT/hr

function hr --description 'Print a horizontal rule'

	if test (count $argv) -eq 0
		string repeat --max (tput cols) -- '#'
	else
		for S in $argv
			string repeat --max (tput cols) -- $S
		end
	end
end

