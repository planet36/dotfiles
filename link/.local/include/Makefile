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
DEPS := $(addsuffix -c.d, $(basename $(C_HDRS))) $(addsuffix -cpp.d, $(basename $(CXX_HDRS)))
OBJS := $(addsuffix -c.o, $(basename $(C_HDRS))) $(addsuffix -cpp.o, $(basename $(CXX_HDRS)))
BINS := $(addsuffix -c.out, $(basename $(C_HDRS))) $(addsuffix -cpp.out, $(basename $(CXX_HDRS)))

all: $(OBJS)

bins: $(BINS)

objs: $(OBJS)

%-c.o: %.h
	@# This is done to prevent "warning: #pragma once in main file".
	-printf '#include "%s"\n' $< | LC_ALL=C $(CC) $(CPPFLAGS) $(CFLAGS) -x c -o $@ - -c

%-cpp.o: %.hpp
	@# This is done to prevent "warning: #pragma once in main file".
	-printf '#include "%s"\n' $< | LC_ALL=C $(CXX) $(CPPFLAGS) $(CXXFLAGS) -x c++ -o $@ - -c

%-c.out: %.h
	@# This is done to prevent "warning: #pragma once in main file".
	-printf '#include "%s"\nint main(){return 0;}\n' $< | LC_ALL=C $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -x c -o $@ - $(LDLIBS)

%-cpp.out: %.hpp
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
