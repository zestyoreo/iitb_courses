main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	swap
	movl	buf+4, %edx
	movl	buf, %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LCO, (%esp)
	call	printf
	movl	$0, %eax
	leave
	ret
swap:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$buf+4, bufp1
	movl	bufp0, %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	bufp0, %eax
	movl	bufp1, %edx
	movl	(%edx), %edx
	movl	%edx, (%eax)
	movl	bufp1, %eax
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
	leave
	ret