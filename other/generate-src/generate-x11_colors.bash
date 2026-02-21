#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

set -e

curl --silent --show-error https://gitlab.freedesktop.org/xorg/xserver/-/raw/master/dix/color.c | \
sed -n -e '/static const BuiltinColor BuiltinColors\[\] = {/, /};/ p' | \
python3 filter-oscolor.py

cat <<EOT

rgb_vals = [0] + list(range(95, 255+1, 40))

num_to_rgb = {}

# Adapted from:
# https://github.com/pygments/pygments/blob/master/pygments/formatters/terminal256.py#L172

# ANSI Colors (16..231)
for i in range(216):
    r = rgb_vals[(i // 36) % 6]
    g = rgb_vals[(i // 6) % 6]
    b = rgb_vals[i % 6]
    num = i + 16
    num_to_rgb[num] = (r, g, b)

# ANSI Grays (232..255)
for i in range(24):
    v = i * 10 + 8
    num = i + 232
    num_to_rgb[num] = (v, v, v)

del rgb_vals
EOT
