CLANG=clang
CFLAGS=-O0 -emit-llvm -c  -g
LLVM_BIN=~/cpu/llvm-thumips/llvm-3.1.src/Release+Asserts/bin
LLC=$(LLVM_BIN)/llc -march=mipsel
GCC_PREFIX=/home/guest/cpu/llvm_install/bin/mipsel-linux-
#GCC_PREFIX=mips-sde-elf-
AS=$(GCC_PREFIX)as -EL -g -mips32 
LD=$(GCC_PREFIX)ld

all: a.out

a.out: test1.o init.o
	$(LD) -G 0 -n -nostdlib -static -T ldscript.ld -o $@ $^

init.o: init.s
	$(AS)  -o $@ $^

test1.o: test1.c
	$(CLANG) $(CFLAGS) -o test1.bc $^
	$(LLC) test1.bc 
	$(AS) -KPIC -o $@ test1.s 

clean:
	-rm a.out *.o test1.bc test1.s
