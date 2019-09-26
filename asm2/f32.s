	.file	"f32.cc"
	.text
	.globl	_Z1f5small
	.type	_Z1f5small, @function
_Z1f5small:
.LFB57:
	movl	%edi, %eax
	movsbl	%dil, %edi
	movsbl	%ah, %eax
	movsbl	%al, %eax
	leal	(%rdi,%rax,2), %eax
	ret
.LFE57:
	.size	_Z1f5small, .-_Z1f5small
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"0"
.LC1:
	.string	"%d.%d = %d\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB58:
	cmpl	$1, %edi
	pushq	%r12
	pushq	%rbp
	pushq	%rbx
	jle	.L4
	movl	%edi, %ebp
	movq	8(%rsi), %rdi
	xorl	%edx, %edx
	movq	%rsi, %r12
	xorl	%esi, %esi
	call	strtol@PLT
	cmpl	$2, %ebp
	movl	%eax, %ebx
	je	.L9
	movq	16(%r12), %rdi
.L5:
	xorl	%edx, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movq	%rax, %rcx
	xorl	%eax, %eax
	movb	%bl, %al
	movb	%cl, %ah
	movl	%eax, %edi
	call	_Z1f5small
	leaq	.LC1(%rip), %rsi
	movl	%eax, %r8d
	movsbl	%bl, %edx
	movsbl	%cl, %ecx
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	popq	%rbx
	xorl	%eax, %eax
	popq	%rbp
	popq	%r12
	ret
.L4:
	leaq	.LC0(%rip), %rdi
	xorl	%edx, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movl	%eax, %ebx
.L9:
	leaq	.LC0(%rip), %rdi
	jmp	.L5
.LFE58:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
