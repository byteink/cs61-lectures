	.file	"f39.cc"
	.text
	.globl	_Z7times13j
	.type	_Z7times13j, @function
_Z7times13j:
.LFB0:
	leal	(%rdi,%rdi,2), %eax
	leal	(%rdi,%rax,4), %eax
	ret
.LFE0:
	.size	_Z7times13j, .-_Z7times13j
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
