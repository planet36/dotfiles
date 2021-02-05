# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

function x11_color_hex
    set --local rgb /usr/share/nvim/runtime/rgb.txt

    if not test -f "$rgb"
        printf 'Error: No such file: %s\n' "$rgb"
    end

    awk 'BEGIN{IGNORECASE=1}

NR>1 && $0 !~ /grey/ {

hex_str = sprintf("#%02X%02X%02X", $1, $2, $3)

color_name = $4
for (i=5; i<=NF; i++){color_name=color_name" "$i}

#print color_name
#print hex_str
if (!(hex_str in color_map)) { color_map[hex_str] = color_name }
}

END {

for (key in color_map) { print key }
#for (key in color_map) { print color_map[key] }

}' $rgb

end
