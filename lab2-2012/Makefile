PROJ	:= 5
EMPTY	:=
SPACE	:= $(EMPTY) $(EMPTY)
SLASH	:= /

V       := @

GCCPREFIX:=mips-sde-elf-

# eliminate default suffix rules
.SUFFIXES: .c .S .h

# define compiler and flags

HOSTCC		:= gcc
HOSTCFLAGS	:= -g -Wall -O2

GDB		:= $(GCCPREFIX)gdb

THUMIPSCC		:= ./thumips-cc
CLANG := clang
#CC :=$(GCCPREFIX)gcc
CFLAGS	:= -fno-builtin -nostdlib  -nostdinc
CTYPE	:= c S

LD      := $(GCCPREFIX)ld
AS      := $(GCCPREFIX)as -EL -g -mips32 -xgot
LDFLAGS	+= -nostdlib

OBJCOPY := $(GCCPREFIX)objcopy
OBJDUMP := $(GCCPREFIX)objdump

COPY	:= cp
MKDIR   := mkdir -p
MV		:= mv
RM		:= rm -f
AWK		:= awk
SED		:= sed
SH		:= sh
TR		:= tr
TOUCH	:= touch -c

TAR		:= tar
ZIP		:= gzip

OBJDIR	:= obj
BINDIR	:= bin



# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# include kernel/user

INCLUDE	+= libs/

#CFLAGS	+= $(addprefix -I,$(INCLUDE))

LIBDIR	+= libs


# -------------------------------------------------------------------
# kernel

$(kernel): $(KOBJS) tools/kernel.ld

MODULES   := init libs debug driver trap mm sync
SRC_DIR   := $(addprefix kern/,$(MODULES))
BUILD_DIR := $(addprefix obj/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ       := $(patsubst kern/%.c,obj/%.o,$(SRC))
ASMSRC    := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.S))
OBJ       += $(patsubst kern/%.S,obj/%.o,$(ASMSRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.c $(SRC_DIR)
vpath %.S $(SRC_DIR)

#	$(CC) $(INCLUDES) -EL -G0 -c -nostdlib -nostdinc -fno-builtin  $$< -o $$@
define make-goal
$1/%.o: %.c
	$(THUMIPSCC) "$(INCLUDES) $(CFLAGS)"  $$<  $$@

$1/%.o: %.S
	$(CLANG) $(INCLUDES) -D__ASSEMBLY__ -E $$< | $(AS) -o $$@

endef

.PHONY: all checkdirs clean 

all: checkdirs obj/ucore-kernel


obj/ucore-kernel: $(OBJ) tools/kernel.ld
	$(LD) -nostdlib -n -G 0 -static -T tools/kernel.ld $(OBJ) -o $@


checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))


