# SPDX-FileCopyrightText: Steven Ward
# SPDX-License-Identifier: OSL-3.0

export LC_ALL := C

CPPFLAGS = -MMD -MP
CPPFLAGS += -D_GNU_SOURCE
CPPFLAGS += `pkg-config --cflags libutf8proc`

CFLAGS += $(OPTIMIZE_OPTIONS)
CFLAGS += -Werror
CFLAGS += -Wno-error=pedantic
CFLAGS += -Wno-error=useless-cast
CFLAGS += -Wno-unused-function

CXXFLAGS += $(OPTIMIZE_OPTIONS)
CXXFLAGS += -Werror
CXXFLAGS += -Wno-error=pedantic
CXXFLAGS += -Wno-error=useless-cast
CXXFLAGS += -Wno-unused-function

#LDFLAGS +=

#LDLIBS +=
LDLIBS += `pkg-config --libs fmt libutf8proc`

C_HDRS := $(wildcard *.h)
CXX_HDRS := $(wildcard *.hpp)
DEPS := $(C_HDRS:.h=.d) $(CXX_HDRS:.hpp=.d)
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
