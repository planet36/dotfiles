# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

BUILD_DIRS = \
dwm \
slstatus \
st \
stw

# These will be cloned but not built
CLONE_ONLY_DIRS = \
arch-install \
dwm-suckless \
slstatus-suckless \
st-suckless

build: clone
	$(foreach DIR, $(BUILD_DIRS), $(MAKE) -C $(DIR);)

clone: | $(BUILD_DIRS) $(CLONE_ONLY_DIRS)

clean install lint uninstall: clone
	$(foreach DIR, $(BUILD_DIRS), $(MAKE) -C $(DIR) $@;)

arch-install:
	git clone https://github.com/planet36/arch-install.git

# My repos (forked from suckless)
# Clone and add remotes to the respective suckless repos
dwm slstatus st:
	git clone https://github.com/planet36/$@.git
	cd $@ ; \
	git remote add suckless https://git.suckless.org/$@ ; \
	git remote set-url --push suckless DISABLE ; \
	git fetch suckless ; \
	cd - > /dev/null

stw:
	git clone https://github.com/sineemore/stw.git

dwm-suckless slstatus-suckless st-suckless:
	git clone https://git.suckless.org/$(subst -suckless,,$@) $@

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: build clone clean install lint uninstall
