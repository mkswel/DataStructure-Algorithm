	.arch armv8-a
	.file	"test4.c"
	.text
	.align	2
	.global	nsum_for
	.type	nsum_for, %function
nsum_for:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x29, sp
	.cfi_def_cfa_register 29
	sub	sp, sp, #16
	str	w0, [x29, 28]	//[x29, 28]存放n
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x1, [x0]
	str	x1, [x29, 56]
	mov	x1, 0
	mov	x0, sp
	mov	x10, x0			//x10存放栈指针
	ldr	w0, [x29, 28]
	sxtw	x1, w0
	sub	x1, x1, #1
	str	x1, [x29, 40]
	sxtw	x1, w0
	mov	x8, x1
	mov	x9, 0
	lsr	x1, x8, 59
	lsl	x5, x9, 5
	orr	x5, x1, x5
	lsl	x4, x8, 5
	sxtw	x1, w0
	mov	x6, x1
	mov	x7, 0
	lsr	x1, x6, 59
	lsl	x3, x7, 5
	orr	x3, x1, x3
	lsl	x2, x6, 5
	sxtw	x0, w0
	lsl	x0, x0, 2
	add	x0, x0, 15
	lsr	x0, x0, 4
	lsl	x0, x0, 4
	and	x1, x0, -65536
	sub	x1, sp, x1
.L2:
	cmp	sp, x1
	beq	.L3
	sub	sp, sp, #65536
	str	xzr, [sp, 1024]
	b	.L2
.L3:
	and	x1, x0, 65535
	sub	sp, sp, x1
	str	xzr, [sp]
	and	x0, x0, 65535
	cmp	x0, 1024
	bcc	.L4
	str	xzr, [sp, 1024]
.L4:
	add	x0, sp, 16				//以下四行用于调整数组a首地址位置
	add	x0, x0, 3
	lsr	x0, x0, 2
	lsl	x0, x0, 2
	str	x0, [x29, 48]			//[x29, 48]存放数组a首地址
	str	wzr, [x29, 36]			//[x29, 36]存放result，全零寄存器wzr用于初始化result为0
	str	wzr, [x29, 32]			//[x29, 32]存放i
	b	.L5
.L6:							//循环体
	ldr	x0, [x29, 48]			//取数组a首地址到x0
	ldrsw	x1, [x29, 32]		//取i值到变址寄存器x1
	ldr	w2, [x29, 32]			//取i值到w2
	str	w2, [x0, x1, lsl 2]		//执行指令a[i]=i
	ldr	x0, [x29, 48]
	ldrsw	x1, [x29, 32]
	ldr	w0, [x0, x1, lsl 2]		//导出a[i]值到w0
	ldr	w1, [x29, 36]			//取result值到w1
	add	w0, w1, w0				//执行指令result+=a[i]
	str	w0, [x29, 36]			//存回reult
	ldr	w0, [x29, 32]			//取i值到w0
	add	w0, w0, 1				//执行指令i++
	str	w0, [x29, 32] 		  	//存回i
.L5:
	ldr	w1, [x29, 32]
	ldr	w0, [x29, 28]			//[x29, 28]存放n
	cmp	w1, w0					//判断循环终止
	blt	.L6
	ldr	w0, [x29, 36]
	mov	sp, x10
	mov	w1, w0					//返回result值
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x3, [x29, 56]
	ldr	x2, [x0]
	subs	x3, x3, x2
	mov	x2, 0
	beq	.L8
	bl	__stack_chk_fail
.L8:
	mov	w0, w1
	mov	sp, x29
	ldp	x29, x30, [sp], 64	//恢复栈帧和指令地址，从函数调用中返回
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE0:
	.size	nsum_for, .-nsum_for
	.section	.rodata
	.align	3
.LC0:
	.string	"%d\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!	
	/*
	s29和x30入栈sp，并且sp自减32
	函数调用前用于保存帧指针和返回地址
	x29帧指针寄存器存放栈帧底部地址
	x30链接寄存器存放返回地址,即指令str	w0, [sp, 28]的地址
	x29跟x30都是64位，分别占用8字节，这里分配32字节
	x29存放在[sp-32]，x30存放在[sp-24]
	额外分配16字节用于存放其他数据，局部变量等
	*/
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	mov	w0, 7
	bl	nsum_for
	str	w0, [sp, 28]		//[sp, 28]存放ans
	ldr	w1, [sp, 28]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
