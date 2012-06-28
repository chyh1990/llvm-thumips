clang -O0 -emit-llvm -c -o main.bc main.c
~/cpu/llvm-thumips/llvm-3.1.src/Release+Asserts/bin/llc -march=mipsel main.bc
