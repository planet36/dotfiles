
INCS =
SRCS = $(wildcard *.cpp)
DEPS = $(SRCS:.cpp=.d)
OBJS = $(SRCS:.cpp=.o)

CXXFLAGS += -std=c++17 -Os $(INCS)
DEPFLAGS += -MMD -MP
#LDFLAGS += -lfmt

BIN = $(notdir $(PWD))

$(BIN): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c $<

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: install
install: $(BIN)
	@mkdir --verbose --parents -- ~/.local/bin/
	@cp --verbose --update -- $(BIN) ~/.local/bin/

.PHONY: clean
clean:
	@$(RM) --verbose -- $(BIN) $(OBJS) $(DEPS) *~ core core.[[:digit:]]*

.PHONY: distclean
distclean: clean
	@$(RM) --verbose -- ~/.local/bin/$(BIN)

-include $(DEPS)
