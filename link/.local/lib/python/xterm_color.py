# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# pylint: disable=bad-indentation
# pylint: disable=fixme
# pylint: disable=invalid-name
# pylint: disable=missing-module-docstring
# pylint: disable=pointless-string-statement
# pylint: disable=trailing-newlines

__author__ = 'Steven Ward'
__version__ = '2020-08-10'
__license__ = 'OSL-3.0'

'''
# X11 color names
awk 'BEGIN{IGNORECASE=1}

NR>1 && $0 !~ /grey/ {

hex_str = sprintf("#%02X%02X%02X", $1, $2, $3)

color_name = $4
for (i=5; i<=NF; i++){color_name=color_name" "$i}

printf("\t\"%s\" : \"%s\",\n", color_name, hex_str)
}' /usr/share/X11/rgb.txt
'''

x11_colorname_to_rgb_string = {
    "snow"                   : "#FFFAFA",
    "ghost white"            : "#F8F8FF",
    "GhostWhite"             : "#F8F8FF",
    "white smoke"            : "#F5F5F5",
    "WhiteSmoke"             : "#F5F5F5",
    "gainsboro"              : "#DCDCDC",
    "floral white"           : "#FFFAF0",
    "FloralWhite"            : "#FFFAF0",
    "old lace"               : "#FDF5E6",
    "OldLace"                : "#FDF5E6",
    "linen"                  : "#FAF0E6",
    "antique white"          : "#FAEBD7",
    "AntiqueWhite"           : "#FAEBD7",
    "papaya whip"            : "#FFEFD5",
    "PapayaWhip"             : "#FFEFD5",
    "blanched almond"        : "#FFEBCD",
    "BlanchedAlmond"         : "#FFEBCD",
    "bisque"                 : "#FFE4C4",
    "peach puff"             : "#FFDAB9",
    "PeachPuff"              : "#FFDAB9",
    "navajo white"           : "#FFDEAD",
    "NavajoWhite"            : "#FFDEAD",
    "moccasin"               : "#FFE4B5",
    "cornsilk"               : "#FFF8DC",
    "ivory"                  : "#FFFFF0",
    "lemon chiffon"          : "#FFFACD",
    "LemonChiffon"           : "#FFFACD",
    "seashell"               : "#FFF5EE",
    "honeydew"               : "#F0FFF0",
    "mint cream"             : "#F5FFFA",
    "MintCream"              : "#F5FFFA",
    "azure"                  : "#F0FFFF",
    "alice blue"             : "#F0F8FF",
    "AliceBlue"              : "#F0F8FF",
    "lavender"               : "#E6E6FA",
    "lavender blush"         : "#FFF0F5",
    "LavenderBlush"          : "#FFF0F5",
    "misty rose"             : "#FFE4E1",
    "MistyRose"              : "#FFE4E1",
    "white"                  : "#FFFFFF",
    "black"                  : "#000000",
    "dark slate gray"        : "#2F4F4F",
    "DarkSlateGray"          : "#2F4F4F",
    "dim gray"               : "#696969",
    "DimGray"                : "#696969",
    "slate gray"             : "#708090",
    "SlateGray"              : "#708090",
    "light slate gray"       : "#778899",
    "LightSlateGray"         : "#778899",
    "gray"                   : "#BEBEBE",
    "x11 gray"               : "#BEBEBE",
    "X11Gray"                : "#BEBEBE",
    "web gray"               : "#808080",
    "WebGray"                : "#808080",
    "light gray"             : "#D3D3D3",
    "LightGray"              : "#D3D3D3",
    "midnight blue"          : "#191970",
    "MidnightBlue"           : "#191970",
    "navy"                   : "#000080",
    "navy blue"              : "#000080",
    "NavyBlue"               : "#000080",
    "cornflower blue"        : "#6495ED",
    "CornflowerBlue"         : "#6495ED",
    "dark slate blue"        : "#483D8B",
    "DarkSlateBlue"          : "#483D8B",
    "slate blue"             : "#6A5ACD",
    "SlateBlue"              : "#6A5ACD",
    "medium slate blue"      : "#7B68EE",
    "MediumSlateBlue"        : "#7B68EE",
    "light slate blue"       : "#8470FF",
    "LightSlateBlue"         : "#8470FF",
    "medium blue"            : "#0000CD",
    "MediumBlue"             : "#0000CD",
    "royal blue"             : "#4169E1",
    "RoyalBlue"              : "#4169E1",
    "blue"                   : "#0000FF",
    "dodger blue"            : "#1E90FF",
    "DodgerBlue"             : "#1E90FF",
    "deep sky blue"          : "#00BFFF",
    "DeepSkyBlue"            : "#00BFFF",
    "sky blue"               : "#87CEEB",
    "SkyBlue"                : "#87CEEB",
    "light sky blue"         : "#87CEFA",
    "LightSkyBlue"           : "#87CEFA",
    "steel blue"             : "#4682B4",
    "SteelBlue"              : "#4682B4",
    "light steel blue"       : "#B0C4DE",
    "LightSteelBlue"         : "#B0C4DE",
    "light blue"             : "#ADD8E6",
    "LightBlue"              : "#ADD8E6",
    "powder blue"            : "#B0E0E6",
    "PowderBlue"             : "#B0E0E6",
    "pale turquoise"         : "#AFEEEE",
    "PaleTurquoise"          : "#AFEEEE",
    "dark turquoise"         : "#00CED1",
    "DarkTurquoise"          : "#00CED1",
    "medium turquoise"       : "#48D1CC",
    "MediumTurquoise"        : "#48D1CC",
    "turquoise"              : "#40E0D0",
    "cyan"                   : "#00FFFF",
    "aqua"                   : "#00FFFF",
    "light cyan"             : "#E0FFFF",
    "LightCyan"              : "#E0FFFF",
    "cadet blue"             : "#5F9EA0",
    "CadetBlue"              : "#5F9EA0",
    "medium aquamarine"      : "#66CDAA",
    "MediumAquamarine"       : "#66CDAA",
    "aquamarine"             : "#7FFFD4",
    "dark green"             : "#006400",
    "DarkGreen"              : "#006400",
    "dark olive green"       : "#556B2F",
    "DarkOliveGreen"         : "#556B2F",
    "dark sea green"         : "#8FBC8F",
    "DarkSeaGreen"           : "#8FBC8F",
    "sea green"              : "#2E8B57",
    "SeaGreen"               : "#2E8B57",
    "medium sea green"       : "#3CB371",
    "MediumSeaGreen"         : "#3CB371",
    "light sea green"        : "#20B2AA",
    "LightSeaGreen"          : "#20B2AA",
    "pale green"             : "#98FB98",
    "PaleGreen"              : "#98FB98",
    "spring green"           : "#00FF7F",
    "SpringGreen"            : "#00FF7F",
    "lawn green"             : "#7CFC00",
    "LawnGreen"              : "#7CFC00",
    "green"                  : "#00FF00",
    "lime"                   : "#00FF00",
    "x11 green"              : "#00FF00",
    "X11Green"               : "#00FF00",
    "web green"              : "#008000",
    "WebGreen"               : "#008000",
    "chartreuse"             : "#7FFF00",
    "medium spring green"    : "#00FA9A",
    "MediumSpringGreen"      : "#00FA9A",
    "green yellow"           : "#ADFF2F",
    "GreenYellow"            : "#ADFF2F",
    "lime green"             : "#32CD32",
    "LimeGreen"              : "#32CD32",
    "yellow green"           : "#9ACD32",
    "YellowGreen"            : "#9ACD32",
    "forest green"           : "#228B22",
    "ForestGreen"            : "#228B22",
    "olive drab"             : "#6B8E23",
    "OliveDrab"              : "#6B8E23",
    "dark khaki"             : "#BDB76B",
    "DarkKhaki"              : "#BDB76B",
    "khaki"                  : "#F0E68C",
    "pale goldenrod"         : "#EEE8AA",
    "PaleGoldenrod"          : "#EEE8AA",
    "light goldenrod yellow" : "#FAFAD2",
    "LightGoldenrodYellow"   : "#FAFAD2",
    "light yellow"           : "#FFFFE0",
    "LightYellow"            : "#FFFFE0",
    "yellow"                 : "#FFFF00",
    "gold"                   : "#FFD700",
    "light goldenrod"        : "#EEDD82",
    "LightGoldenrod"         : "#EEDD82",
    "goldenrod"              : "#DAA520",
    "dark goldenrod"         : "#B8860B",
    "DarkGoldenrod"          : "#B8860B",
    "rosy brown"             : "#BC8F8F",
    "RosyBrown"              : "#BC8F8F",
    "indian red"             : "#CD5C5C",
    "IndianRed"              : "#CD5C5C",
    "saddle brown"           : "#8B4513",
    "SaddleBrown"            : "#8B4513",
    "sienna"                 : "#A0522D",
    "peru"                   : "#CD853F",
    "burlywood"              : "#DEB887",
    "beige"                  : "#F5F5DC",
    "wheat"                  : "#F5DEB3",
    "sandy brown"            : "#F4A460",
    "SandyBrown"             : "#F4A460",
    "tan"                    : "#D2B48C",
    "chocolate"              : "#D2691E",
    "firebrick"              : "#B22222",
    "brown"                  : "#A52A2A",
    "dark salmon"            : "#E9967A",
    "DarkSalmon"             : "#E9967A",
    "salmon"                 : "#FA8072",
    "light salmon"           : "#FFA07A",
    "LightSalmon"            : "#FFA07A",
    "orange"                 : "#FFA500",
    "dark orange"            : "#FF8C00",
    "DarkOrange"             : "#FF8C00",
    "coral"                  : "#FF7F50",
    "light coral"            : "#F08080",
    "LightCoral"             : "#F08080",
    "tomato"                 : "#FF6347",
    "orange red"             : "#FF4500",
    "OrangeRed"              : "#FF4500",
    "red"                    : "#FF0000",
    "hot pink"               : "#FF69B4",
    "HotPink"                : "#FF69B4",
    "deep pink"              : "#FF1493",
    "DeepPink"               : "#FF1493",
    "pink"                   : "#FFC0CB",
    "light pink"             : "#FFB6C1",
    "LightPink"              : "#FFB6C1",
    "pale violet red"        : "#DB7093",
    "PaleVioletRed"          : "#DB7093",
    "maroon"                 : "#B03060",
    "x11 maroon"             : "#B03060",
    "X11Maroon"              : "#B03060",
    "web maroon"             : "#800000",
    "WebMaroon"              : "#800000",
    "medium violet red"      : "#C71585",
    "MediumVioletRed"        : "#C71585",
    "violet red"             : "#D02090",
    "VioletRed"              : "#D02090",
    "magenta"                : "#FF00FF",
    "fuchsia"                : "#FF00FF",
    "violet"                 : "#EE82EE",
    "plum"                   : "#DDA0DD",
    "orchid"                 : "#DA70D6",
    "medium orchid"          : "#BA55D3",
    "MediumOrchid"           : "#BA55D3",
    "dark orchid"            : "#9932CC",
    "DarkOrchid"             : "#9932CC",
    "dark violet"            : "#9400D3",
    "DarkViolet"             : "#9400D3",
    "blue violet"            : "#8A2BE2",
    "BlueViolet"             : "#8A2BE2",
    "purple"                 : "#A020F0",
    "x11 purple"             : "#A020F0",
    "X11Purple"              : "#A020F0",
    "web purple"             : "#800080",
    "WebPurple"              : "#800080",
    "medium purple"          : "#9370DB",
    "MediumPurple"           : "#9370DB",
    "thistle"                : "#D8BFD8",
    "snow1"                  : "#FFFAFA",
    "snow2"                  : "#EEE9E9",
    "snow3"                  : "#CDC9C9",
    "snow4"                  : "#8B8989",
    "seashell1"              : "#FFF5EE",
    "seashell2"              : "#EEE5DE",
    "seashell3"              : "#CDC5BF",
    "seashell4"              : "#8B8682",
    "AntiqueWhite1"          : "#FFEFDB",
    "AntiqueWhite2"          : "#EEDFCC",
    "AntiqueWhite3"          : "#CDC0B0",
    "AntiqueWhite4"          : "#8B8378",
    "bisque1"                : "#FFE4C4",
    "bisque2"                : "#EED5B7",
    "bisque3"                : "#CDB79E",
    "bisque4"                : "#8B7D6B",
    "PeachPuff1"             : "#FFDAB9",
    "PeachPuff2"             : "#EECBAD",
    "PeachPuff3"             : "#CDAF95",
    "PeachPuff4"             : "#8B7765",
    "NavajoWhite1"           : "#FFDEAD",
    "NavajoWhite2"           : "#EECFA1",
    "NavajoWhite3"           : "#CDB38B",
    "NavajoWhite4"           : "#8B795E",
    "LemonChiffon1"          : "#FFFACD",
    "LemonChiffon2"          : "#EEE9BF",
    "LemonChiffon3"          : "#CDC9A5",
    "LemonChiffon4"          : "#8B8970",
    "cornsilk1"              : "#FFF8DC",
    "cornsilk2"              : "#EEE8CD",
    "cornsilk3"              : "#CDC8B1",
    "cornsilk4"              : "#8B8878",
    "ivory1"                 : "#FFFFF0",
    "ivory2"                 : "#EEEEE0",
    "ivory3"                 : "#CDCDC1",
    "ivory4"                 : "#8B8B83",
    "honeydew1"              : "#F0FFF0",
    "honeydew2"              : "#E0EEE0",
    "honeydew3"              : "#C1CDC1",
    "honeydew4"              : "#838B83",
    "LavenderBlush1"         : "#FFF0F5",
    "LavenderBlush2"         : "#EEE0E5",
    "LavenderBlush3"         : "#CDC1C5",
    "LavenderBlush4"         : "#8B8386",
    "MistyRose1"             : "#FFE4E1",
    "MistyRose2"             : "#EED5D2",
    "MistyRose3"             : "#CDB7B5",
    "MistyRose4"             : "#8B7D7B",
    "azure1"                 : "#F0FFFF",
    "azure2"                 : "#E0EEEE",
    "azure3"                 : "#C1CDCD",
    "azure4"                 : "#838B8B",
    "SlateBlue1"             : "#836FFF",
    "SlateBlue2"             : "#7A67EE",
    "SlateBlue3"             : "#6959CD",
    "SlateBlue4"             : "#473C8B",
    "RoyalBlue1"             : "#4876FF",
    "RoyalBlue2"             : "#436EEE",
    "RoyalBlue3"             : "#3A5FCD",
    "RoyalBlue4"             : "#27408B",
    "blue1"                  : "#0000FF",
    "blue2"                  : "#0000EE",
    "blue3"                  : "#0000CD",
    "blue4"                  : "#00008B",
    "DodgerBlue1"            : "#1E90FF",
    "DodgerBlue2"            : "#1C86EE",
    "DodgerBlue3"            : "#1874CD",
    "DodgerBlue4"            : "#104E8B",
    "SteelBlue1"             : "#63B8FF",
    "SteelBlue2"             : "#5CACEE",
    "SteelBlue3"             : "#4F94CD",
    "SteelBlue4"             : "#36648B",
    "DeepSkyBlue1"           : "#00BFFF",
    "DeepSkyBlue2"           : "#00B2EE",
    "DeepSkyBlue3"           : "#009ACD",
    "DeepSkyBlue4"           : "#00688B",
    "SkyBlue1"               : "#87CEFF",
    "SkyBlue2"               : "#7EC0EE",
    "SkyBlue3"               : "#6CA6CD",
    "SkyBlue4"               : "#4A708B",
    "LightSkyBlue1"          : "#B0E2FF",
    "LightSkyBlue2"          : "#A4D3EE",
    "LightSkyBlue3"          : "#8DB6CD",
    "LightSkyBlue4"          : "#607B8B",
    "SlateGray1"             : "#C6E2FF",
    "SlateGray2"             : "#B9D3EE",
    "SlateGray3"             : "#9FB6CD",
    "SlateGray4"             : "#6C7B8B",
    "LightSteelBlue1"        : "#CAE1FF",
    "LightSteelBlue2"        : "#BCD2EE",
    "LightSteelBlue3"        : "#A2B5CD",
    "LightSteelBlue4"        : "#6E7B8B",
    "LightBlue1"             : "#BFEFFF",
    "LightBlue2"             : "#B2DFEE",
    "LightBlue3"             : "#9AC0CD",
    "LightBlue4"             : "#68838B",
    "LightCyan1"             : "#E0FFFF",
    "LightCyan2"             : "#D1EEEE",
    "LightCyan3"             : "#B4CDCD",
    "LightCyan4"             : "#7A8B8B",
    "PaleTurquoise1"         : "#BBFFFF",
    "PaleTurquoise2"         : "#AEEEEE",
    "PaleTurquoise3"         : "#96CDCD",
    "PaleTurquoise4"         : "#668B8B",
    "CadetBlue1"             : "#98F5FF",
    "CadetBlue2"             : "#8EE5EE",
    "CadetBlue3"             : "#7AC5CD",
    "CadetBlue4"             : "#53868B",
    "turquoise1"             : "#00F5FF",
    "turquoise2"             : "#00E5EE",
    "turquoise3"             : "#00C5CD",
    "turquoise4"             : "#00868B",
    "cyan1"                  : "#00FFFF",
    "cyan2"                  : "#00EEEE",
    "cyan3"                  : "#00CDCD",
    "cyan4"                  : "#008B8B",
    "DarkSlateGray1"         : "#97FFFF",
    "DarkSlateGray2"         : "#8DEEEE",
    "DarkSlateGray3"         : "#79CDCD",
    "DarkSlateGray4"         : "#528B8B",
    "aquamarine1"            : "#7FFFD4",
    "aquamarine2"            : "#76EEC6",
    "aquamarine3"            : "#66CDAA",
    "aquamarine4"            : "#458B74",
    "DarkSeaGreen1"          : "#C1FFC1",
    "DarkSeaGreen2"          : "#B4EEB4",
    "DarkSeaGreen3"          : "#9BCD9B",
    "DarkSeaGreen4"          : "#698B69",
    "SeaGreen1"              : "#54FF9F",
    "SeaGreen2"              : "#4EEE94",
    "SeaGreen3"              : "#43CD80",
    "SeaGreen4"              : "#2E8B57",
    "PaleGreen1"             : "#9AFF9A",
    "PaleGreen2"             : "#90EE90",
    "PaleGreen3"             : "#7CCD7C",
    "PaleGreen4"             : "#548B54",
    "SpringGreen1"           : "#00FF7F",
    "SpringGreen2"           : "#00EE76",
    "SpringGreen3"           : "#00CD66",
    "SpringGreen4"           : "#008B45",
    "green1"                 : "#00FF00",
    "green2"                 : "#00EE00",
    "green3"                 : "#00CD00",
    "green4"                 : "#008B00",
    "chartreuse1"            : "#7FFF00",
    "chartreuse2"            : "#76EE00",
    "chartreuse3"            : "#66CD00",
    "chartreuse4"            : "#458B00",
    "OliveDrab1"             : "#C0FF3E",
    "OliveDrab2"             : "#B3EE3A",
    "OliveDrab3"             : "#9ACD32",
    "OliveDrab4"             : "#698B22",
    "DarkOliveGreen1"        : "#CAFF70",
    "DarkOliveGreen2"        : "#BCEE68",
    "DarkOliveGreen3"        : "#A2CD5A",
    "DarkOliveGreen4"        : "#6E8B3D",
    "khaki1"                 : "#FFF68F",
    "khaki2"                 : "#EEE685",
    "khaki3"                 : "#CDC673",
    "khaki4"                 : "#8B864E",
    "LightGoldenrod1"        : "#FFEC8B",
    "LightGoldenrod2"        : "#EEDC82",
    "LightGoldenrod3"        : "#CDBE70",
    "LightGoldenrod4"        : "#8B814C",
    "LightYellow1"           : "#FFFFE0",
    "LightYellow2"           : "#EEEED1",
    "LightYellow3"           : "#CDCDB4",
    "LightYellow4"           : "#8B8B7A",
    "yellow1"                : "#FFFF00",
    "yellow2"                : "#EEEE00",
    "yellow3"                : "#CDCD00",
    "yellow4"                : "#8B8B00",
    "gold1"                  : "#FFD700",
    "gold2"                  : "#EEC900",
    "gold3"                  : "#CDAD00",
    "gold4"                  : "#8B7500",
    "goldenrod1"             : "#FFC125",
    "goldenrod2"             : "#EEB422",
    "goldenrod3"             : "#CD9B1D",
    "goldenrod4"             : "#8B6914",
    "DarkGoldenrod1"         : "#FFB90F",
    "DarkGoldenrod2"         : "#EEAD0E",
    "DarkGoldenrod3"         : "#CD950C",
    "DarkGoldenrod4"         : "#8B6508",
    "RosyBrown1"             : "#FFC1C1",
    "RosyBrown2"             : "#EEB4B4",
    "RosyBrown3"             : "#CD9B9B",
    "RosyBrown4"             : "#8B6969",
    "IndianRed1"             : "#FF6A6A",
    "IndianRed2"             : "#EE6363",
    "IndianRed3"             : "#CD5555",
    "IndianRed4"             : "#8B3A3A",
    "sienna1"                : "#FF8247",
    "sienna2"                : "#EE7942",
    "sienna3"                : "#CD6839",
    "sienna4"                : "#8B4726",
    "burlywood1"             : "#FFD39B",
    "burlywood2"             : "#EEC591",
    "burlywood3"             : "#CDAA7D",
    "burlywood4"             : "#8B7355",
    "wheat1"                 : "#FFE7BA",
    "wheat2"                 : "#EED8AE",
    "wheat3"                 : "#CDBA96",
    "wheat4"                 : "#8B7E66",
    "tan1"                   : "#FFA54F",
    "tan2"                   : "#EE9A49",
    "tan3"                   : "#CD853F",
    "tan4"                   : "#8B5A2B",
    "chocolate1"             : "#FF7F24",
    "chocolate2"             : "#EE7621",
    "chocolate3"             : "#CD661D",
    "chocolate4"             : "#8B4513",
    "firebrick1"             : "#FF3030",
    "firebrick2"             : "#EE2C2C",
    "firebrick3"             : "#CD2626",
    "firebrick4"             : "#8B1A1A",
    "brown1"                 : "#FF4040",
    "brown2"                 : "#EE3B3B",
    "brown3"                 : "#CD3333",
    "brown4"                 : "#8B2323",
    "salmon1"                : "#FF8C69",
    "salmon2"                : "#EE8262",
    "salmon3"                : "#CD7054",
    "salmon4"                : "#8B4C39",
    "LightSalmon1"           : "#FFA07A",
    "LightSalmon2"           : "#EE9572",
    "LightSalmon3"           : "#CD8162",
    "LightSalmon4"           : "#8B5742",
    "orange1"                : "#FFA500",
    "orange2"                : "#EE9A00",
    "orange3"                : "#CD8500",
    "orange4"                : "#8B5A00",
    "DarkOrange1"            : "#FF7F00",
    "DarkOrange2"            : "#EE7600",
    "DarkOrange3"            : "#CD6600",
    "DarkOrange4"            : "#8B4500",
    "coral1"                 : "#FF7256",
    "coral2"                 : "#EE6A50",
    "coral3"                 : "#CD5B45",
    "coral4"                 : "#8B3E2F",
    "tomato1"                : "#FF6347",
    "tomato2"                : "#EE5C42",
    "tomato3"                : "#CD4F39",
    "tomato4"                : "#8B3626",
    "OrangeRed1"             : "#FF4500",
    "OrangeRed2"             : "#EE4000",
    "OrangeRed3"             : "#CD3700",
    "OrangeRed4"             : "#8B2500",
    "red1"                   : "#FF0000",
    "red2"                   : "#EE0000",
    "red3"                   : "#CD0000",
    "red4"                   : "#8B0000",
    "DeepPink1"              : "#FF1493",
    "DeepPink2"              : "#EE1289",
    "DeepPink3"              : "#CD1076",
    "DeepPink4"              : "#8B0A50",
    "HotPink1"               : "#FF6EB4",
    "HotPink2"               : "#EE6AA7",
    "HotPink3"               : "#CD6090",
    "HotPink4"               : "#8B3A62",
    "pink1"                  : "#FFB5C5",
    "pink2"                  : "#EEA9B8",
    "pink3"                  : "#CD919E",
    "pink4"                  : "#8B636C",
    "LightPink1"             : "#FFAEB9",
    "LightPink2"             : "#EEA2AD",
    "LightPink3"             : "#CD8C95",
    "LightPink4"             : "#8B5F65",
    "PaleVioletRed1"         : "#FF82AB",
    "PaleVioletRed2"         : "#EE799F",
    "PaleVioletRed3"         : "#CD6889",
    "PaleVioletRed4"         : "#8B475D",
    "maroon1"                : "#FF34B3",
    "maroon2"                : "#EE30A7",
    "maroon3"                : "#CD2990",
    "maroon4"                : "#8B1C62",
    "VioletRed1"             : "#FF3E96",
    "VioletRed2"             : "#EE3A8C",
    "VioletRed3"             : "#CD3278",
    "VioletRed4"             : "#8B2252",
    "magenta1"               : "#FF00FF",
    "magenta2"               : "#EE00EE",
    "magenta3"               : "#CD00CD",
    "magenta4"               : "#8B008B",
    "orchid1"                : "#FF83FA",
    "orchid2"                : "#EE7AE9",
    "orchid3"                : "#CD69C9",
    "orchid4"                : "#8B4789",
    "plum1"                  : "#FFBBFF",
    "plum2"                  : "#EEAEEE",
    "plum3"                  : "#CD96CD",
    "plum4"                  : "#8B668B",
    "MediumOrchid1"          : "#E066FF",
    "MediumOrchid2"          : "#D15FEE",
    "MediumOrchid3"          : "#B452CD",
    "MediumOrchid4"          : "#7A378B",
    "DarkOrchid1"            : "#BF3EFF",
    "DarkOrchid2"            : "#B23AEE",
    "DarkOrchid3"            : "#9A32CD",
    "DarkOrchid4"            : "#68228B",
    "purple1"                : "#9B30FF",
    "purple2"                : "#912CEE",
    "purple3"                : "#7D26CD",
    "purple4"                : "#551A8B",
    "MediumPurple1"          : "#AB82FF",
    "MediumPurple2"          : "#9F79EE",
    "MediumPurple3"          : "#8968CD",
    "MediumPurple4"          : "#5D478B",
    "thistle1"               : "#FFE1FF",
    "thistle2"               : "#EED2EE",
    "thistle3"               : "#CDB5CD",
    "thistle4"               : "#8B7B8B",
    "gray0"                  : "#000000",
    "gray1"                  : "#030303",
    "gray2"                  : "#050505",
    "gray3"                  : "#080808",
    "gray4"                  : "#0A0A0A",
    "gray5"                  : "#0D0D0D",
    "gray6"                  : "#0F0F0F",
    "gray7"                  : "#121212",
    "gray8"                  : "#141414",
    "gray9"                  : "#171717",
    "gray10"                 : "#1A1A1A",
    "gray11"                 : "#1C1C1C",
    "gray12"                 : "#1F1F1F",
    "gray13"                 : "#212121",
    "gray14"                 : "#242424",
    "gray15"                 : "#262626",
    "gray16"                 : "#292929",
    "gray17"                 : "#2B2B2B",
    "gray18"                 : "#2E2E2E",
    "gray19"                 : "#303030",
    "gray20"                 : "#333333",
    "gray21"                 : "#363636",
    "gray22"                 : "#383838",
    "gray23"                 : "#3B3B3B",
    "gray24"                 : "#3D3D3D",
    "gray25"                 : "#404040",
    "gray26"                 : "#424242",
    "gray27"                 : "#454545",
    "gray28"                 : "#474747",
    "gray29"                 : "#4A4A4A",
    "gray30"                 : "#4D4D4D",
    "gray31"                 : "#4F4F4F",
    "gray32"                 : "#525252",
    "gray33"                 : "#545454",
    "gray34"                 : "#575757",
    "gray35"                 : "#595959",
    "gray36"                 : "#5C5C5C",
    "gray37"                 : "#5E5E5E",
    "gray38"                 : "#616161",
    "gray39"                 : "#636363",
    "gray40"                 : "#666666",
    "gray41"                 : "#696969",
    "gray42"                 : "#6B6B6B",
    "gray43"                 : "#6E6E6E",
    "gray44"                 : "#707070",
    "gray45"                 : "#737373",
    "gray46"                 : "#757575",
    "gray47"                 : "#787878",
    "gray48"                 : "#7A7A7A",
    "gray49"                 : "#7D7D7D",
    "gray50"                 : "#7F7F7F",
    "gray51"                 : "#828282",
    "gray52"                 : "#858585",
    "gray53"                 : "#878787",
    "gray54"                 : "#8A8A8A",
    "gray55"                 : "#8C8C8C",
    "gray56"                 : "#8F8F8F",
    "gray57"                 : "#919191",
    "gray58"                 : "#949494",
    "gray59"                 : "#969696",
    "gray60"                 : "#999999",
    "gray61"                 : "#9C9C9C",
    "gray62"                 : "#9E9E9E",
    "gray63"                 : "#A1A1A1",
    "gray64"                 : "#A3A3A3",
    "gray65"                 : "#A6A6A6",
    "gray66"                 : "#A8A8A8",
    "gray67"                 : "#ABABAB",
    "gray68"                 : "#ADADAD",
    "gray69"                 : "#B0B0B0",
    "gray70"                 : "#B3B3B3",
    "gray71"                 : "#B5B5B5",
    "gray72"                 : "#B8B8B8",
    "gray73"                 : "#BABABA",
    "gray74"                 : "#BDBDBD",
    "gray75"                 : "#BFBFBF",
    "gray76"                 : "#C2C2C2",
    "gray77"                 : "#C4C4C4",
    "gray78"                 : "#C7C7C7",
    "gray79"                 : "#C9C9C9",
    "gray80"                 : "#CCCCCC",
    "gray81"                 : "#CFCFCF",
    "gray82"                 : "#D1D1D1",
    "gray83"                 : "#D4D4D4",
    "gray84"                 : "#D6D6D6",
    "gray85"                 : "#D9D9D9",
    "gray86"                 : "#DBDBDB",
    "gray87"                 : "#DEDEDE",
    "gray88"                 : "#E0E0E0",
    "gray89"                 : "#E3E3E3",
    "gray90"                 : "#E5E5E5",
    "gray91"                 : "#E8E8E8",
    "gray92"                 : "#EBEBEB",
    "gray93"                 : "#EDEDED",
    "gray94"                 : "#F0F0F0",
    "gray95"                 : "#F2F2F2",
    "gray96"                 : "#F5F5F5",
    "gray97"                 : "#F7F7F7",
    "gray98"                 : "#FAFAFA",
    "gray99"                 : "#FCFCFC",
    "gray100"                : "#FFFFFF",
    "dark gray"              : "#A9A9A9",
    "DarkGray"               : "#A9A9A9",
    "dark blue"              : "#00008B",
    "DarkBlue"               : "#00008B",
    "dark cyan"              : "#008B8B",
    "DarkCyan"               : "#008B8B",
    "dark magenta"           : "#8B008B",
    "DarkMagenta"            : "#8B008B",
    "dark red"               : "#8B0000",
    "DarkRed"                : "#8B0000",
    "light green"            : "#90EE90",
    "LightGreen"             : "#90EE90",
    "crimson"                : "#DC143C",
    "indigo"                 : "#4B0082",
    "olive"                  : "#808000",
    "rebecca purple"         : "#663399",
    "RebeccaPurple"          : "#663399",
    "silver"                 : "#C0C0C0",
    "teal"                   : "#008080",
}

