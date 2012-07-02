CLANG=clang
CFLAGS=-O0 -emit-llvm -c  -g
LLVM_BIN=~/cpu/llvm-thumips/llvm-3.1.src/Release+Asserts/bin
LLC=$(LLVM_BIN)/llc -march=mipsel
GCC_PREFIX=/home/guest/cpu/llvm_install/bin/mipsel-linux-
#GCC_PREFIX=mips-sde-elf-
AS=$(GCC_PREFIX)as -EL -g -mips1
LD=$(GCC_PREFIX)ld

all: test.o

test.o: test.c
	$(CLANG) $(CFLAGS) -o test.bc $^
	$(LLC) test.bc 
	$(AS) -KPIC -o $@ test.s 

clean:
	-rm a.out *.o test.bc test.s
