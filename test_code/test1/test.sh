clang -O0 -emit-llvm -c -g -o test1.bc test1.c
~/cpu/llvm-thumips/llvm-3.1.src/Release+Asserts/bin/llc -march=mipsel test1.bc
mips-sde-elf-as -EL -g -mips2 test1.s -o test1.o
mips-sde-elf-ld -T ldscript.ld test1.o init.o
