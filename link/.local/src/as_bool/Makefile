
INCS = 
HDRS = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

CXXFLAGS += -Os $(INCS)
#LDFLAGS += -lfmt

EXECUTABLE = $(notdir $(PWD))

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: all
all: $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

$(OBJS): $(HDRS)

$(EXECUTABLE): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

.PHONY: install
install: $(EXECUTABLE)
	@mkdir --verbose --parents -- ~/.local/bin/
	@cp --verbose --update -- $(EXECUTABLE) ~/.local/bin/

.PHONY: clean
clean:
	@$(RM) --verbose -- $(EXECUTABLE) *.o *~ core core.[[:digit:]]*

.PHONY: distclean
distclean: clean
	@$(RM) --verbose -- ~/.local/bin/$(EXECUTABLE)

