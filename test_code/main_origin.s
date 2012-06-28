	.section .mdebug.abi32
	.previous
	.file	"main.bc"
	.text
	.globl	main
	.align	2
	.type	main,@function
	.ent	main                    # @main
main:
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
# BB#0:
	addiu	$sp, $sp, -24
$tmp1:
	.cfi_def_cfa_offset 24
	sw	$zero, 20($sp)
	sb	$zero, 16($sp)
	lui	$2, 25711
	ori	$2, $2, 28519
	sw	$2, 12($sp)
	lui	$2, 8307
	ori	$2, $2, 26912
	sw	$2, 8($sp)
	lui	$2, 29793
	ori	$2, $2, 26708
	sw	$2, 4($sp)
	sw	$zero, 0($sp)
	addiu	$2, $zero, 4
	b	$BB0_1
	nop
$BB0_2:                                 #   in Loop: Header=BB0_1 Depth=1
	lw	$3, 0($sp)
	addiu	$4, $sp, 4
	addu	$3, $4, $3
	lbu	$4, 0($3)
	addiu	$4, $4, 1
	sb	$4, 0($3)
	lw	$3, 0($sp)
	addiu	$3, $3, 1
	sw	$3, 0($sp)
$BB0_1:                                 # =>This Inner Loop Header: Depth=1
	lw	$3, 0($sp)
	slt	$3, $2, $3
	beq	$3, $zero, $BB0_2
	nop
# BB#3:
	addu	$2, $zero, $zero
	addiu	$sp, $sp, 24
	jr	$ra
	nop
	.set	macro
	.set	reorder
	.end	main
$tmp2:
	.size	main, ($tmp2)-main
	.cfi_endproc

	.type	$main.test,@object      # @main.test
	.section	.rodata.str1.1,"aMS",@progbits,1
$main.test:
	.asciz	 "That is good"
	.size	$main.test, 13


