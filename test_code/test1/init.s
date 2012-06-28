.global start
.extern main

.set noreorder
.set STACKSIZE, 0x100

.section .text

start:
  la $sp, stack
  addiu $sp, STACKSIZE-32
  jal main
  nop
  bgez $zero, .
  nop

.section .bss
stack:
  .STACKSIZE


