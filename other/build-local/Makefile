# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: MPL-2.0

# https://stackoverflow.com/a/17845120/1892784

TOPTARGETS = all clean install uninstall lint

SUBDIRS = $(wildcard */.)

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: $(TOPTARGETS) $(SUBDIRS)
