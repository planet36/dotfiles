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

install: $(BIN)
	@mkdir --verbose --parents -- ~/.local/bin/
	@cp --verbose --update -- $(BIN) ~/.local/bin/

clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) *~ core core.[[:digit:]]*

uninstall: clean
	@$(RM) --verbose -- ~/.local/bin/$(BIN)

lint:
	clang-tidy --quiet $(SRCS) -- $(CXXFLAGS) $(LDFLAGS)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: install clean uninstall lint

-include $(DEPS)
