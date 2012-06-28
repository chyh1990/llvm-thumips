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
	.frame	$sp,80,$ra
	.mask 	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
# BB#0:
	addiu	$sp, $sp, -80
$tmp5:
	.cfi_def_cfa_offset 80
	sw	$ra, 76($sp)            # 4-byte Folded Spill
	sw	$21, 72($sp)            # 4-byte Folded Spill
	sw	$20, 68($sp)            # 4-byte Folded Spill
	sw	$19, 64($sp)            # 4-byte Folded Spill
	sw	$18, 60($sp)            # 4-byte Folded Spill
	sw	$17, 56($sp)            # 4-byte Folded Spill
	sw	$16, 52($sp)            # 4-byte Folded Spill
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
	sw	$zero, 48($sp)
	sb	$zero, 44($sp)
	lui	$2, 25711
	ori	$2, $2, 28519
	sw	$2, 40($sp)
	lui	$2, 8307
	ori	$2, $2, 26912
	sw	$2, 36($sp)
	lui	$2, 29793
	ori	$2, $2, 26708
	sw	$2, 32($sp)
	sw	$zero, 28($sp)
	addiu	$16, $zero, 4
	addiu	$17, $zero, 3
	addiu	$18, $zero, 66
	addiu	$19, $zero, 99
	b	$BB1_1
	nop
$BB1_5:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$2, 28($sp)
	addiu	$2, $2, 1
	sw	$2, 28($sp)
$BB1_1:                                 # =>This Inner Loop Header: Depth=1
	lw	$2, 28($sp)
	slt	$2, $16, $2
	bne	$2, $zero, $BB1_6
	nop
# BB#2:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$5, 28($sp)
	addiu	$20, $sp, 32
	addu	$2, $20, $5
	lbu	$21, 0($2)
	lw	$25, %call16(add)($gp)
	addu	$4, $zero, $5
	jalr	$25
	nop
	lw	$gp, 16($sp)
	addu	$2, $21, $2
	lw	$3, 28($sp)
	addu	$3, $20, $3
	lb	$4, 0($3)
	addu	$2, $2, $4
	addiu	$2, $2, 33
	sb	$2, 0($3)
	lw	$2, 28($sp)
	bne	$2, $17, $BB1_4
	nop
# BB#3:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$2, 28($sp)
	addu	$2, $20, $2
	sb	$18, 0($2)
	bgez	$zero, $BB1_5
	nop
$BB1_4:                                 #   in Loop: Header=BB1_1 Depth=1
	lw	$2, 28($sp)
	addu	$2, $20, $2
	sb	$19, 0($2)
	b	$BB1_5
	nop
$BB1_6:
	lw	$2, 28($sp)
	mul	$2, $2, $2
	sw	$2, 28($sp)
	addiu	$2, $2, 23
	sw	$2, 28($sp)
	addu	$2, $zero, $zero
	lw	$16, 52($sp)            # 4-byte Folded Reload
	lw	$17, 56($sp)            # 4-byte Folded Reload
	lw	$18, 60($sp)            # 4-byte Folded Reload
	lw	$19, 64($sp)            # 4-byte Folded Reload
	lw	$20, 68($sp)            # 4-byte Folded Reload
	lw	$21, 72($sp)            # 4-byte Folded Reload
	lw	$ra, 76($sp)            # 4-byte Folded Reload
	addiu	$sp, $sp, 80
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


