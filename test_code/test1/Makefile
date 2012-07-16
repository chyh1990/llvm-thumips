#CLANG=clang
CFLAGS=-G0 -EL -mips1 -O0 -fno-delayed-branch -Wa,-O0 -nostdinc
#LLVM_BIN=~/cpu/llvm-thumips/llvm-3.1.src/Release+Asserts/bin
#LLC=$(LLVM_BIN)/llc -march=mipsel
#GCC_PREFIX=/home/guest/cpu/llvm_install/bin/mipsel-linux-
GCC_PREFIX=mips-sde-elf-
CC=$(GCC_PREFIX)gcc
AS=$(GCC_PREFIX)as -EL -g -mips32 
LD=$(GCC_PREFIX)ld

all: a.out

a.out: test1.o init.o
	$(LD) -G0 -EL -nostdlib -static -T ldscript.ld -o $@ $^

init.o: init.s
	$(AS)  -o $@ $^

test1.o: test1.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf a.out *.o  

run: a.out
	qemu-system-mipsel -M mipssim -m 2M -serial stdio -kernel a.out
