	.file	"test_lw_cycles.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	measure_lw_cycles
	.type	measure_lw_cycles, @function
measure_lw_cycles:
 #APP
# 16 "test_lw_cycles.c" 1
	rdcycle t0
	rdcycle t1
	
# 0 "" 2
 #NO_APP
	lui	t1,%hi(test_data)
	addi	t1,t1,%lo(test_data)
 #APP
# 27 "test_lw_cycles.c" 1
	rdcycle t0
	lw t2, 0(t1)
	rdcycle t1
	
# 0 "" 2
 #NO_APP
	ret
	.size	measure_lw_cycles, .-measure_lw_cycles
	.globl	test_data
	.section	.sdata,"aw"
	.align	2
	.type	test_data, @object
	.size	test_data, 4
test_data:
	.word	305419896
	.ident	"GCC: (14.2.0+19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
