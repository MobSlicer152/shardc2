%.c.o: %.c
	@printf "\tCC\t$<"
	@$(CC) -c -o $<.o $(CFLAGS) $(CPPFLAGS) $<

TEST_SRCS = src/test.c
TEST_OBJS = $(TEST_SRCS:.c=.c.o)

$(TEST_OBJS): $(TEST_SRC)

$(BINDIR)/test: $(TEST_OBJS)

test: $(BINDIR)/test

