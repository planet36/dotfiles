# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# default install paths
PREFIX ?= /usr/local
MANPREFIX = $(PREFIX)/share/man

SRCS = $(wildcard *.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

CPPFLAGS += -MMD -MP
CFLAGS += -D_GNU_SOURCE
#LDFLAGS +=

BIN = $(notdir $(CURDIR))

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) *~ core core.[[:digit:]]*

install: $(BIN)
	@mkdir --verbose --parents -- "$(DESTDIR)$(PREFIX)/bin"
	@cp --verbose --update -- $(BIN) "$(DESTDIR)$(PREFIX)/bin"
	@chmod --changes --preserve-root -- 755 "$(DESTDIR)$(PREFIX)/bin/$(BIN)"

uninstall:
	@$(RM) --verbose -- "$(DESTDIR)$(PREFIX)/bin/$(BIN)"

lint:
	clang-tidy --quiet $(SRCS) -- $(CPPFLAGS) $(CFLAGS) $(LDFLAGS)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: install clean uninstall lint

-include $(DEPS)
