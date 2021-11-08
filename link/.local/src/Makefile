# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

REPO_DIRS = \
dwm \
slstatus \
st \
stw

build: clone
	$(foreach DIR, $(REPO_DIRS), $(MAKE) -C $(DIR);)

clone: | $(REPO_DIRS)

clean install lint uninstall: clone
	$(foreach DIR, $(REPO_DIRS), $(MAKE) -C $(DIR) $@;)

# My repos
# These repos were forked from suckless
# Add remotes to the suckless repos
dwm slstatus st:
	#git@github.com:planet36/$@.git
	git clone https://github.com/planet36/$@.git
	cd $@ ; \
	git remote add suckless https://git.suckless.org/$@ ; \
	git remote set-url --push suckless DISABLE ; \
	git fetch suckless ; \
	cd - > /dev/null

stw:
	git clone https://github.com/sineemore/stw.git

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: build clone clean install lint uninstall
