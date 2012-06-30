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
	.frame	$sp,8,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
# BB#0:
	addiu	$sp, $sp, -8
$tmp1:
	.cfi_def_cfa_offset 8
	sw	$zero, 4($sp)
	addiu	$2, $zero, 1
	sw	$2, 0($sp)
	addiu	$2, $zero, 11
	sw	$2, 0($sp)
	bne	$zero, $zero, $BB0_2
	nop
# BB#1:
	addiu	$2, $zero, 23
	sw	$2, 0($sp)
$BB0_2:
	addu	$2, $zero, $zero
	addiu	$sp, $sp, 8
	jr	$ra
	nop
	.set	macro
	.set	reorder
	.end	main
$tmp2:
	.size	main, ($tmp2)-main
	.cfi_endproc


