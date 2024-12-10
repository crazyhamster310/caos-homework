	.intel_syntax noprefix
	.global very_important_function
	.extern A

	.data
printf_mask:
	.asciz "%lld "
scanf_mask:
	.asciz "%d"
number: .quad 0

	.text
very_important_function:
	push r12
	push r13
	mov rcx, rdi
	xor r12, r12
	mov r13, A
for:
	push rcx
	lea rdi, [scanf_mask]
	lea rsi, [number]
	xor rax, rax
	call scanf

	movsxd r10, [number]
	movsxd rax, [r13 + r12]
	imul r10
	
	lea rdi, [printf_mask]
	mov rsi, rax
	xor rax, rax
	call printf
	pop rcx
	
	add r12, 4
	loop for

	pop r13
	pop r12

	ret