'''
# Color
vals = [0] + list(range(95, 255+1, 40))
i = 16
for r in vals:
    for g in vals:
        for b in vals:
            print("{:3} : \"#{:02X}{:02X}{:02X}\",".format(i, r, g, b))
            i += 1

# Gray
vals = list(range(8, 255 - 18, 10))
i = 255+1 - 24
for x in vals:
    print("{:3} : \"#{:02X}{:02X}{:02X}\",".format(i, x, x, x))
    i += 1
'''

# https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
xterm_color_num_to_rgb_string = {
#  0 : "#000000",
#  1 : "#AA0000",
#  2 : "#00AA00",
#  3 : "#AA5500",
#  4 : "#0000AA",
#  5 : "#AA00AA",
#  6 : "#00AAAA",
#  7 : "#AAAAAA",
#  8 : "#555555",
#  9 : "#FF5555",
# 10 : "#55FF55",
# 11 : "#FFFF55",
# 12 : "#5555FF",
# 13 : "#FF55FF",
# 14 : "#55FFFF",
# 15 : "#FFFFFF",

 16 : "#000000",
 17 : "#00005F",
 18 : "#000087",
 19 : "#0000AF",
 20 : "#0000D7",
 21 : "#0000FF",
 22 : "#005F00",
 23 : "#005F5F",
 24 : "#005F87",
 25 : "#005FAF",
 26 : "#005FD7",
 27 : "#005FFF",
 28 : "#008700",
 29 : "#00875F",
 30 : "#008787",
 31 : "#0087AF",
 32 : "#0087D7",
 33 : "#0087FF",
 34 : "#00AF00",
 35 : "#00AF5F",
 36 : "#00AF87",
 37 : "#00AFAF",
 38 : "#00AFD7",
 39 : "#00AFFF",
 40 : "#00D700",
 41 : "#00D75F",
 42 : "#00D787",
 43 : "#00D7AF",
 44 : "#00D7D7",
 45 : "#00D7FF",
 46 : "#00FF00",
 47 : "#00FF5F",
 48 : "#00FF87",
 49 : "#00FFAF",
 50 : "#00FFD7",
 51 : "#00FFFF",
 52 : "#5F0000",
 53 : "#5F005F",
 54 : "#5F0087",
 55 : "#5F00AF",
 56 : "#5F00D7",
 57 : "#5F00FF",
 58 : "#5F5F00",
 59 : "#5F5F5F",
 60 : "#5F5F87",
 61 : "#5F5FAF",
 62 : "#5F5FD7",
 63 : "#5F5FFF",
 64 : "#5F8700",
 65 : "#5F875F",
 66 : "#5F8787",
 67 : "#5F87AF",
 68 : "#5F87D7",
 69 : "#5F87FF",
 70 : "#5FAF00",
 71 : "#5FAF5F",
 72 : "#5FAF87",
 73 : "#5FAFAF",
 74 : "#5FAFD7",
 75 : "#5FAFFF",
 76 : "#5FD700",
 77 : "#5FD75F",
 78 : "#5FD787",
 79 : "#5FD7AF",
 80 : "#5FD7D7",
 81 : "#5FD7FF",
 82 : "#5FFF00",
 83 : "#5FFF5F",
 84 : "#5FFF87",
 85 : "#5FFFAF",
 86 : "#5FFFD7",
 87 : "#5FFFFF",
 88 : "#870000",
 89 : "#87005F",
 90 : "#870087",
 91 : "#8700AF",
 92 : "#8700D7",
 93 : "#8700FF",
 94 : "#875F00",
 95 : "#875F5F",
 96 : "#875F87",
 97 : "#875FAF",
 98 : "#875FD7",
 99 : "#875FFF",
100 : "#878700",
101 : "#87875F",
102 : "#878787",
103 : "#8787AF",
104 : "#8787D7",
105 : "#8787FF",
106 : "#87AF00",
107 : "#87AF5F",
108 : "#87AF87",
109 : "#87AFAF",
110 : "#87AFD7",
111 : "#87AFFF",
112 : "#87D700",
113 : "#87D75F",
114 : "#87D787",
115 : "#87D7AF",
116 : "#87D7D7",
117 : "#87D7FF",
118 : "#87FF00",
119 : "#87FF5F",
120 : "#87FF87",
121 : "#87FFAF",
122 : "#87FFD7",
123 : "#87FFFF",
124 : "#AF0000",
125 : "#AF005F",
126 : "#AF0087",
127 : "#AF00AF",
128 : "#AF00D7",
129 : "#AF00FF",
130 : "#AF5F00",
131 : "#AF5F5F",
132 : "#AF5F87",
133 : "#AF5FAF",
134 : "#AF5FD7",
135 : "#AF5FFF",
136 : "#AF8700",
137 : "#AF875F",
138 : "#AF8787",
139 : "#AF87AF",
140 : "#AF87D7",
141 : "#AF87FF",
142 : "#AFAF00",
143 : "#AFAF5F",
144 : "#AFAF87",
145 : "#AFAFAF",
146 : "#AFAFD7",
147 : "#AFAFFF",
148 : "#AFD700",
149 : "#AFD75F",
150 : "#AFD787",
151 : "#AFD7AF",
152 : "#AFD7D7",
153 : "#AFD7FF",
154 : "#AFFF00",
155 : "#AFFF5F",
156 : "#AFFF87",
157 : "#AFFFAF",
158 : "#AFFFD7",
159 : "#AFFFFF",
160 : "#D70000",
161 : "#D7005F",
162 : "#D70087",
163 : "#D700AF",
164 : "#D700D7",
165 : "#D700FF",
166 : "#D75F00",
167 : "#D75F5F",
168 : "#D75F87",
169 : "#D75FAF",
170 : "#D75FD7",
171 : "#D75FFF",
172 : "#D78700",
173 : "#D7875F",
174 : "#D78787",
175 : "#D787AF",
176 : "#D787D7",
177 : "#D787FF",
178 : "#D7AF00",
179 : "#D7AF5F",
180 : "#D7AF87",
181 : "#D7AFAF",
182 : "#D7AFD7",
183 : "#D7AFFF",
184 : "#D7D700",
185 : "#D7D75F",
186 : "#D7D787",
187 : "#D7D7AF",
188 : "#D7D7D7",
189 : "#D7D7FF",
190 : "#D7FF00",
191 : "#D7FF5F",
192 : "#D7FF87",
193 : "#D7FFAF",
194 : "#D7FFD7",
195 : "#D7FFFF",
196 : "#FF0000",
197 : "#FF005F",
198 : "#FF0087",
199 : "#FF00AF",
200 : "#FF00D7",
201 : "#FF00FF",
202 : "#FF5F00",
203 : "#FF5F5F",
204 : "#FF5F87",
205 : "#FF5FAF",
206 : "#FF5FD7",
207 : "#FF5FFF",
208 : "#FF8700",
209 : "#FF875F",
210 : "#FF8787",
211 : "#FF87AF",
212 : "#FF87D7",
213 : "#FF87FF",
214 : "#FFAF00",
215 : "#FFAF5F",
216 : "#FFAF87",
217 : "#FFAFAF",
218 : "#FFAFD7",
219 : "#FFAFFF",
220 : "#FFD700",
221 : "#FFD75F",
222 : "#FFD787",
223 : "#FFD7AF",
224 : "#FFD7D7",
225 : "#FFD7FF",
226 : "#FFFF00",
227 : "#FFFF5F",
228 : "#FFFF87",
229 : "#FFFFAF",
230 : "#FFFFD7",
231 : "#FFFFFF",

232 : "#080808",
233 : "#121212",
234 : "#1C1C1C",
235 : "#262626",
236 : "#303030",
237 : "#3A3A3A",
238 : "#444444",
239 : "#4E4E4E",
240 : "#585858",
241 : "#626262",
242 : "#6C6C6C",
243 : "#767676",
244 : "#808080",
245 : "#8A8A8A",
246 : "#949494",
247 : "#9E9E9E",
248 : "#A8A8A8",
249 : "#B2B2B2",
250 : "#BCBCBC",
251 : "#C6C6C6",
252 : "#D0D0D0",
253 : "#DADADA",
254 : "#E4E4E4",
255 : "#EEEEEE",
}
