clang -O0 -emit-llvm -c -o main.bc main.c
# the following line just for modified llvm code
~/cpu/llvm-thumips/llvm-3.1.src/Release+Asserts/bin/llc -march=mipsel main.bc
# the following line for origin llvm
#~/cpu/llvm_install/bin/llc -march=mipsel main.bc -o main_origin.s
