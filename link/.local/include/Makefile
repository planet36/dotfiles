# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

export LC_ALL := C

CPPFLAGS = -MMD -MP
CPPFLAGS += `pkg-config --cflags libutf8proc`

CFLAGS = -pipe -Wall -Wextra -Wpedantic -Wfatal-errors
CFLAGS += -Wno-unused-function
CFLAGS += -std=gnu23
CFLAGS += -O3 -flto=auto -march=native -fno-math-errno
CFLAGS += -Werror -Wno-error=pedantic

CXXFLAGS = -pipe -Wall -Wextra -Wpedantic -Wfatal-errors
CXXFLAGS += -Wno-unused-function
CXXFLAGS += -std=gnu++26
CXXFLAGS += -O3 -flto=auto -march=native -fno-math-errno
CXXFLAGS += -Werror -Wno-error=pedantic

#LDFLAGS +=

#LDLIBS +=
LDLIBS += `pkg-config --libs fmt libutf8proc`

C_HDRS := $(wildcard *.h)
CXX_HDRS := $(wildcard *.hpp)
DEPS = $(C_HDRS:.h=.d) $(CXX_HDRS:.hpp=.d)
OBJS := $(addsuffix .o, $(basename $(C_HDRS))) $(addsuffix .o, $(basename $(CXX_HDRS)))
BINS := $(addsuffix .out, $(basename $(C_HDRS))) $(addsuffix .out, $(basename $(CXX_HDRS)))

all: $(OBJS)

bins: $(BINS)

objs: $(OBJS)

%.o: %.h
	@# This is done to prevent "warning: #pragma once in main file".
	-printf '#include "%s"\n' $< | LC_ALL=C $(CC) $(CPPFLAGS) $(CFLAGS) -x c -o $@ - -c

%.o: %.hpp
	@# This is done to prevent "warning: #pragma once in main file".
	-printf '#include "%s"\n' $< | LC_ALL=C $(CXX) $(CPPFLAGS) $(CXXFLAGS) -x c++ -o $@ - -c

%.out: %.h
	@# This is done to prevent "warning: #pragma once in main file".
	-printf '#include "%s"\nint main(){return 0;}\n' $< | LC_ALL=C $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -x c -o $@ - $(LDLIBS)

%.out: %.hpp
	@# This is done to prevent "warning: #pragma once in main file".
	-printf '#include "%s"\nint main(){return 0;}\n' $< | LC_ALL=C $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -x c++ -o $@ - $(LDLIBS)

clean:
	@$(RM) --verbose -- $(DEPS) $(OBJS) $(BINS)

lint:
	-clang-tidy --quiet $(C_HDRS) -- $(CPPFLAGS) $(CFLAGS)
	-clang-tidy --quiet $(CXX_HDRS) -- $(CPPFLAGS) $(CXXFLAGS)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: all bins objs clean lint

-include $(DEPS)
