#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

set -e

cd "$SCRIPT_DIR"

OUT_DIR="$(git rev-parse --show-toplevel)"/link/.local/include

calc -d -m 4 -f generate-series-approx-coeff-aux-lat.cal > "$OUT_DIR"/aux-lat-conv.hpp
calc -d -m 4 -f generate-series-approx-coeff-tm.cal      > "$OUT_DIR"/utm-ups-const.hpp
python3 generate-ascii.py                                > "$OUT_DIR"/ascii.hpp
python3 generate-gcc-machine-modes-typedefs.py           > "$OUT_DIR"/gcc-machine-modes-typedefs.hpp
python3 generate-math-const.py                           > "$OUT_DIR"/math-const.hpp

cat <<EOT
# Run these commands:

git diff \
$OUT_DIR/{ascii.hpp,aux-lat-conv.hpp,gcc-machine-modes-typedefs.hpp,math-const.hpp,utm-ups-const.hpp}

git commit -m 'Update generated source code files' \
$OUT_DIR/{ascii.hpp,aux-lat-conv.hpp,gcc-machine-modes-typedefs.hpp,math-const.hpp,utm-ups-const.hpp}
EOT
