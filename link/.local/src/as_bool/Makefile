
INCS =
SRCS = $(wildcard *.c)
DEPS = $(SRCS:.c=.d)
OBJS = $(SRCS:.c=.o)

CFLAGS += -Wno-cast-qual -Os $(INCS)
DEPFLAGS += -MMD -MP
#LDFLAGS +=

BIN = $(notdir $(PWD))

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(DEPFLAGS) $(CFLAGS) -c $<

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
