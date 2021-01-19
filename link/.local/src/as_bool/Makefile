
INCS =
SRCS = $(wildcard *.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

DEPFLAGS += -MMD -MP
CFLAGS += -Wno-cast-qual -Os $(INCS) $(DEPFLAGS)
#LDFLAGS +=

BIN = $(notdir $(PWD))

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

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
