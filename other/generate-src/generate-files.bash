#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck disable=SC2034

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

set -e

cd "$SCRIPT_DIR"

OUT_DIR="$(git rev-parse --show-toplevel)/link/.local"

python3 generate-ascii.py                                > "$OUT_DIR"/include/ascii.hpp
python3 generate-bit-patterns.py                         > "$OUT_DIR"/include/bit_patterns.hpp
python3 generate-gcc-machine-modes-typedefs.py           > "$OUT_DIR"/include/gcc-machine-modes-typedefs.hpp
python3 generate-math-const.py                           > "$OUT_DIR"/include/math-const.hpp
bash generate-x11_colors.bash                            > "$OUT_DIR"/lib/python/x11_colors.py

cat <<EOT

# Run these commands:

git diff \
$OUT_DIR/include/{ascii,bit_patterns,gcc-machine-modes-typedefs,math-const}.hpp \
$OUT_DIR/lib/python/x11_colors.py

git commit -m 'Update generated source code files' \
$OUT_DIR/include/{ascii,bit_patterns,gcc-machine-modes-typedefs,math-const}.hpp \
$OUT_DIR/lib/python/x11_colors.py

# Or reset the changes

git checkout \
$OUT_DIR/include/{ascii,bit_patterns,gcc-machine-modes-typedefs,math-const}.hpp \
$OUT_DIR/lib/python/x11_colors.py

EOT
