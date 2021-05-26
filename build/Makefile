# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

SUBDIRS=$(sort $(wildcard */))

build:
	$(foreach DIR, $(SUBDIRS), $(MAKE) -C $(DIR);)

clean install uninstall lint:
	$(foreach DIR, $(SUBDIRS), $(MAKE) -C $(DIR) $@;)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: build clean install uninstall lint
