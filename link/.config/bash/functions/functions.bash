# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# shellcheck shell=bash

# shellcheck disable=SC2059
# SC2059: Don't use variables in the printf format string. Use printf "..%s.." "$foo".

# to print dots:
# yes '. ' | head -n 1000 | tr -d '\n' | fold

# get tar member
# tar -x -v -f AVCATT_ONESAF_cm.20200109.0.tgz -C ~/tmp AVCATT_ONESAF_cm.20200109.0/PAIR

# How to replace text using grep and perl...
# rg -l -P -- 'OLD' | xargs perl -p -i.bak -e 's|OLD|NEW|g;'
# rg -l -P -- 'OLD' | xargs perl -p -i~ -e 's|OLD|NEW|g;'
