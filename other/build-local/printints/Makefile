# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# default install paths
PREFIX ?= /usr/local
MANDIR ?= $(PREFIX)/share/man

CPPFLAGS += -MMD -MP
#CXXFLAGS +=
LDLIBS += -lfmt

SRCS = $(wildcard *.cpp)
DEPS = $(SRCS:.cpp=.d)
OBJS = $(SRCS:.cpp=.o)

BIN = $(notdir $(CURDIR))

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) *~ core core.[[:digit:]]*

install: $(BIN)
	@mkdir --verbose --parents -- "$(DESTDIR)$(PREFIX)/bin"
	@cp --verbose --update -- $(BIN) "$(DESTDIR)$(PREFIX)/bin"
	@chmod --changes --preserve-root -- 755 "$(DESTDIR)$(PREFIX)/bin/$(BIN)"

uninstall:
	@$(RM) --verbose -- "$(DESTDIR)$(PREFIX)/bin/$(BIN)"

lint:
	clang-tidy --quiet $(SRCS) -- $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: all install clean uninstall lint

-include $(DEPS)
