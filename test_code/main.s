	.section .mdebug.abi32
	.previous
	.file	"main.bc"
	.text
	.globl	add
	.align	2
	.type	add,@function
	.ent	add                     # @add
add:
	.cfi_startproc
	.frame	$sp,16,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
# BB#0:
	addiu	$sp, $sp, -16
$tmp1:
	.cfi_def_cfa_offset 16
	sw	$4, 8($sp)
	sw	$5, 4($sp)
	lw	$2, 8($sp)
	bne	$2, $5, $BB0_2
	nop
# BB#1:
	lw	$2, 4($sp)
	lw	$3, 8($sp)
	subu	$2, $3, $2
	bgez	$zero, $BB0_3
	nop
$BB0_2:
	lw	$2, 4($sp)
	lw	$3, 8($sp)
	addu	$2, $3, $2
$BB0_3:
	sw	$2, 12($sp)
	lw	$2, 12($sp)
	addiu	$sp, $sp, 16
	jr	$ra
	nop
	.set	macro
	.set	reorder
	.end	add
$tmp2:
	.size	add, ($tmp2)-add
	.cfi_endproc

	.globl	main
	.align	2
	.type	main,@function
	.ent	main                    # @main
main:
	.cfi_startproc
	.frame	$sp,96,$ra
	.mask 	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
# BB#0:
	addiu	$sp, $sp, -96
$tmp5:
	.cfi_def_cfa_offset 96
	sw	$ra, 92($sp)            # 4-byte Folded Spill
	sw	$21, 88($sp)            # 4-byte Folded Spill
	sw	$20, 84($sp)            # 4-byte Folded Spill
	sw	$19, 80($sp)            # 4-byte Folded Spill
	sw	$18, 76($sp)            # 4-byte Folded Spill
	sw	$17, 72($sp)            # 4-byte Folded Spill
	sw	$16, 68($sp)            # 4-byte Folded Spill
$tmp6:
	.cfi_offset 31, -4
$tmp7:
	.cfi_offset 21, -8
$tmp8:
	.cfi_offset 20, -12
$tmp9:
	.cfi_offset 19, -16
$tmp10:
	.cfi_offset 18, -20
$tmp11:
	.cfi_offset 17, -24
$tmp12:
	.cfi_offset 16, -28
	.cprestore	16
	sw	$zero, 64($sp)
	lui	$2, 25711
	ori	$2, $2, 28519
	sw	$2, 56($sp)
	lui	$2, 8307
	ori	$2, $2, 26912
	sw	$2, 52($sp)
	lui	$2, 29793
	ori	$2, $2, 26708
	sw	$2, 48($sp)
	addiu	$2, $zero, 0
	sb	$2, 60($sp)
	andi	$27, $zero, 255
	sb	$27, 28($sp)
	sra	$27, $zero, 8
	andi	$27, $27, 255
	addiu	$26, $sp, 1
	sb	$27, 28($26)
	sw	$zero, 36($sp)
	sw	$zero, 32($sp)
	addiu	$16, $zero, 4
	addiu	$17, $zero, 66
	addiu	$18, $zero, 1
	addiu	$19, $zero, 99
	b	$BB1_1
	nop
$BB1_5:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$2, 32($sp)
	addiu	$3, $2, 1
	lw	$2, 36($sp)
	sw	$3, 32($sp)
	sltu	$3, $3, $18
	addu	$3, $3, $zero
	addu	$2, $2, $3
	sw	$2, 36($sp)
$BB1_1:                                 # =>This Inner Loop Header: Depth=1
	lw	$2, 32($sp)
	sltu	$2, $16, $2
	lw	$3, 36($sp)
	slt	$4, $zero, $3
	movz	$4, $2, $3
	bne	$4, $zero, $BB1_6
	nop
# BB#2:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$5, 32($sp)
	addiu	$20, $sp, 48
	addu	$2, $20, $5
	lbu	$21, 0($2)
	lw	$25, %call16(add)($gp)
	addu	$4, $zero, $5
	jalr	$25
	nop
	lw	$gp, 16($sp)
	addu	$2, $21, $2
	lw	$3, 32($sp)
	addu	$3, $20, $3
	lb	$4, 0($3)
	addu	$2, $2, $4
	addiu	$2, $2, 33
	sb	$2, 0($3)
	lw	$2, 32($sp)
	xori	$2, $2, 3
	lw	$3, 36($sp)
	or	$2, $2, $3
	bne	$2, $zero, $BB1_4
	nop
# BB#3:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$2, 32($sp)
	addu	$2, $20, $2
	sb	$17, 0($2)
	bgez	$zero, $BB1_5
	nop
$BB1_4:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$2, 32($sp)
	addu	$2, $20, $2
	sb	$19, 0($2)
	b	$BB1_5
	nop
$BB1_6:
	addiu	$26, $sp, 1
	lbu	$2, 28($sp)
	lbu	$27, 28($26)
	sll	$27, $27, 8
	or	$2, $2, $27
	addiu	$2, $2, -12
	andi	$27, $2, 255
	sb	$27, 28($sp)
	sra	$27, $2, 8
	andi	$27, $27, 255
	addiu	$26, $sp, 1
	sb	$27, 28($26)
	lw	$2, 32($sp)
	multu	$2, $2
	mflo	$5
	mfhi	$4
	addiu	$3, $zero, 77
	multu	$5, $3
	mflo	$6
	mfhi	$5
	lw	$7, 36($sp)
	sw	$6, 40($sp)
	mul	$2, $2, $7
	addu	$4, $4, $2
	addu	$2, $4, $2
	mul	$2, $2, $3
	addu	$2, $5, $2
	sw	$2, 44($sp)
	lw	$2, 32($sp)
	addiu	$3, $2, 23
	lw	$2, 36($sp)
	sw	$3, 32($sp)
	addiu	$4, $zero, 23
	sltu	$3, $3, $4
	addiu	$4, $zero, 0
	addu	$3, $3, $4
	addu	$2, $2, $3
	sw	$2, 36($sp)
	addu	$2, $zero, $zero
	lw	$16, 68($sp)            # 4-byte Folded Reload
	lw	$17, 72($sp)            # 4-byte Folded Reload
	lw	$18, 76($sp)            # 4-byte Folded Reload
	lw	$19, 80($sp)            # 4-byte Folded Reload
	lw	$20, 84($sp)            # 4-byte Folded Reload
	lw	$21, 88($sp)            # 4-byte Folded Reload
	lw	$ra, 92($sp)            # 4-byte Folded Reload
	addiu	$sp, $sp, 96
	jr	$ra
	nop
	.set	macro
	.set	reorder
	.end	main
$tmp13:
	.size	main, ($tmp13)-main
	.cfi_endproc

	.type	$main.test,@object      # @main.test
	.section	.rodata.str1.1,"aMS",@progbits,1
$main.test:
	.asciz	 "That is good"
	.size	$main.test, 13


