export

# Directories
ROOT = $(strip $(shell pwd))
BINDIR := $(ROOT)/bin

# Architecture and platform
PLATFORM := $(strip $(guile (string-downcase "$(shell uname -s)")))
ARCH := $(strip $(shell uname -m))

# Basic tools
CC := clang
LD := $(CC)
AR := ar
AS := nasm

ifeq ($(strip $(SHELL)), cmd)
	MKDIR := mkdir
else
	MKDIR := mkdir -p
endif

# Flags
INCLUDES += $(addprefix -I, $(ROOT)/include)
LIBDIRS += $(addprefix -L, $(BINDIR))
LDLIBS +=
ASFLAGS += $(INCLUDES) -felf64
CFLAGS += $(ARCH_CFLAGS) -fPIC -ffreestanding
CPPFLAGS += $(INCLUDES)
LDFLAGS += -nostdlib

# Phony targets
.PHONY: all clean clean-build help info list targets libc test

# Rules
all: libc test

CLEANFILES = $(BINDIR) $(shell find -type f -regex '.*\.o')
clean:
	@printf "\tCLEAN\t$(CLEANFILES)\n"

# It's downright evil not to have a target like this in your Makefile
help:
	@printf -- "---<[ SHARDC2 MAKEFILE INFORMATION ]>---\n"
	@printf "\nThese targets are available:\n"
	@printf "all\t\t-\tBuild everything\n"
	@printf "clean-build\t-\tClean, then build everything\n"
	@printf "clean\t\t-\tClean built files\n"
	@printf "help\t\t-\tDisplay this help\n"
	@printf "info\t\t-\tSame as help\n"
	@printf "list\t\t-\tSame as help\n"
	@printf "targets\t\t-\tSame as help\n"
	@printf "Default target is all\n"
	@printf "\nUsing these variables:\n"
	@printf "ROOT\t\t=\t$(ROOT)\n"
	@printf "BINDIR\t\t=\t$(BINDIR)\n"
	@printf "CC\t\t=\t$(CC)\n"
	@printf "AR\t\t=\t$(AR)\n"
	@printf "MKDIR\t\t=\t$(MKDIR)\n"
	@printf "INCLUDES\t=\t$(INCLUDES)\n"
	@printf "LIBDIRS\t\t=\t$(LIBDIRS)\n"
	@printf "LDLIBS\t\t=\t$(LDLIBS)\n"
	@printf "ASFLAGS\t\t=\t$(ASFLAGS)\n"
	@printf "CFLAGS\t\t=\t$(CFLAGS)\n"
	@printf "CPPFLAGS\t=\t$(CPPFLAGS)\n"
	@printf "LDFLAGS\t\t=\t$(LDFLAGS)\n"
	@printf "CLEANFILES\t=\t$(CLEANFILES)\n"
	@printf "PLATFORM\t=\t$(PLATFORM)\n"
	@printf "ARCH\t\t=\t$(ARCH)\n"

info: help
list: help
targets: help

$(BINDIR):
	$(MKDIR) $(BINDIR)

libc: $(BINDIR)
	@printf "\tDESCEND\tlibc\n"
	@$(MAKE) -q -C $(ROOT)/libc libc

test: $(BINDIR) libc
	@printf "\tDESCEND\ttest\n"
	@$(MAKE) -q -C $(ROOT)/test test

