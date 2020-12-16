
INCLUDE :=
CXXFLAGS := -Wall -std=c++17 -Os
DEBUG :=
#LDFLAGS := -lfmt
LDFLAGS :=

#HEADER := $(notdir $(PWD)).h
HEADER :=

#SOURCE := $(notdir $(PWD)).cpp
#EXECUTABLE := $(notdir $(PWD))
EXECUTABLE := dir_is_empty
SOURCE := $(EXECUTABLE).cpp

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) $(HEADER)
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(DEBUG) -o $@ $(SOURCE) $(LDFLAGS)

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

