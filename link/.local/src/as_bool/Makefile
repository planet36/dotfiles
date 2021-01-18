
INCS = 
HDRS = $(wildcard *.h)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS += -Wno-cast-qual -Os $(INCS)
#LDFLAGS += -lfmt

EXECUTABLE = $(notdir $(PWD))

# https://www.gnu.org/software/make/manual/make.html#Phony-Targets
.PHONY: all
all: $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

$(OBJS): $(HDRS)

$(EXECUTABLE): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

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

