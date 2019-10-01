	.file	"f50.cc"
	.text
	.globl	_Z1fP10four_bytesi
	.type	_Z1fP10four_bytesi, @function
_Z1fP10four_bytesi:
.LFB0:
	movslq	%esi, %rsi
	movzbl	(%rdi,%rsi,4), %eax
	ret
.LFE0:
	.size	_Z1fP10four_bytesi, .-_Z1fP10four_bytesi
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
