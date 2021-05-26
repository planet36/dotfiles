# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# default install paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

INCS =
SRCS = $(wildcard *.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

DEPFLAGS += -MMD -MP
CFLAGS += $(INCS) $(DEPFLAGS)
#LDFLAGS +=

BIN = $(notdir $(CURDIR))

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

install: $(BIN)
	@mkdir --verbose --parents -- ~/.local/bin/
	@cp --verbose --update -- $(BIN) ~/.local/bin/

clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) *~ core core.[[:digit:]]*

uninstall: clean
	@$(RM) --verbose -- ~/.local/bin/$(BIN)

lint:
	clang-tidy --quiet $(SRCS) -- $(CFLAGS) $(LDFLAGS)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: install clean uninstall lint

-include $(DEPS)
