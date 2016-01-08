	.file	"test.cpp"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	_Z4sortPi
	.type	_Z4sortPi, @function
_Z4sortPi:
.LFB1404:
	.cfi_startproc
	movl	$11, %edx
	.p2align 4,,10
	.p2align 3
.L4:
	subl	$1, %edx
	movq	%rdi, %rax
	leaq	4(%rdi,%rdx,4), %rsi
	movq	%rdx, %r8
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%rax), %edx
	movl	4(%rax), %ecx
	cmpl	%ecx, %edx
	jge	.L2
	movl	%ecx, (%rax)
	movl	%edx, 4(%rax)
.L2:
	addq	$4, %rax
	cmpq	%rsi, %rax
	jne	.L3
	testl	%r8d, %r8d
	movl	%r8d, %edx
	jne	.L4
	rep ret
	.cfi_endproc
.LFE1404:
	.size	_Z4sortPi, .-_Z4sortPi
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.section	.text.startup,"ax",@progbits
.LHOTB1:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1403:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	$_ZSt3cin, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$64, %rsp
	.cfi_def_cfa_offset 96
	leaq	16(%rsp), %rbp
	leaq	12(%rsp), %rsi
	leaq	64(%rsp), %r12
	movq	%rbp, %rbx
	call	_ZNSirsERi
	.p2align 4,,10
	.p2align 3
.L9:
	movq	%rbx, %rsi
	movl	$_ZSt3cin, %edi
	addq	$4, %rbx
	call	_ZNSirsERi
	cmpq	%r12, %rbx
	jne	.L9
	leaq	16(%rsp), %rdi
	call	_Z4sortPi
	movl	12(%rsp), %edx
	xorl	%esi, %esi
	testl	%edx, %edx
	jle	.L10
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L11:
	addl	0(%rbp), %eax
	addl	$1, %esi
	addq	$4, %rbp
	cmpl	%edx, %eax
	jl	.L11
.L10:
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	addq	$64, %rsp
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1403:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE1:
	.section	.text.startup
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.section	.text.startup
.LHOTB2:
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB1572:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE1572:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 5.2.0"
	.section	.note.GNU-stack,"",@progbits
