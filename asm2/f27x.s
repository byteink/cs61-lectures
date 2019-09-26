	.file	"f27x.cc"
	.text
	.globl	_Z1fii
	.type	_Z1fii, @function
_Z1fii:
.LFB0:
	cmpl	%esi, %edi
	movl	%esi, %eax
	cmovge	%edi, %eax
	ret
.LFE0:
	.size	_Z1fii, .-_Z1fii
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
