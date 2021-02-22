
INCS =
SRCS = $(wildcard *.cpp)
DEPS = $(SRCS:.cpp=.d)
OBJS = $(SRCS:.cpp=.o)

DEPFLAGS += -MMD -MP
CXXFLAGS += -std=c++17 $(INCS) $(DEPFLAGS)
#LDFLAGS += -lfmt

BIN = $(notdir $(PWD))

$(BIN): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

install: $(BIN)
	@mkdir --verbose --parents -- ~/.local/bin/
	@cp --verbose --update -- $(BIN) ~/.local/bin/

clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) *~ core core.[[:digit:]]*

distclean: clean
	@$(RM) --verbose -- ~/.local/bin/$(BIN)

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: install clean distclean

-include $(DEPS)
