%.c.o: %.c
	@printf "\tCC\t$<\n"
	@$(CC) -c -o $<.o $(CFLAGS) $(CPPFLAGS) $<

%.s.o: %.s
	@printf "\tAS\t$<\n"
	@$(AS) -o $<.o $(ASFLAGS) $<

# Sources and objects
LIBC_PLATFORM_ARCH_SPECIFIC_SRCS = src/$(PLATFORM)/$(ARCH)/crt0.s
LIBC_PLATFORM_ARCH_SPECIFIC_OBJS = $($(LIBC_PLATFORM_ARCH_SPECIFIC_SRCS:.c=.c.o):.s=.s.o)

$(LIBC_PLATFORM_ARCH_SPECIFIC_OBJS): $(LIBC_PLATFORM_ARCH_SPECIFIC_SRCS)

LIBC_OBJS = $(LIBC_PLATFORM_ARCH_SPECIFIC_OBJS)

$(BINDIR)/libshardc2.a: $(LIBC_OBJS)

libc: $(BINDIR)/libshardc2.a

