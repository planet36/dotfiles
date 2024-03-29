#!/usr/bin/bash
# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# Run this script from the target directory.

# https://go.dev/blog/go-fonts
# https://go.googlesource.com/image/+/master/font/gofont/ttfs/

curl -O -L https://go.googlesource.com/image/+archive/master/font/gofont/ttfs.tar.gz

# Files in ttfs.tar.gz have timestamps in the future
# Use -m to not extract file modified times
tar -x -m -f ttfs.tar.gz

rm --verbose ttfs.tar.gz

