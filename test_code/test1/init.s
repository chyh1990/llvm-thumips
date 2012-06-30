.global start
.extern main

.set noreorder
.set STACKSIZE, 0x100

.section .text

start:
  jal 1f
  nop
  .word _gp
1:
  lw $gp, 0($ra)
  la $sp, stack+STACKSIZE-8
  la $t9, main
  jal $t9
  nop
  bgez $zero, .
  nop

.section .bss
stack:
  .space STACKSIZE


