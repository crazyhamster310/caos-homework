	.text
	.global sum

sum:
	cmp x1, 0
	beq recursion_end
	ldr x3, [x2]
	add x0, x0, x3
	add x2, x2, 4
	sub x1, x1, 1
	b sum
recursion_end:
	ret
