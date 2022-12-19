#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck disable=SC2034

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

set -e

cd "$SCRIPT_DIR"

OUT_DIR="$(git rev-parse --show-toplevel)/link/.local"

calc -d -m 4 -f generate-series-approx-coeff-aux-lat.cal > "$OUT_DIR"/include/aux-lat-conv.hpp
calc -d -m 4 -f generate-series-approx-coeff-tm.cal      > "$OUT_DIR"/include/utm-ups-const.hpp
python3 generate-ascii.py                                > "$OUT_DIR"/include/ascii.hpp
python3 generate-gcc-machine-modes-typedefs.py           > "$OUT_DIR"/include/gcc-machine-modes-typedefs.hpp
python3 generate-math-const.py                           > "$OUT_DIR"/include/math-const.hpp
bash generate-x11_colors.bash                            > "$OUT_DIR"/lib/python/x11_colors.py

cat <<EOT
# Run these commands:

git diff \
$OUT_DIR/include/{ascii,aux-lat-conv,gcc-machine-modes-typedefs,math-const,utm-ups-const}.hpp \
$OUT_DIR/lib/python/x11_colors.py

git commit -m 'Update generated source code files' \
$OUT_DIR/include/{ascii,aux-lat-conv,gcc-machine-modes-typedefs,math-const,utm-ups-const}.hpp \
$OUT_DIR/lib/python/x11_colors.py
EOT
