	.file	"main.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	call	init_PortE
.L4:
	movl	$1073890300, %eax
	movl	(%rax), %eax
	andl	$56, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	testl	%eax, %eax
	jne	.L2
	movl	$1073890300, %eax
	movl	$4, (%rax)
	jmp	.L4
.L2:
	movl	$1073890300, %eax
	movl	$0, (%rax)
	jmp	.L4
	.seh_endproc
	.globl	init_PortE
	.def	init_PortE;	.scl	2;	.type	32;	.endef
	.seh_proc	init_PortE
init_PortE:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$1074783752, %eax
	movl	(%rax), %eax
	movl	$1074783752, %edx
	orl	$16, %eax
	movl	%eax, (%rdx)
	movl	$1074783752, %eax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	$1073890592, %eax
	movl	$1280262987, (%rax)
	movl	$1073890600, %eax
	movl	$0, (%rax)
	movl	$1073890604, %eax
	movl	$0, (%rax)
	movl	$1073890304, %eax
	movl	$4, (%rax)
	movl	$1073890336, %eax
	movl	$0, (%rax)
	movl	$1073890576, %eax
	movl	$56, (%rax)
	movl	$1073890588, %eax
	movl	$60, (%rax)
	nop
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 11.2.0"
