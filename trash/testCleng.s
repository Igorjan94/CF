	.text
	.file	"test.cpp"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%r14
.Ltmp0:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp1:
	.cfi_def_cfa_offset 24
	subq	$72, %rsp
.Ltmp2:
	.cfi_def_cfa_offset 96
.Ltmp3:
	.cfi_offset %rbx, -24
.Ltmp4:
	.cfi_offset %r14, -16
	leaq	12(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	16(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	20(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	24(%rsp), %r14
	movl	$_ZSt3cin, %edi
	movq	%r14, %rsi
	callq	_ZNSirsERi
	leaq	28(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	32(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	36(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	40(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	44(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	48(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	52(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	56(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	leaq	60(%rsp), %rsi
	movl	$_ZSt3cin, %edi
	callq	_ZNSirsERi
	movl	$1, %eax
	movl	$11, %r8d
	xorl	%edx, %edx
	.align	16, 0x90
.LBB0_1:                                # %.lr.ph.i
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_9 Depth 2
	movl	$11, %esi
	subl	%edx, %esi
	movl	16(%rsp), %ecx
	testb	$1, %sil
	jne	.LBB0_3
# BB#2:                                 #   in Loop: Header=BB0_1 Depth=1
	xorl	%ebx, %ebx
	jmp	.LBB0_7
	.align	16, 0x90
.LBB0_3:                                # %.backedge.i._crit_edge.prol
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	20(%rsp), %edi
	cmpl	%edi, %ecx
	jge	.LBB0_4
# BB#5:                                 #   in Loop: Header=BB0_1 Depth=1
	movl	%edi, 16(%rsp)
	movl	%ecx, 20(%rsp)
	jmp	.LBB0_6
	.align	16, 0x90
.LBB0_4:                                #   in Loop: Header=BB0_1 Depth=1
	movl	%edi, %ecx
.LBB0_6:                                # %.lr.ph.i.split
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	$1, %ebx
.LBB0_7:                                # %.lr.ph.i.split
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpl	$10, %edx
	je	.LBB0_13
# BB#8:                                 # %.lr.ph.i.split.split
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	%r8d, %edi
	subl	%ebx, %edi
	leaq	(%r14,%rbx,4), %rbx
	.align	16, 0x90
.LBB0_9:                                # %.backedge.i._crit_edge
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-4(%rbx), %esi
	cmpl	%esi, %ecx
	jge	.LBB0_10
# BB#24:                                #   in Loop: Header=BB0_9 Depth=2
	movl	%esi, -8(%rbx)
	movl	%ecx, -4(%rbx)
	jmp	.LBB0_11
	.align	16, 0x90
.LBB0_10:                               #   in Loop: Header=BB0_9 Depth=2
	movl	%esi, %ecx
.LBB0_11:                               # %.backedge.i
                                        #   in Loop: Header=BB0_9 Depth=2
	movl	(%rbx), %esi
	cmpl	%esi, %ecx
	jge	.LBB0_12
# BB#22:                                #   in Loop: Header=BB0_9 Depth=2
	movl	%esi, -4(%rbx)
	movl	%ecx, (%rbx)
	jmp	.LBB0_23
	.align	16, 0x90
.LBB0_12:                               #   in Loop: Header=BB0_9 Depth=2
	movl	%esi, %ecx
.LBB0_23:                               # %.backedge.i.1
                                        #   in Loop: Header=BB0_9 Depth=2
	addq	$8, %rbx
	addl	$-2, %edi
	jne	.LBB0_9
.LBB0_13:                               # %._crit_edge.i
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%eax
	decl	%r8d
	incl	%edx
	cmpl	$12, %eax
	jne	.LBB0_1
# BB#14:                                # %_Z4sortPi.exit.preheader
	movl	12(%rsp), %ecx
	xorl	%eax, %eax
	testl	%ecx, %ecx
	jle	.LBB0_17
# BB#15:
	xorl	%edx, %edx
	.align	16, 0x90
.LBB0_16:                               # %_Z4sortPi.exit
                                        # =>This Inner Loop Header: Depth=1
	addl	16(%rsp,%rax,4), %edx
	incq	%rax
	cmpl	%ecx, %edx
	jl	.LBB0_16
.LBB0_17:
	cmpl	$12, %eax
	movl	$-1, %esi
	cmovlel	%eax, %esi
	movl	$_ZSt4cout, %edi
	callq	_ZNSolsEi
	movq	%rax, %r14
	movq	(%r14), %rax
	movq	-24(%rax), %rax
	movq	240(%r14,%rax), %rbx
	testq	%rbx, %rbx
	je	.LBB0_25
# BB#18:                                # %_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit
	cmpb	$0, 56(%rbx)
	je	.LBB0_20
# BB#19:
	movb	67(%rbx), %al
	jmp	.LBB0_21
.LBB0_20:
	movq	%rbx, %rdi
	callq	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movl	$10, %esi
	movq	%rbx, %rdi
	callq	*48(%rax)
.LBB0_21:                               # %_ZNKSt5ctypeIcE5widenEc.exit
	movsbl	%al, %esi
	movq	%r14, %rdi
	callq	_ZNSo3putEc
	movq	%rax, %rdi
	callq	_ZNSo5flushEv
	xorl	%eax, %eax
	addq	$72, %rsp
	popq	%rbx
	popq	%r14
	retq
.LBB0_25:
	callq	_ZSt16__throw_bad_castv
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.globl	_Z4sortPi
	.align	16, 0x90
	.type	_Z4sortPi,@function
_Z4sortPi:                              # @_Z4sortPi
	.cfi_startproc
# BB#0:
	leaq	8(%rdi), %r8
	movl	$1, %r10d
	movl	$11, %r9d
	xorl	%r11d, %r11d
	.align	16, 0x90
.LBB1_1:                                # %.lr.ph
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_9 Depth 2
	movl	$11, %eax
	subl	%r11d, %eax
	movl	(%rdi), %esi
	testb	$1, %al
	jne	.LBB1_3
# BB#2:                                 #   in Loop: Header=BB1_1 Depth=1
	xorl	%ecx, %ecx
	jmp	.LBB1_7
	.align	16, 0x90
.LBB1_3:                                #   in Loop: Header=BB1_1 Depth=1
	movl	4(%rdi), %ecx
	cmpl	%ecx, %esi
	jge	.LBB1_4
# BB#5:                                 #   in Loop: Header=BB1_1 Depth=1
	movl	%ecx, (%rdi)
	movl	%esi, 4(%rdi)
	jmp	.LBB1_6
	.align	16, 0x90
.LBB1_4:                                #   in Loop: Header=BB1_1 Depth=1
	movl	%ecx, %esi
.LBB1_6:                                # %.lr.ph.split
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	$1, %ecx
.LBB1_7:                                # %.lr.ph.split
                                        #   in Loop: Header=BB1_1 Depth=1
	cmpl	$10, %r11d
	je	.LBB1_13
# BB#8:                                 # %.lr.ph.split.split
                                        #   in Loop: Header=BB1_1 Depth=1
	movl	%r9d, %edx
	subl	%ecx, %edx
	leaq	(%r8,%rcx,4), %rcx
	.align	16, 0x90
.LBB1_9:                                #   Parent Loop BB1_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-4(%rcx), %eax
	cmpl	%eax, %esi
	jge	.LBB1_10
# BB#15:                                #   in Loop: Header=BB1_9 Depth=2
	movl	%eax, -8(%rcx)
	movl	%esi, -4(%rcx)
	jmp	.LBB1_11
	.align	16, 0x90
.LBB1_10:                               #   in Loop: Header=BB1_9 Depth=2
	movl	%eax, %esi
.LBB1_11:                               # %.backedge
                                        #   in Loop: Header=BB1_9 Depth=2
	movl	(%rcx), %eax
	cmpl	%eax, %esi
	jge	.LBB1_12
# BB#16:                                #   in Loop: Header=BB1_9 Depth=2
	movl	%eax, -4(%rcx)
	movl	%esi, (%rcx)
	jmp	.LBB1_17
	.align	16, 0x90
.LBB1_12:                               #   in Loop: Header=BB1_9 Depth=2
	movl	%eax, %esi
.LBB1_17:                               # %.backedge.1
                                        #   in Loop: Header=BB1_9 Depth=2
	addq	$8, %rcx
	addl	$-2, %edx
	jne	.LBB1_9
.LBB1_13:                               # %._crit_edge
                                        #   in Loop: Header=BB1_1 Depth=1
	incl	%r10d
	decl	%r9d
	incl	%r11d
	cmpl	$12, %r10d
	jne	.LBB1_1
# BB#14:
	retq
.Lfunc_end1:
	.size	_Z4sortPi, .Lfunc_end1-_Z4sortPi
	.cfi_endproc

	.section	.text.startup,"ax",@progbits
	.align	16, 0x90
	.type	_GLOBAL__sub_I_test.cpp,@function
_GLOBAL__sub_I_test.cpp:                # @_GLOBAL__sub_I_test.cpp
	.cfi_startproc
# BB#0:
	pushq	%rax
.Ltmp5:
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	callq	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$_ZStL8__ioinit, %esi
	movl	$__dso_handle, %edx
	popq	%rax
	jmp	__cxa_atexit            # TAILCALL
.Lfunc_end2:
	.size	_GLOBAL__sub_I_test.cpp, .Lfunc_end2-_GLOBAL__sub_I_test.cpp
	.cfi_endproc

	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.init_array,"aw",@init_array
	.align	8
	.quad	_GLOBAL__sub_I_test.cpp

	.ident	"clang version 3.7.0 (tags/RELEASE_370/final)"
	.section	".note.GNU-stack","",@progbits
