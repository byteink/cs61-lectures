	.file	"f40.cc"
	.text
	.globl	_Z5or_opii
	.type	_Z5or_opii, @function
_Z5or_opii:
.LFB0:
	movl	%edi, %eax
	orl	%esi, %eax
	ret
.LFE0:
	.size	_Z5or_opii, .-_Z5or_opii
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
