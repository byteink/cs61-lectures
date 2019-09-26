	.file	"f24.cc"
	.text
	.globl	_Z1fiii
	.type	_Z1fiii, @function
_Z1fiii:
.LFB0:
	cmpl	%edx, %esi
	je	.L3
	movl	%esi, %eax
	ret
.L3:
	movl	%edi, %eax
	ret
.LFE0:
	.size	_Z1fiii, .-_Z1fiii
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
