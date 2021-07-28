#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

SCRIPT_NAME="$(basename -- "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname -- "${BASH_SOURCE[0]}")"

set -e

cd "$SCRIPT_DIR"

OUT_DIR="$HOME"/.local/include

calc -d -m 4 -f generate-series-approx-coeff-aux-lat.cal > "$OUT_DIR"/aux-lat-conv.hpp
calc -d -m 4 -f generate-series-approx-coeff-tm.cal      > "$OUT_DIR"/utm-ups-const.hpp
python3 generate-gcc-machine-modes-typedefs.py           > "$OUT_DIR"/gcc-machine-modes-typedefs.hpp
python3 generate-math-const.py                           > "$OUT_DIR"/math-const.hpp
