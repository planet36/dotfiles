# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

TOPTARGETS := all clone clean install uninstall lint

BUILD_DIRS = \
dwm \
PractRand \
slstatus \
st \
stw

# These will be cloned but not built
CLONE_ONLY_DIRS = \
arch-install \
ecef-geodetic \
dwm-suckless \
prng-test-bench \
randp \
slstatus-suckless \
st-suckless \
stw-sineemore

SUBDIRS := $(BUILD_DIRS) $(CLONE_ONLY_DIRS)

all: clone
	$(foreach DIR, $(BUILD_DIRS), $(MAKE) -C $(DIR);)

clone: | $(SUBDIRS)

clean install uninstall lint: clone
	$(foreach DIR, $(BUILD_DIRS), $(MAKE) -C $(DIR) $@;)

arch-install ecef-geodetic PractRand:
	git clone --quiet https://github.com/planet36/$@.git

# My repos (forked from suckless)
# Clone and add upstream remotes
dwm slstatus st:
	git clone --quiet https://github.com/planet36/$@.git
	cd $@ ; \
	git remote add suckless https://git.suckless.org/$@ ; \
	git remote set-url --push suckless DISABLE ; \
	git fetch --quiet suckless ; \
	cd - > /dev/null

dwm-suckless slstatus-suckless st-suckless:
	git clone --quiet https://git.suckless.org/$(subst -suckless,,$@) $@

stw-sineemore:
	git clone --quiet https://github.com/sineemore/$(subst -sineemore,,$@).git $@

# My repos (forked from github)
# Clone and add upstream remotes
stw:
	git clone --quiet https://github.com/planet36/$@.git
	cd $@ ; \
	git remote add upstream https://github.com/sineemore/$@.git ; \
	git remote set-url --push upstream DISABLE ; \
	git fetch --quiet upstream ; \
	cd - > /dev/null

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: $(TOPTARGETS)
