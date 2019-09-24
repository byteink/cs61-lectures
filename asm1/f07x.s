	.file	"f07x.cc"
	.text
	.globl	_Z3sumv
	.type	_Z3sumv, @function
_Z3sumv:
.LFB0:
	movl	aa(%rip), %eax
	addl	ai(%rip), %eax
	addl	au(%rip), %eax
	addl	bi(%rip), %eax
	ret
.LFE0:
	.size	_Z3sumv, .-_Z3sumv
	.globl	main
	.type	main, @function
main:
.LFB1:
	call	_Z3sumv
	rep ret
.LFE1:
	.size	main, .-main
	.globl	bi
	.data
	.align 4
	.type	bi, @object
	.size	bi, 4
bi:
	.long	-1
	.globl	aa
	.align 8
	.type	aa, @object
	.size	aa, 8
aa:
	.long	10
	.long	20
	.globl	au
	.align 4
	.type	au, @object
	.size	au, 4
au:
	.long	10
	.globl	ai
	.align 4
	.type	ai, @object
	.size	ai, 4
ai:
	.long	10
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
