	.file	"f23.cc"
	.text
	.globl	_Z1fllll
	.type	_Z1fllll, @function
_Z1fllll:
.LFB0:
	subq	%rsi, %rdi
	leaq	(%rdi,%rcx), %rax
	ret
.LFE0:
	.size	_Z1fllll, .-_Z1fllll
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
