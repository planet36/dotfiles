# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

# default install paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

INCS =
SRCS = $(wildcard *.cpp)
DEPS = $(SRCS:.cpp=.d)
OBJS = $(SRCS:.cpp=.o)

DEPFLAGS += -MMD -MP
CXXFLAGS += -std=c++17 $(INCS) $(DEPFLAGS)
#LDFLAGS += -lfmt

BIN = $(notdir $(CURDIR))

$(BIN): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) *~ core core.[[:digit:]]*

install: $(BIN)
	@mkdir --verbose --parents -- "$(DESTDIR)$(PREFIX)/bin"
	@cp --verbose --update -- $(BIN) "$(DESTDIR)$(PREFIX)/bin"
	@chmod --changes --preserve-root -- 755 "$(DESTDIR)$(PREFIX)/bin/$(BIN)"

uninstall:
	@$(RM) --verbose -- "$(DESTDIR)$(PREFIX)/bin/$(BIN)"

lint:
	clang-tidy --quiet $(SRCS) -- $(CXXFLAGS) $(LDFLAGS)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: install clean uninstall lint

-include $(DEPS)
